// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingUpgradeDetails.h"
#include "../../ComponentWidgets/ResourceCostItemWidget.h"
#include "../../../../Utilities/WidgetUtils.h"
#include "../../../../Delegates/UIDelegates.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "Components/GridPanel.h"
#include "Components/Button.h"
#include "../../../../Domain/Client/ROVClient.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"

void UBuildingUpgradeDetails::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UpgradeBtn->OnClicked.AddDynamic(this, &UBuildingUpgradeDetails::OnUpgradeClicked);
	DeconstructBtn->OnClicked.AddDynamic(this, &UBuildingUpgradeDetails::OnDeconstructClicked);
}

void UBuildingUpgradeDetails::ClearUpgradeWidget()
{
	// CostGridPanel->ClearChildren();
	for (auto item : CostWidgets)
		item->RemoveFromParent();

	CostWidgets.Empty();
}

void UBuildingUpgradeDetails::AddResourceItemToUpdateDetails(UResourceCostItemWidget *costWidget)
{
	AddResourceItemToWidget(costWidget);
}
void UBuildingUpgradeDetails::AddResourceItemToUpdateDetails(EResourceType rType, FString name, int amount)
{
	auto costWidget = UWidgetUtils::CreateResourceCostItemWidget(this);
	costWidget->SetupResource(rType, name, amount);
	AddResourceItemToWidget(costWidget);
}

void UBuildingUpgradeDetails::AddResourceItemToWidget(UResourceCostItemWidget *costWidget)
{
	auto num = CostWidgets.Num();

	auto column = num;
	auto row = 0;
	if (num >= 3)
	{
		row = 1;
		column -= 3;
	}

	UDebugMessages::LogDisplay(this, "adding upgrade item to row: " + FString::SanitizeFloat(row) + " and col: " + FString::SanitizeFloat(column));
	CostGridPanel->AddChildToGrid(costWidget, row, column);
	CostWidgets.Emplace(costWidget);
}

#pragma optimize("", off)
void UBuildingUpgradeDetails::OnUpgradeClicked()
{
	auto cityData = UROVDataUtils::GetGameManager()->GetCityOverviewData();

	auto client = NewObject<UROVClient>();
	client->UpgradeBuilding(
		FBase::ToString(BuildingId),
		cityData->GetCityId(),
		[this](FString content)
		{
			FBuildingUpgradeResponseApiDto responseDto;
			if (UFileManagementUtilities::JsonToStruct(content, &responseDto))
			{
				if (responseDto.GetSuccess())
				{
					auto uiInstance = UUIDelegates::GetInstance();

					if (!uiInstance)
						return UDebugMessages::LogError(this, "failed to get ui delegate instance");

					uiInstance->_OnRequestUpdatedResourceCount.Broadcast();
					uiInstance->_OnBuildingBeginConstruction.Broadcast(responseDto.GetPayload().GetStartTime(),
																	   responseDto.GetPayload().GetFinishTime(),
																	   BuildingType, BuildingId);
				}
				else
				{
					UDebugMessages::LogError(this, "failed to upgrade " + responseDto.GetError());
				}
			}
		});
}

void UBuildingUpgradeDetails::OnDeconstructClicked()
{
	auto cityData = UROVDataUtils::GetGameManager()->GetCityOverviewData();
	auto client = NewObject<UROVClient>();

	client->DeconstructBuilding(
		FBase::ToString(BuildingId),
		cityData->GetCityId(),
		[this](FString content)
		{
			FBuildingDeconstructResponseApiDto responseDto;
			if (UFileManagementUtilities::JsonToStruct(content, &responseDto))
			{
				if (responseDto.GetSuccess())
				{
					auto uiInstance = UUIDelegates::GetInstance();

					if (!uiInstance)
						return UDebugMessages::LogError(this, "failed to get ui delegate instance");

					uiInstance->_OnRequestUpdatedResourceCount.Broadcast();
					uiInstance->_OnBuildingBeginConstruction.Broadcast(responseDto.GetPayload().GetStartTime(),
																	   responseDto.GetPayload().GetFinishTime(),
																	   BuildingType, BuildingId);
				}
				else
				{
					UDebugMessages::LogError(this, "failed to deconstruct " + responseDto.GetError());
				}
			}
		});
}

void UBuildingUpgradeDetails::HideDeconstructBtn()
{
	DeconstructBtn->SetVisibility(ESlateVisibility::Hidden);
}
void UBuildingUpgradeDetails::ShowDeconstructBtn()
{
	DeconstructBtn->SetVisibility(ESlateVisibility::Visible);
}

void UBuildingUpgradeDetails::HideUpgradeBtn()
{
	UpgradeBtn->SetVisibility(ESlateVisibility::Hidden);
}
void UBuildingUpgradeDetails::ShowUpgradeBtn()
{
	UpgradeBtn->SetVisibility(ESlateVisibility::Visible);
}

#pragma optimize("", on)
