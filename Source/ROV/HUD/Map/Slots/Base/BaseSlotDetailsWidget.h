// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Dtos/FWorldDtos.h"
#include "BaseSlotDetailsWidget.generated.h"

class AMapSlot;
class UButton;

/**
 *
 */
UCLASS()
class ROV_API UBaseSlotDetailsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    virtual void SetupForSlot(AMapSlot *slot);
    virtual void SlotDetailsRecieved();

protected:
    UPROPERTY(meta = (BindWidget))
    UButton *CloseButton;

    UFUNCTION()
    void HideWidget();

    UPROPERTY()
    AMapSlot *CurrentSlot;

    UPROPERTY() 
    FMapLocationOccupationDetailsResponseDto OccupationDetails;
};
