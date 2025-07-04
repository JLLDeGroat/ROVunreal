// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "BuildingUpgradeDetails.generated.h"

class UGridPanel;
class UButton;
class UResourceCostItemWidget;

UCLASS()
class ROV_API UBuildingUpgradeDetails : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void ClearUpgradeWidget();

	void SetBuildingId(FGuid buildingId) { BuildingId = buildingId; }
	void SetBuildingType(EBuildingType buildingType) { BuildingType = buildingType; }

	void AddResourceItemToUpdateDetails(UResourceCostItemWidget *costWidget);
	void AddResourceItemToUpdateDetails(EResourceType rType, FString name, int amount);

	void HideDeconstructBtn();
	void ShowDeconstructBtn();

	void HideUpgradeBtn();
	void ShowUpgradeBtn();

protected:
	UFUNCTION()
	void OnUpgradeClicked();

	UFUNCTION()
	void OnDeconstructClicked();

	void AddResourceItemToWidget(UResourceCostItemWidget *costWidget);

	UPROPERTY()
	TArray<UResourceCostItemWidget *> CostWidgets;

	UPROPERTY(meta = (BindWidget))
	UGridPanel *CostGridPanel;
	UPROPERTY(meta = (BindWidget))
	UButton *UpgradeBtn;
	UPROPERTY(meta = (BindWidget))
	UButton *DeconstructBtn;
	UPROPERTY()
	FGuid BuildingId;
	UPROPERTY()
	EBuildingType BuildingType;
};
