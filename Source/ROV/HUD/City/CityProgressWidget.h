// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CityProgressWidget.generated.h"

class UVerticalBox;
class UCityProgressItemWidget;
/**
 *
 */
UCLASS()
class ROV_API UCityProgressWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCityProgressWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION() void UpdateProgressWidgetsCallback();
	UFUNCTION() void OnBuildingAddingToProgressWidget(FDateTime StartTime, FDateTime EndTime, EBuildingType BuildingType, FGuid BuildingId);
	UFUNCTION() void OnDeconstructingBuildingAddingToProgressWidget(FDateTime StartTime, FDateTime EndTime, EBuildingType BuildingType, FGuid BuildingId);
	UFUNCTION() void OnTrainingAddToProgressWidget(FDateTime StartTime, FDateTime EndTime, FGuid buildingId, EROVUnitType unitType, int amount);
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget)) UVerticalBox* ProgressBox;
	UPROPERTY() TArray<UCityProgressItemWidget*> ProgressWidgets;

	void AddToProgressWidgets(UCityProgressItemWidget* widget);

private:

	FTimerHandle UpdateProgressWidgetsHandle;
	void StartProgressWidgetsHandle();

	UPROPERTY() FString ProgressItemWidgetRef = "/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/ComponentWidgets/ProgressItem_Bp.ProgressItem_Bp_C'";

	UCityProgressItemWidget* CreateSupplyListItemWidget();
};


