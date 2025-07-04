// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildBuildingWidget.h"
#include "../../Delegates/UIDelegates.h"
#include "../../Delegates/CityDelegates.h"
#include "../../Interfaces/GatewayClient.h"
#include "../../Domain/Client/ROVClient.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "ROVData/Dtos/FBuildingDtos.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "Components/Button.h"
#include "ComponentWidgets/BuildableBuildingItemWidget.h"
#include "ComponentWidgets/ResourceCostItemWidget.h"
#include "Components/ScrollBox.h"

UBuildBuildingWidget::UBuildBuildingWidget(const FObjectInitializer &ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UBuildBuildingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetVisibility(ESlateVisibility::Hidden);
	GatewayClient = NewObject<UROVClient>();
	BuildablesAdded = false;

	auto uiInstance = UUIDelegates::GetInstance();
	uiInstance->_OnEmptySlotClicked.AddDynamic(this, &UBuildBuildingWidget::EmptySlotClicked);
	ExitButton->OnClicked.AddDynamic(this, &UBuildBuildingWidget::HideWidget);
}

void UBuildBuildingWidget::EmptySlotClicked(int32 SlotId)
{
	SetVisibility(ESlateVisibility::Visible);
	CurrentSlot = SlotId;
	if (!BuildablesAdded)
	{

		auto manager = UROVDataUtils::GetGameManager();
		auto cityId = manager->GetCityOverviewData()->GetCityId();

		GatewayClient->GetSlotContents(cityId, [this](FString content)
									   { return OnGetSlotContents(content); });
	}
}
void UBuildBuildingWidget::OnGetSlotContents(FString content)
{
	FBuildingSlotContentsApiDto response;
	if (UFileManagementUtilities::JsonToStruct(content, &response))
	{
		for (int i = 0; i < response.GetPayload().GetBuildingItems().Num(); i++)
		{

			auto item = response.GetPayload().GetBuildingItems()[i];
			UDebugMessages::LogDisplay(this, item.GetName());
			UDebugMessages::LogDisplay(this, "has " + FString::SanitizeFloat(item.GetBuildingCost().GetResources().Num()) + " resources");

			auto newWidget = CreateBuildingItemWidget();
			newWidget->SetTitleAndDesc(item.GetBuildingType(), item.GetName(), item.GetDescription());
			newWidget->SetParentWidget(this);

			// AddBuildableItem(this, (uint8)item.GetBuildingType(), item.GetName(), item.GetDescription());
			for (int x = 0; x < item.GetBuildingCost().GetResources().Num(); x++)
			{
				auto res = item.GetBuildingCost().GetResources()[x];
				newWidget->AddResourceItem(res.GetResourceType(), res.GetAmount());
			}
			BuildableScroll->AddChild(newWidget);
		}

		BuildablesAdded = true;
	}
	else
	{
		UDebugMessages::LogError(this, "failed to serialize SlotContents");
	}
}

void UBuildBuildingWidget::AttemptToBuildBuilding(uint8 buildingType)
{
	auto manager = UROVDataUtils::GetGameManager();
	auto cityId = manager->GetCityOverviewData()->GetCityId();

	FBuildingBuildRequestDto buildRequest = FBuildingBuildRequestDto();
	buildRequest.SetBuildingType((EBuildingType)buildingType);
	buildRequest.SetCityId(cityId);
	buildRequest.SetSlot(CurrentSlot);

	GatewayClient->AttemptToBuild(&buildRequest, [this](FString content)
								  { return OnAttemptCallback(content); });
}
#pragma optimize("", off)
void UBuildBuildingWidget::OnAttemptCallback(FString content)
{
	UDebugMessages::LogDisplay(this, content);

	FBuildingBuildResponseDto responseDto;
	UDebugMessages::LogDisplay(this, content);
	if (UFileManagementUtilities::JsonToStruct(content, &responseDto))
	{

		if (!responseDto.GetSuccess())
		{
			UDebugMessages::LogError(this, "TODO: affect ui to tell user what happened");
			return UDebugMessages::LogError(this, "failed to build building. " + responseDto.GetError());
		}

		UDebugMessages::LogDisplay(this, "successfully built");

		auto cityInstance = UCityDelegates::GetInstance();
		cityInstance->_OnSuccessBuildBuilding.Broadcast(CurrentSlot, responseDto.GetPayload().GetBuildingType());

		auto gameManager = UROVDataUtils::GetGameManager();
		auto slot = gameManager->GetSlotOverviewBySlotId(CurrentSlot);

		if (!slot->GetBuilding() || slot->GetBuilding()->GetBuildingType() == EBuildingType::INVALID)
		{
			auto building = slot->AddBuilding(responseDto.GetPayload().GetBuildingType(), responseDto.GetPayload().GetBuildingId().ToString(EGuidFormats::DigitsWithHyphens), 0);
			if (building)
			{
				auto name = building->GetBuildingType();
			}
		} // gameManager->AddBuildingToSlot(slot->GetSlot(), responseDto.GetPayload().GetBuildingType(), responseDto.GetPayload().GetBuildingId().ToString(EGuidFormats::DigitsWithHyphens), 0);

		slot = gameManager->GetSlotOverviewBySlotId(CurrentSlot);

		auto uiInstance = UUIDelegates::GetInstance();

		if (!uiInstance)
			return UDebugMessages::LogError(this, "failed to get ui delegate instance");

		uiInstance->_OnRequestUpdatedResourceCount.Broadcast();
		uiInstance->_OnBuildingBeginConstruction.Broadcast(responseDto.GetPayload().GetStartTime(),
														   responseDto.GetPayload().GetFinishTime(), responseDto.GetPayload().GetBuildingType(),
														   responseDto.GetPayload().GetBuildingId());

		slot = gameManager->GetSlotOverviewBySlotId(CurrentSlot);
	}
}

UResourceCostItemWidget *UBuildBuildingWidget::CreateResourceCostWidget()
{
	FSoftClassPath hudUIRef(*resourceCostRef);
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UResourceCostItemWidget>())
		return CreateWidget<UResourceCostItemWidget>(this, hudUIWidgetClass);

	return nullptr;
}

UBuildableBuildingItemWidget *UBuildBuildingWidget::CreateBuildingItemWidget()
{
	FSoftClassPath hudUIRef(*buildingItemRef);
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UBuildableBuildingItemWidget>())
		return CreateWidget<UBuildableBuildingItemWidget>(this, hudUIWidgetClass);

	return nullptr;
}

void UBuildBuildingWidget::HideWidget()
{
	SetVisibility(ESlateVisibility::Hidden);

	auto cityDelegates = UCityDelegates::GetInstance();
	if (cityDelegates)
	{
		cityDelegates->_OnAllowUiReactions.Broadcast();
	}
}
#pragma optimize("", on)