// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "CityProgressItemWidget.generated.h"

class UProgressBar;
class UTextBlock;
class IGatewayClient;

/**
 *
 */
UCLASS()
class ROV_API UCityProgressItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable) void SetProgressValues(FDateTime startTime, FDateTime finishTime, EBuildingType buildingType, FGuid buildingId);
	void SetProgressValues(FDateTime startTime, FDateTime finishTime, EROVUnitType buildingType, FGuid buildingId, int amount);

	void CalculateProgress();
	bool GetIsComplete();

protected:
	UPROPERTY(meta = (BindWidget)) UProgressBar* ProgressBar;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ProgressName;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ProgressTime;

	UPROPERTY() FDateTime StartTime;
	UPROPERTY() FDateTime FinishTime;
	UPROPERTY() EBuildingType BuildingType;
	UPROPERTY() FGuid Id;
	UPROPERTY() EROVUnitType UnitType;
	UPROPERTY() int Amount;

private:

	void CheckOnBuildingComplete();
	void CheckOnTrainingComplete();
	UPROPERTY() TScriptInterface<IGatewayClient> GatewayClient;

	UPROPERTY() bool bCheckingOnResult;
	UPROPERTY() bool bIsComplete;

};
