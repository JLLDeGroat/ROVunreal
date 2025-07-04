// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitAttackAmountItemWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "../../../../Utilities/WidgetUtils.h"

void UUnitAttackAmountItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    AttackSlider->OnValueChanged.AddDynamic(this, &UUnitAttackAmountItemWidget::OnSliderChange);
}

void UUnitAttackAmountItemWidget::SetupAttackAmountItem(EROVUnitType unitType, int amount)
{
    UnitType = unitType;
    MaxAmount = amount;
    RequestedAmount = 0;
    AttackSlider->SetValue(0);

    Title->SetText(FText::FromString(UWidgetUtils::GetUnitNameFromEnum(unitType)));
    MaxAttackAmount->SetText(FText::FromString(FString::SanitizeFloat(amount)));
    AttackAmount->SetText(FText::FromString("0"));
}

void UUnitAttackAmountItemWidget::OnSliderChange(float value)
{
    RequestedAmount = MaxAmount * value;
    AttackAmount->SetText(FText::FromString(FString::SanitizeFloat(RequestedAmount)));
}

int UUnitAttackAmountItemWidget::GetRequestAmount()
{
    return RequestedAmount;
}
EROVUnitType UUnitAttackAmountItemWidget::GetUnitType()
{
    return UnitType;
}