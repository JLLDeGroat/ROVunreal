// Fill out your copyright notice in the Description page of Project Settings.

#include "CityBuildingDetailsWidget.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "../../../Entities/Components/BuildingDetailsComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../ComponentWidgets/CityProgressItemWidget.h"
#include "../../../Domain/Client/ROVClient.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "Components/TextBlock.h"
#include "VgFlmngmnt/Domain/FileManagementUtilities.h"
#include "Components/ScrollBox.h"
#include "Components/GridPanel.h"
#include "Components/TrainingItemWidget.h"
#include "../../../Utilities/WidgetUtils.h"
#include "Components/UnitDetailItem.h"

void UCityBuildingDetailsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
#pragma optimize("", off)

void UCityBuildingDetailsWidget::SetupForBuilding(AActor *buildingActor)
{
	BaseSetup(buildingActor);

	ProgressItem->SetVisibility(ESlateVisibility::Hidden);

	auto gameData = UROVDataUtils::GetGameManager();
	auto garrison = gameData->GetCityOverviewData()->GetGarrison();

	for (auto unit : garrison->GetArmy()->GetUnits())
	{
		auto detailItemWidget = GetUnitDetailItem(unit.GetUnitType());

		if (!detailItemWidget)
		{
			detailItemWidget = UWidgetUtils::CreateUnitDetailItemWidget(this);
			PlaceUnitDetailsInWidget(detailItemWidget);

			detailItemWidget->SetupItem(unit.GetAmount(), unit.GetUnitType());
			UnitDetailWidgets.Emplace(detailItemWidget);
		}

		detailItemWidget->SetUnitAmount(unit.GetAmount());
	}
	// get units
	// add to unit grid panel
	auto unitItemWidget = UWidgetUtils::CreateUnitDetailItemWidget(this);
}

UUnitDetailItem *UCityBuildingDetailsWidget::GetUnitDetailItem(EROVUnitType unitType)
{
	for (auto detailItem : UnitDetailWidgets)
		if (detailItem->GetUnitType() == unitType)
			return detailItem;

	return nullptr;
}

void UCityBuildingDetailsWidget::PlaceUnitDetailsInWidget(UUnitDetailItem *widgetItem)
{
	auto column = UnitDetailWidgets.Num();
	auto row = 0;
	if (column >= 3)
	{
		column -= 3;
		row += 1;
	}

	UnitDetailsPanel->AddChildToGrid(widgetItem, row, column);
}

#pragma optimize("", on)