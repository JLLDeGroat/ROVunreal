// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseSlotDetailsWidget.h"
#include "StartAttackWidget.generated.h"

class UTextBlock;
class UScrollBox;
struct FMapLocationOccupationDetailsResponseDto;
/**
 *
 */
UCLASS()
class ROV_API UStartAttackWidget : public UBaseSlotDetailsWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void StartAttackAtOccupiedLocation(FMapLocationOccupationDetailsResponseDto *occupation);

	void HideStartAttackWidget();

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock *AttackTitle;

	UPROPERTY(meta = (BindWidget))
	UScrollBox *UnitAmountList;
};
