// Fill out your copyright notice in the Description page of Project Settings.

#include "AiCitySlotWidget.h"
#include "../../../Delegates/MapUIDelegates.h"
#include "Components/TextBlock.h"
#include "../../../Entities/MapSlot.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "Components/ArmyPresenceDetailsWidget.h"
#include "Components/Button.h"
#include "../../../Utilities/WidgetUtils.h"
#include "../MainMapWidget.h"
#include "StartAttackWidget.h"

void UAiCitySlotWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetVisibility(ESlateVisibility::Hidden);

    SpyButton->OnClicked.AddDynamic(this, &UAiCitySlotWidget::OnSpyClicked);
    AttackButton->OnClicked.AddDynamic(this, &UAiCitySlotWidget::OnAttackClicked);
}

void UAiCitySlotWidget::SetupForSlot(AMapSlot *slot)
{
    Super::SetupForSlot(slot);
    SetVisibility(ESlateVisibility::Visible);

    ArmyPresenceWidget->AddPresenceItem(EROVUnitType::Peasant, 10);
}

#pragma optimize("", off)
void UAiCitySlotWidget::SlotDetailsRecieved()
{
    UDebugMessages::LogDisplay(this, "WOOP WOOP");

    Title->SetText(FText::FromString(OccupationDetails.GetName()));

    for (auto garrisonItem : OccupationDetails.GetGarrison())
    {
        UDebugMessages::LogDisplay(this, "garrisonItemDesc: " + garrisonItem.GetAmountDescription());
        ArmyPresenceWidget->AddPresenceItem(garrisonItem.GetUnitType(), garrisonItem.GetAmountDescription());
    }
}

void UAiCitySlotWidget::OnSpyClicked()
{
    UDebugMessages::LogError(this, "on spy clicked");
}
void UAiCitySlotWidget::OnAttackClicked()
{
    UDebugMessages::LogDisplay(this, "on attack clicked");

    auto widget = UWidgetUtils::GetMainMapWidget(this);
    auto attackWidget = widget->GetStartAttackWidget();

    attackWidget->StartAttackAtOccupiedLocation(&OccupationDetails);
    SetVisibility(ESlateVisibility::Hidden);
}
#pragma optimize("", on)