// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildableBuildingItemWidget.h"
#include "../BuildBuildingWidget.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "ResourceCostItemWidget.h"
#include "../../../Utilities/WidgetUtils.h"
#include "Components/Button.h"

UBuildableBuildingItemWidget::UBuildableBuildingItemWidget(const FObjectInitializer &ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UBuildableBuildingItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BuildButton->OnClicked.AddDynamic(this, &UBuildableBuildingItemWidget::BuildClicked);
}

int UBuildableBuildingItemWidget::GetGridColumn(int currentTotal)
{
	auto column = currentTotal;
	if (currentTotal > 2)
		column -= 3;
	return column;
}

int UBuildableBuildingItemWidget::GetGridRow(int currentTotal)
{
	auto row = 0;
	if (currentTotal > 2)
		row += 1;
	return row;
}

void UBuildableBuildingItemWidget::SetParentWidget(UBuildBuildingWidget *parent)
{
	ParentWidget = parent;
}

void UBuildableBuildingItemWidget::BuildClicked()
{
	ParentWidget->AttemptToBuildBuilding((uint8)BuildingType);
}
void UBuildableBuildingItemWidget::SetTitleAndDesc(EBuildingType bType, FString name, FString desc)
{
	BuildingType = bType;
	BuildingName->SetText(FText::FromString(name));
	BuildingDescription->SetText(FText::FromString(desc));
}

void UBuildableBuildingItemWidget::AddResourceItem(EResourceType rType, int amount)
{
	auto resourceItem = UWidgetUtils::CreateResourceCostItemWidget(this); // CreateResourceCostWidget();

	auto row = ResourceCostGrid->GetChildrenCount() >= 3 ? 1 : 0;
	auto column = ResourceCostGrid->GetChildrenCount() >= 3 ? ResourceCostGrid->GetChildrenCount() - 3 : ResourceCostGrid->GetChildrenCount();

	resourceItem->SetupResource(rType, "res", amount);
	ResourceCostGrid->AddChildToGrid(resourceItem, row, column);
}

UResourceCostItemWidget *UBuildableBuildingItemWidget::CreateResourceCostWidget()
{
	FSoftClassPath hudUIRef(*resourceCostRef);
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UResourceCostItemWidget>())
		return CreateWidget<UResourceCostItemWidget>(this, hudUIWidgetClass);

	return nullptr;
}