// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseBuildingDetailsWidget.generated.h"

class UTextBlock;
class UButton;
class IGatewayClient;
class UBuildingUpgradeDetails;
class UCityProgressItemWidget;

UCLASS()
class ROV_API UBaseBuildingDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void SetUpgradeWidgetVisibility(ESlateVisibility visibility);

	virtual void SetupForBuilding(AActor *buildingActor) {}

protected:
	UFUNCTION()
	virtual void HideWidget();

	void BaseSetup(AActor *actor);

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Title;
	UPROPERTY()
	AActor *BuildingActor;

	UPROPERTY(meta = (BindWidget))
	UButton *ExitButton;

	UPROPERTY()
	TScriptInterface<IGatewayClient> GatewayClient;

	UPROPERTY(meta = (BindWidget)) UBuildingUpgradeDetails* UpgradeWidget;

	UPROPERTY(meta = (BindWidget))
	UCityProgressItemWidget *ProgressItem;

	FTimerHandle UpdateProgressWidgetsHandle;
	void StartProgressWidgetsHandle();
	UFUNCTION() void UpdateProgressWidgetsCallback();
};
