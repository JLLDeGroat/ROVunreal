// Fill out your copyright notice in the Description page of Project Settings.

#include "StartAttackWidget.h"
#include "ROVData/Dtos/FWorldDtos.h"
#include "Components/TextBlock.h"
#include "../../../Utilities/WidgetUtils.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Dtos/FCityOverviewDtos.h"
#include "ROVData/Manager/GameDataManager.h"
#include "Components/ScrollBox.h"
#include "Components/UnitAttackAmountItemWidget.h"
#include "Components/Button.h"

void UStartAttackWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetVisibility(ESlateVisibility::Hidden);
}

void UStartAttackWidget::StartAttackAtOccupiedLocation(FMapLocationOccupationDetailsResponseDto *occupation)
{
    SetVisibility(ESlateVisibility::Visible);

    AttackTitle->SetText(FText::FromString("Attacking lvl " + FString::SanitizeFloat(occupation->GetAiLevel()) + " city " + occupation->GetName()));

    auto gameManager = UROVDataUtils::GetGameManager();
    auto city = gameManager->GetCityOverviewData();

    for (auto unit : city->GetGarrison()->GetArmy()->GetUnits())
    {
        auto widget = UWidgetUtils::CreateArmyAttackItem(this);
        widget->SetupAttackAmountItem(unit.GetUnitType(), unit.GetAmount());
        UnitAmountList->AddChild(widget);
    }
}