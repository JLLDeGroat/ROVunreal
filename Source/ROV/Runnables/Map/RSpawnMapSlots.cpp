// Fill out your copyright notice in the Description page of Project Settings.

#include "RSpawnMapSlots.h"
#include "Tasks/CheckSlotExistsTask.h"
#include "../../Pawns/Components/PawnMapSlotSpawnerComponent.h"
#include "../../Entities/MapSlot.h"

#pragma optimize("", off)
UBaseRunnable *URSpawnMapSlots::InsertVariables(UPawnMapSlotSpawnerComponent *spawnComponent, TArray<FLocationDto> locations)
{
    Locations = locations;
    SpawnComponent = spawnComponent;
    return this;
}

void URSpawnMapSlots::ActivateThread()
{
    int iteration = 0;
    for (auto loc : Locations)
    {
        if (!bIsAlive)
            return;

        iteration += 1;
        auto x = loc.GetX();
        auto y = loc.GetY();
        auto translatedX = x * 50;
        auto translatedY = y * 50;

        EOccupiedType occupiedType = EOccupiedType::INVALID;
        if (loc.GetOccupied())
            occupiedType = loc.GetOccupiedDetails()->GetOccupiedType();

        auto world = GetWorld();
        FVector spawnLocation = FVector(translatedX, translatedY, 0);
        auto spawnSlotComponent = SpawnComponent;

        auto uid = loc.GetUid();

        if (!LoadHasSlotAlready(spawnSlotComponent, x, y) && bIsAlive)
        {
            FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
                [world, spawnLocation, x, y, spawnSlotComponent, occupiedType, uid]
                {
                    if (!world)
                        return;

                    auto mapSlot = world->SpawnActor<AMapSlot>(spawnLocation, FRotator(0));
                    if (mapSlot)
                    {
                        mapSlot->SetXAndY(x, y);
                        mapSlot->SetupOccupation(occupiedType);
                        mapSlot->SetUid(uid);
                    }

                    if (spawnSlotComponent)
                        spawnSlotComponent->AddMapSlot(mapSlot);
                },
                TStatId(), nullptr, ENamedThreads::GameThread);

            if (iteration % 5 == 0)
            {
                FPlatformProcess::Sleep(.001f);
            }
        }
    }
}

bool URSpawnMapSlots::LoadHasSlotAlready(UPawnMapSlotSpawnerComponent *comp, int x, int y)
{
    bool exists = false;
    bool isComplete = false;
    TGraphTask<CheckSlotExistsTask>::CreateTask().ConstructAndDispatchWhenReady(comp, x, y, &exists, &isComplete);

    int iteration = 0;
    float secondsToWaitUntilGiveup = 5;
    float increment = .01f;
    while (!isComplete)
    {
        if (!bIsAlive)
            return false;

        FPlatformProcess::Sleep(increment);
        iteration += increment;

        if (iteration >= secondsToWaitUntilGiveup)
        {
            UDebugMessages::LogError(this, "failed to LoadHasSlotAlready, after " + FString::SanitizeFloat(secondsToWaitUntilGiveup) + " seconds");
            return false;
        }
    }

    return exists;
}
#pragma optimize("", on)