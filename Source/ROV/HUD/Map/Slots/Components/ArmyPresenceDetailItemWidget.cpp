// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmyPresenceDetailItemWidget.h"
#include "../../../../Delegates/MapUIDelegates.h"
#include "Components/TextBlock.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

void UArmyPresenceDetailItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UArmyPresenceDetailItemWidget::SetPresenceAmount(FString value)
{
    PresenceAmount->SetText(FText::FromString(value));
}
void UArmyPresenceDetailItemWidget::SetPresenceAmount(int amount)
{
    PresenceAmount->SetText(FText::FromString("x " + FString::SanitizeFloat(amount)));
}

void UArmyPresenceDetailItemWidget::SetImage(EROVUnitType unitType)
{
    // TODO:
    UDebugMessages::LogError(this, "Not IMPLEMENTED");
}