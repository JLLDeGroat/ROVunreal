// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelChangeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "Kismet/GameplayStatics.h"
#include "../../GameModes/MapGameMode.h"
#include "../../GameModes/CityGameMode.h"

void ULevelChangeWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    LevelText->SetText(FText::FromString("World"));
    LevelBtn->OnClicked.AddDynamic(this, &ULevelChangeWidget::OnLevelBtnClicked);
}

void ULevelChangeWidget::OnLevelBtnClicked()
{
    UDebugMessages::LogDisplay(this, "OnLevelBtnClicked clicked");

    auto world = GetWorld();
    auto currentGameMode = world->GetAuthGameMode();

    if (currentGameMode->IsA<ACityGameMode>())
    {
        FName lName = FName("World");
        UGameplayStatics::OpenLevel(this, lName, true, "game=Class'/Script/ROV.MapGameMode'?");
    }
    else
    {
        FName lName = FName("City");
        UGameplayStatics::OpenLevel(this, lName, true, "game=Class'/Script/ROV.CityGameMode'?");
    }
}