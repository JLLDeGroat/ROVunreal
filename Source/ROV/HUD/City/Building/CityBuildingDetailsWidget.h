// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseBuildingDetailsWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "CityBuildingDetailsWidget.generated.h"

class UGridPanel;
class UUnitDetailItem;
/**
 *
 */
UCLASS()
class ROV_API UCityBuildingDetailsWidget : public UBaseBuildingDetailsWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	virtual void SetupForBuilding(AActor *buildingActor) override;

protected:
	UPROPERTY(meta = (BindWidget))
	UGridPanel *UnitDetailsPanel;

	UPROPERTY()
	TArray<UUnitDetailItem *> UnitDetailWidgets;

	UUnitDetailItem *GetUnitDetailItem(EROVUnitType unitType);
	void PlaceUnitDetailsInWidget(UUnitDetailItem * widgetItem);
};
