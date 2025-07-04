// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "UnitDetailItem.generated.h"

class IGatewayClient;
class UImage;
class UTextBlock;

/**
 *
 */
UCLASS()
class ROV_API UUnitDetailItem : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void SetupItem(int amount, EROVUnitType unitType);

	void SetUnitAmount(int amount);
	void SetUnitType(EROVUnitType unitType);

	int GetUnitAmount() { return Amount; }
	EROVUnitType GetUnitType() { return UnitType; }

protected:
	UPROPERTY(meta = (Bindwidget))
	UImage *UnitImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock *UnitAmount;

	UPROPERTY()
	EROVUnitType UnitType;
	UPROPERTY()
	int Amount;
};
