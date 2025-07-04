// Fill out your copyright notice in the Description page of Project Settings.

#include "MapDetailsWidget.h"
#include "../../../Delegates/MapUIDelegates.h"
#include "Components/TextBlock.h"

void UMapDetailsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    auto delegates = UMapUIDelegates::GetInstance();
    if (delegates)
    {
        delegates->_OnMapLocationChange.AddDynamic(this, &UMapDetailsWidget::OnLocationChanged);
    }
}

void UMapDetailsWidget::OnLocationChanged(int x, int y)
{
    LocationX->SetText(FText::FromString("X: " + FString::SanitizeFloat(x)));
    LocationY->SetText(FText::FromString("Y: " + FString::SanitizeFloat(y)));
}