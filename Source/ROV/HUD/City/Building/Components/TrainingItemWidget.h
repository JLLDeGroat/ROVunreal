// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "TrainingItemWidget.generated.h"

class IGatewayClient;
class UImage;
class UTextBlock;
class USlider;
class UResourceCostItemWidget;
class UGridPanel;
class UButton;
/**
 *
 */
UCLASS()
class ROV_API UTrainingItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	void SetUnitName(FString name);
	void SetUnitType(EROVUnitType unitType);
	void SetBuildingId(FGuid id);
	void AddResourceCost(int amount, EResourceType rType);
	void SetupMaxAmounts();
protected:

	UPROPERTY() TArray<UResourceCostItemWidget*> ResourceCostItems;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Title;

	UPROPERTY(meta = (BindWidget)) UTextBlock* TrainAmount;
	UPROPERTY(meta = (BindWidget)) UTextBlock* MaxTrainAmount;
	UPROPERTY(meta = (BindWidget)) USlider* TrainSlider;
	UPROPERTY(meta = (BindWidget)) UGridPanel* CostGrid;
	UPROPERTY(meta = (BindWidget)) UButton* TrainButton;

	UFUNCTION() void OnSliderChange(float value);
	UFUNCTION() void AttemptTraining();

private:

	UPROPERTY() FString resourceCostRef = "/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/ComponentWidgets/ResourceCostItem_Bp.ResourceCostItem_Bp_C'";
	UResourceCostItemWidget* CreateResourceCostWidget();

	UPROPERTY() int RequestedAmount;
	UPROPERTY() int MaxAmountAllowed;
	UPROPERTY() EROVUnitType UnitType;
	UPROPERTY() TScriptInterface<IGatewayClient> GatewayClient;
	UPROPERTY() FGuid BuildingId;
};
