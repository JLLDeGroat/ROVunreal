// Fill out your copyright notice in the Description page of Project Settings.

#include "CityProgressWidget.h"
#include "ComponentWidgets/CityProgressItemWidget.h"
#include "../../Delegates/UIDelegates.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "ComponentWidgets/CityProgressItemWidget.h"
#include "../../Utilities/WidgetUtils.h"
#include "Components/VerticalBox.h"

UCityProgressWidget::UCityProgressWidget(const FObjectInitializer &ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UCityProgressWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto uiDelegates = UUIDelegates::GetInstance();
	uiDelegates->_OnBuildingBeginConstruction.AddDynamic(this, &UCityProgressWidget::OnBuildingAddingToProgressWidget);
	uiDelegates->_OnBuildingBeginDeConstruction.AddDynamic(this, &UCityProgressWidget::OnDeconstructingBuildingAddingToProgressWidget);
	uiDelegates->_OnTraininBeginProgress.AddDynamic(this, &UCityProgressWidget::OnTrainingAddToProgressWidget);
}

void UCityProgressWidget::AddToProgressWidgets(UCityProgressItemWidget *widget)
{
	ProgressWidgets.Emplace(widget);

	widget->CalculateProgress();

	if (!GetWorld()->GetTimerManager().IsTimerActive(UpdateProgressWidgetsHandle))
	{
		StartProgressWidgetsHandle();
	}
}

void UCityProgressWidget::UpdateProgressWidgetsCallback()
{

	for (int i = 0; i < ProgressWidgets.Num(); i++)
	{
		if (ProgressWidgets[i])
		{
			if (ProgressWidgets[i]->GetIsComplete())
			{
				ProgressWidgets[i]->RemoveFromParent();
				ProgressWidgets[i] = nullptr;
			}
			else
				ProgressWidgets[i]->CalculateProgress();
		}
	}

	for (int i = ProgressWidgets.Num() - 1; i > 0; i--)
	{
		if (!ProgressWidgets[i])
			ProgressWidgets.RemoveAt(i);
	}

	if (ProgressWidgets.Num() == 0)
		GetWorld()->GetTimerManager().ClearTimer(UpdateProgressWidgetsHandle);
	else
		StartProgressWidgetsHandle();
}

void UCityProgressWidget::StartProgressWidgetsHandle()
{
	GetWorld()->GetTimerManager().SetTimer(UpdateProgressWidgetsHandle, this, &UCityProgressWidget::UpdateProgressWidgetsCallback, 1.0f, false);
}

void UCityProgressWidget::OnBuildingAddingToProgressWidget(FDateTime StartTime, FDateTime EndTime, EBuildingType BuildingType, FGuid BuildingId)
{
	UDebugMessages::LogDisplay(this, "OnBuildingAddingToProgressWidget");
	auto newProgressItem = CreateSupplyListItemWidget(); // UWidgetUtils::CreateWidgetFromPath<UCityProgressItemWidget>(this, ProgressItemWidgetRef);

	if (!newProgressItem)
		return UDebugMessages::LogError(this, "failed to create new progress item");

	newProgressItem->SetProgressValues(StartTime, EndTime, BuildingType, BuildingId);
	ProgressBox->AddChildToVerticalBox(newProgressItem);
	AddToProgressWidgets(newProgressItem);
}

void UCityProgressWidget::OnDeconstructingBuildingAddingToProgressWidget(FDateTime StartTime, FDateTime EndTime, EBuildingType BuildingType, FGuid BuildingId)
{
	UDebugMessages::LogDisplay(this, "OnDeconstructingBuildingAddingToProgressWidget");
	auto newProgressItem = CreateSupplyListItemWidget(); // UWidgetUtils::CreateWidgetFromPath<UCityProgressItemWidget>(this, ProgressItemWidgetRef);

	if (!newProgressItem)
		return UDebugMessages::LogError(this, "failed to create new progress item");
	// TODO Change coolor
	newProgressItem->SetProgressValues(StartTime, EndTime, BuildingType, BuildingId);
	ProgressBox->AddChildToVerticalBox(newProgressItem);
	AddToProgressWidgets(newProgressItem);
}

void UCityProgressWidget::OnTrainingAddToProgressWidget(FDateTime StartTime, FDateTime EndTime, FGuid buildingId, EROVUnitType unitType, int amount)
{
	UDebugMessages::LogDisplay(this, "OnTrainingAddToProgressWidget");

	auto newProgressItem = CreateSupplyListItemWidget();

	newProgressItem->SetProgressValues(StartTime, EndTime, unitType, buildingId, amount);
	ProgressBox->AddChildToVerticalBox(newProgressItem);
	AddToProgressWidgets(newProgressItem);
}

UCityProgressItemWidget *UCityProgressWidget::CreateSupplyListItemWidget()
{
	FSoftClassPath hudUIRef(*ProgressItemWidgetRef);
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UCityProgressItemWidget>())
		return CreateWidget<UCityProgressItemWidget>(this, hudUIWidgetClass);

	return nullptr;
}