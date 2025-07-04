// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildBuildingWidget.generated.h"

class IGatewayClient;
class UResourceCostItemWidget;
class UButton;
class UBuildableBuildingItemWidget;
class UScrollBox;
/**
 *
 */
UCLASS()
class ROV_API UBuildBuildingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UBuildBuildingWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeOnInitialized() override;

	void AttemptToBuildBuilding(uint8 buildingType);

protected:

	UFUNCTION() void OnAttemptCallback(FString content);

	UFUNCTION() void EmptySlotClicked(int32 SlotId);
	UFUNCTION() void OnGetSlotContents(FString content);

	UFUNCTION(BlueprintImplementableEvent) void AddBuildableItem(UBuildBuildingWidget* widget, uint8 buildingType, const FString& Name, const FString& Desc);
	UFUNCTION(BlueprintImplementableEvent) void AddResourceToBuildableItem(uint8 resourceType, int amount);
	UFUNCTION(BlueprintImplementableEvent) void FinishBuildableItem();

	UFUNCTION() void HideWidget();

	UPROPERTY(meta = (BindWidget)) UButton* ExitButton;
	UPROPERTY(meta = (BindWidget)) UScrollBox* BuildableScroll;
private:

	UPROPERTY() TArray<UBuildableBuildingItemWidget*> BuildableBuildings;
	UBuildableBuildingItemWidget* CreateBuildingItemWidget();
	UResourceCostItemWidget* CreateResourceCostWidget();
	UPROPERTY() FString resourceCostRef = "/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/ComponentWidgets/ResourceCostItem_Bp.ResourceCostItem_Bp_C'";
	UPROPERTY() FString buildingItemRef = "/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/ComponentWidgets/BuildableBuildingItem_Bp.BuildableBuildingItem_Bp_C'";
	UPROPERTY() bool BuildablesAdded;
	UPROPERTY() int CurrentSlot;
	UPROPERTY() TScriptInterface<IGatewayClient> GatewayClient;

};
