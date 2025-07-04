// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "UnitAttackAmountItemWidget.generated.h"

class UTextBlock;
class USlider;
/**
 *
 */
UCLASS()
class ROV_API UUnitAttackAmountItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void SetupAttackAmountItem(EROVUnitType unitType, int amount);

	int GetRequestAmount();
	EROVUnitType GetUnitType();

protected:
	UPROPERTY()
	EROVUnitType UnitType;

	UPROPERTY()
	int MaxAmount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Title;
	UPROPERTY(meta = (BindWidget))
	UTextBlock *AttackAmount;
	UPROPERTY(meta = (BindWidget))
	UTextBlock *MaxAttackAmount;
	UPROPERTY(meta = (BindWidget))
	USlider *AttackSlider;

	UFUNCTION()
	void OnSliderChange(float value);

	UPROPERTY()
	int RequestedAmount;
};
