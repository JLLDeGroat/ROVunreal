// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainingItemWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "../../ComponentWidgets/ResourceCostItemWidget.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Dtos/FCityOverviewDtos.h"
#include "Components/Button.h"
#include "../../../../Domain/Client/ROVClient.h"
#include "ROVData/Dtos/FBaseDtos.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "../../../../HUD/City/CityProgressWidget.h"
#include "../../../../Utilities/WidgetUtils.h"
#include "../../../../HUD/City/MainCityWidget.h"
#include "../../../../Delegates/UIDelegates.h"

void UTrainingItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TrainSlider->OnValueChanged.AddDynamic(this, &UTrainingItemWidget::OnSliderChange);
	TrainButton->OnClicked.AddDynamic(this, &UTrainingItemWidget::AttemptTraining);

	GatewayClient = NewObject<UROVClient>();
}

void UTrainingItemWidget::SetUnitName(FString name)
{
	Title->SetText(FText::FromString(name));
}
void UTrainingItemWidget::SetUnitType(EROVUnitType unitType)
{
	UnitType = unitType;
}
void UTrainingItemWidget::SetBuildingId(FGuid id)
{
	BuildingId = id;
}

void UTrainingItemWidget::AddResourceCost(int amount, EResourceType rType)
{
	auto newWidget = CreateResourceCostWidget();
	newWidget->SetupResource(rType, "", amount);

	CostGrid->AddChildToGrid(newWidget, 0, ResourceCostItems.Num());
	ResourceCostItems.Emplace(newWidget);
}

UResourceCostItemWidget *UTrainingItemWidget::CreateResourceCostWidget()
{
	FSoftClassPath hudUIRef(*resourceCostRef);
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UResourceCostItemWidget>())
		return CreateWidget<UResourceCostItemWidget>(this, hudUIWidgetClass);

	return nullptr;
}

void UTrainingItemWidget::OnSliderChange(float value)
{
	UDebugMessages::LogDisplay(this, FString::SanitizeFloat(value, 0));
	UDebugMessages::LogDisplay(this, FString::SanitizeFloat(MaxAmountAllowed, 0));

	RequestedAmount = MaxAmountAllowed * value;

	for (int i = 0; i < ResourceCostItems.Num(); i++)
	{
		ResourceCostItems[i]->SetMultiplier(RequestedAmount);
	}

	TrainAmount->SetText(FText::FromString(FString::SanitizeFloat(RequestedAmount, 0)));
}
#pragma optimize("", off)
void UTrainingItemWidget::SetupMaxAmounts()
{
	auto gameManager = UROVDataUtils::GetGameManager();
	auto manager = UROVDataUtils::GetGameManager();
	auto overview = manager->GetCityOverviewData();

	MaxAmountAllowed = INT32_MAX;

	for (int i = 0; i < ResourceCostItems.Num(); i++)
	{
		auto rType = ResourceCostItems[i]->GetResourceType();

		auto resourceAmount = overview->GetResourceAmount(rType);
		auto amountAllowed = resourceAmount / ResourceCostItems[i]->GetBaseAmount();

		if (amountAllowed < MaxAmountAllowed)
			MaxAmountAllowed = amountAllowed;
	}

	/*for (int i = 0; i < ResourceCostItems.Num(); i++) {
		ResourceCostItems[i]->SetMultiplier(MaxAmountAllowed);
	}*/

	TrainAmount->SetText(FText::FromString(FString::SanitizeFloat(0, 0)));
	MaxTrainAmount->SetText(FText::FromString(FString::SanitizeFloat(MaxAmountAllowed, 0)));
}

void UTrainingItemWidget::AttemptTraining()
{
	if (UnitType == EROVUnitType::INVALID)
		return UDebugMessages::LogError(this, "unit not set er");

	auto gameManager = UROVDataUtils::GetGameManager();
	auto manager = UROVDataUtils::GetGameManager();
	auto overview = manager->GetCityOverviewData();

	GatewayClient->AttemptToTrainUnits(
		overview->GetCityId(), FBase::ToString(BuildingId), RequestedAmount, UnitType,
		[this](FString content)
		{
			FCitySingleProgressResponseApiDto apiDto;
			if (UFileManagementUtilities::JsonToStruct(content, &apiDto))
			{
				UDebugMessages::LogDisplay(this, "suceeded");

				auto uiDelegates = UUIDelegates::GetInstance();
				if (uiDelegates)
				{
					uiDelegates->_OnTraininBeginProgress.Broadcast(apiDto.GetPayload().GetProgressOverview().GetStartTime(),
																   apiDto.GetPayload().GetProgressOverview().GetEndTime(), BuildingId, apiDto.GetPayload().GetProgressOverview().GetTrainingUnitType(),
																   apiDto.GetPayload().GetProgressOverview().GetTrainingUnitAmount());

					uiDelegates->_OnRequestUpdatedResourceCount.Broadcast();
				}
				else
					UDebugMessages::LogError(this, "failed to get ui delegates");

				// auto cityWidget = UWidgetUtils::GetMainCityWidget(this);
				// auto progressWidget = cityWidget->GetCityProgressWidget();
				// progressWidget->OnTrainingAddToProgressWidget(apiDto.GetPayload().GetProgressOverview().GetStartTime(),
				// 											  apiDto.GetPayload().GetProgressOverview().GetEndTime(), BuildingId, apiDto.GetPayload().GetProgressOverview().GetTrainingUnitType(),
				// 											  apiDto.GetPayload().GetProgressOverview().GetTrainingUnitAmount());

				// auto uiDelegates = UUIDelegates::GetInstance();
				// if (uiDelegates)
				// 	uiDelegates->_OnRequestUpdatedResourceCount.Broadcast();
			}

			// SetVisibility(ESlateVisibility::Hidden);
		});
}
#pragma optimize("", on)