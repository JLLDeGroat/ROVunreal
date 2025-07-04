// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCityWidget.h"
#include "../../../Delegates/MapUIDelegates.h"
#include "Components/TextBlock.h"
#include "../../../Entities/MapSlot.h"

void UPlayerCityWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerCityWidget::SetupForSlot(AMapSlot *slot)
{
    Super::SetupForSlot(slot);
    SetVisibility(ESlateVisibility::Visible);
}

void UPlayerCityWidget::SlotDetailsRecieved()
{
}