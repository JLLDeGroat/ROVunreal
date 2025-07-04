// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseSlotDetailsWidget.h"
#include "AiCitySlotWidget.generated.h"

class UTextBlock;
class UArmyPresenceDetailsWidget;
class UImage;
class AMapSlot;
class UButton;
/**
 *
 */
UCLASS()
class ROV_API UAiCitySlotWidget : public UBaseSlotDetailsWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
    virtual void SetupForSlot(AMapSlot* slot) override;
	virtual void SlotDetailsRecieved() override;
protected:
	UPROPERTY(meta = (BindWidget))
	UArmyPresenceDetailsWidget *ArmyPresenceWidget;

	UPROPERTY(meta = (BindWidget))
	UImage *BuildingImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Title;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Description;

	UPROPERTY(meta= (BindWidget))
	UButton* SpyButton;

	UPROPERTY(meta= (BindWidget))
	UButton* AttackButton;

	UFUNCTION() void OnSpyClicked();
	UFUNCTION() void OnAttackClicked();
};
