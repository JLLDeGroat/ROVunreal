// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "BuildableBuildingItemWidget.generated.h"

class UBuildBuildingWidget;
class UTextBlock;
class UGridPanel;
class UResourceCostItemWidget;
class UButton;
/**
 *
 */
UCLASS()
class ROV_API UBuildableBuildingItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UBuildableBuildingItemWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable) void SetParentWidget(UBuildBuildingWidget* parent);
	UFUNCTION(BlueprintImplementableEvent) void ClearResourceCostItems();
	UFUNCTION(BlueprintCallable) void BuildClicked();

	void SetTitleAndDesc(EBuildingType bType, FString name, FString desc);
	void AddResourceItem(EResourceType rType, int amount);
protected:

	UFUNCTION(BlueprintCallable) int GetGridRow(int currentTotal);
	UFUNCTION(BlueprintCallable) int GetGridColumn(int currentTotal);

	UPROPERTY() UBuildBuildingWidget* ParentWidget;

	UPROPERTY(meta = (BindWidget)) UGridPanel* ResourceCostGrid;

	UPROPERTY(meta = (BindWidget)) EBuildingType BuildingType;
	UPROPERTY(meta = (BindWidget)) UTextBlock* BuildingName;
	UPROPERTY(meta = (BindWidget)) UTextBlock* BuildingDescription;
	UPROPERTY(meta = (BindWidget)) UButton* BuildButton;
	UPROPERTY() FString resourceCostRef = "/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/ComponentWidgets/ResourceCostItem_Bp.ResourceCostItem_Bp_C'";
	UResourceCostItemWidget* CreateResourceCostWidget();
};
