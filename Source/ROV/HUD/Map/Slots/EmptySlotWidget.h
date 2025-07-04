// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseSlotDetailsWidget.h"
#include "EmptySlotWidget.generated.h"

class UTextBlock;
class UArmyPresenceDetailsWidget;
class UImage;
class AMapSlot;
/**
 *
 */
UCLASS()
class ROV_API UEmptySlotWidget : public UBaseSlotDetailsWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void SetupForSlot(AMapSlot *slot) override;
	virtual void SlotDetailsRecieved() override;

protected:
};
