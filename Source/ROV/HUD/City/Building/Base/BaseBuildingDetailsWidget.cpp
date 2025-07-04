// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBuildingDetailsWidget.h"
#include "../../../../Entities/Components/BuildingDetailsComponent.h"
#include "../../../../Utilities/WidgetUtils.h"
#include "../../../../Delegates/CityDelegates.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../../../Domain/Client/ROVClient.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Manager/GameDataManager.h"
#include "VgFlmngmnt/Domain/FileManagementUtilities.h"
#include "../../ComponentWidgets/ResourceCostItemWidget.h"
#include "../Components/BuildingUpgradeDetails.h"
#include "../../ComponentWidgets/CityProgressItemWidget.h"

void UBaseBuildingDetailsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetVisibility(ESlateVisibility::Hidden);
	GatewayClient = NewObject<UROVClient>();

	ExitButton->OnClicked.AddDynamic(this, &UBaseBuildingDetailsWidget::HideWidget);
}

void UBaseBuildingDetailsWidget::BaseSetup(AActor *actor)
{
	BuildingActor = actor;
	SetVisibility(ESlateVisibility::Visible);
	auto buildingDetails = BuildingActor->GetComponentByClass<UBuildingDetailsComponent>();
	if (!buildingDetails)
		return UDebugMessages::LogError(this, "failed to get details component");

	Title->SetText(FText::FromString(UWidgetUtils::GetBuildingNameFromEnum(buildingDetails->GetBuildingType())));

	if (!UWidgetUtils::IsAtMaxLevel(buildingDetails->GetLevel()))
	{
		UDebugMessages::LogDisplay(this, "adding upgrade widget");
		UpgradeWidget->ClearUpgradeWidget();
		UpgradeWidget->SetBuildingId(buildingDetails->GetBuildingId());
		UpgradeWidget->SetBuildingType(buildingDetails->GetBuildingType());
		auto gameManager = UROVDataUtils::GetGameManager();

		UpgradeWidget->HideDeconstructBtn();
		UpgradeWidget->HideUpgradeBtn();

		if (buildingDetails->GetBuildingType() == EBuildingType::City)
		{
			GatewayClient->GetCityUpgradeDetails(
				gameManager->GetCityOverviewData()->GetCityId(),
				[this](FString content)
				{
					FBuildingCityUpgradeDetailsResponseApiDto responseDto;
					if (UFileManagementUtilities::JsonToStruct(content, &responseDto))
					{
						auto payload = responseDto.GetPayload();
						auto resources = payload.GetResources();

						for (auto res : resources)
						{
							auto resourceCostItem = UWidgetUtils::CreateResourceCostItemWidget(this);
							resourceCostItem->SetupResource(res.GetResourceType(), ROVEnums::ResourceAsString(res.GetResourceType()), res.GetAmount());
							UpgradeWidget->AddResourceItemToUpdateDetails(resourceCostItem);
						}

						UpgradeWidget->ShowUpgradeBtn();
					}
				});
		}
		else
		{
			GatewayClient->GetBuildingUpgradeCosts(
				gameManager->GetCityOverviewData()->GetCityId(), buildingDetails->GetBuildingId().ToString(EGuidFormats::DigitsWithHyphens),
				[this](FString content)
				{
					// change all code to use this instead? question mark
					FBuildingUpgradeCostResponseApiDto responseTest;
					if (FJsonObjectConverter::JsonObjectStringToUStruct(content, &responseTest, 0, 0))
					{
						auto costPayload = responseTest.GetPayload();
						auto upgradeDetails = costPayload.GetBuildingUpgradeDetails();
						auto upgradeCosts = costPayload.GetBuildCost();

						for (auto cost : upgradeCosts.GetResources())
						{
							auto resourceCostItem = UWidgetUtils::CreateResourceCostItemWidget(this);
							resourceCostItem->SetupResource(cost.GetResourceType(), ROVEnums::ResourceAsString(cost.GetResourceType()), cost.GetAmount());
							UpgradeWidget->AddResourceItemToUpdateDetails(resourceCostItem);
						}

						UpgradeWidget->ShowUpgradeBtn();
						UpgradeWidget->ShowDeconstructBtn();
					}
				});
		}
	}
}

void UBaseBuildingDetailsWidget::HideWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	auto cityDelegates = UCityDelegates::GetInstance();
	if (cityDelegates)
		cityDelegates->_OnAllowUiReactions.Broadcast();
}

void UBaseBuildingDetailsWidget::SetUpgradeWidgetVisibility(ESlateVisibility visibility)
{
	UpgradeWidget->SetVisibility(visibility);
}

void UBaseBuildingDetailsWidget::StartProgressWidgetsHandle()
{
	GetWorld()->GetTimerManager().SetTimer(UpdateProgressWidgetsHandle, this, &UBaseBuildingDetailsWidget::UpdateProgressWidgetsCallback, 1.0f, false);
}

void UBaseBuildingDetailsWidget::UpdateProgressWidgetsCallback()
{
	if (ProgressItem)
	{
		if (ProgressItem->GetIsComplete())
		{
			ProgressItem->SetVisibility(ESlateVisibility::Hidden);
			SetupForBuilding(BuildingActor);
		}
		else
			ProgressItem->CalculateProgress();
	}

	if (ProgressItem->GetVisibility() != ESlateVisibility::Visible)
	{
		UDebugMessages::LogDisplay(this, "building training queue no longer visible, stopping timer");
		GetWorld()->GetTimerManager().ClearTimer(UpdateProgressWidgetsHandle);
	}
	else
		StartProgressWidgetsHandle();
}