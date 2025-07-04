// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmyPresenceDetailsWidget.h"
#include "../../../../Delegates/MapUIDelegates.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "ArmyPresenceDetailItemWidget.h"
#include "../../../../Utilities/WidgetUtils.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

void UArmyPresenceDetailsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UArmyPresenceDetailsWidget::AddPresenceItem(EROVUnitType unitType, int amount)
{
    auto item = UWidgetUtils::CreateArmyPresenceDetailItem(this);
    auto boxToUse = GetNextInsertion();
    boxToUse->AddChildToVerticalBox(item);
    item->SetPresenceAmount(amount);

    UDebugMessages::LogDisplay(this, "added presence Item");
}
void UArmyPresenceDetailsWidget::AddPresenceItem(EROVUnitType unitType, FString description)
{
    auto item = UWidgetUtils::CreateArmyPresenceDetailItem(this);
    auto boxToUse = GetNextInsertion();
    boxToUse->AddChildToVerticalBox(item);
    item->SetPresenceAmount(description);

    UDebugMessages::LogDisplay(this, "added presence Item");
}

UVerticalBox *UArmyPresenceDetailsWidget::GetNextInsertion()
{
    auto leftCount = LeftList->GetChildrenCount();
    auto rightCount = RightList->GetChildrenCount();

    if (leftCount > rightCount)
        return RightList;
    else
        return LeftList;
}