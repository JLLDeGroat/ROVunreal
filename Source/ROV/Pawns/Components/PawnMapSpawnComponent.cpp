// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnMapSpawnComponent.h"
#include "../../GameModes/MapGameMode.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Dtos/FCityOverviewDtos.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../../ROVPlayerController.h"
#include "PawnMapSlotSpawnerComponent.h"
// Sets default values for this component's properties
UPawnMapSpawnComponent::UPawnMapSpawnComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

void UPawnMapSpawnComponent::BeginPlay()
{
    Super::BeginPlay();

    auto world = GetWorld();
    if (!world)
        return UDebugMessages::LogError(this, "failed to get world");

    auto gameMode = world->GetAuthGameMode<AMapGameMode>();
    if (gameMode)
    {
        UDebugMessages::LogDisplay(this, "found map game mode, going to find spawn point");

        auto gameManager = UROVDataUtils::GetGameManager();
        auto city = gameManager->GetCityOverviewData();

        auto location = city->GetLocation();

        auto xLocation = location->GetX() * 50;
        auto yLocation = location->GetY() * 50;

        auto ownerPawnLocation = GetOwner()->GetActorLocation();
        auto locationToMoveTo = FVector(xLocation, yLocation, ownerPawnLocation.Z);

        GetOwner()->SetActorLocation(locationToMoveTo);
        UDebugMessages::LogDisplay(this, "moved to " + locationToMoveTo.ToString() +
                                             "X " + FString::SanitizeFloat(location->GetX()) + "& Y: " + FString::SanitizeFloat(location->GetY()));

        auto mapSpawnerComp = GetOwner()->GetComponentByClass<UPawnMapSlotSpawnerComponent>();
        check(mapSpawnerComp);

        mapSpawnerComp->SpawnSlotsAroundCityLoc(city->GetCityId(), location->GetX(), location->GetY());
    }
}
