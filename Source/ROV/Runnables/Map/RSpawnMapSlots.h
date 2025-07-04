// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/BaseRunnable.h"
#include "ROVData/Dtos/FWorldDtos.h"
#include "RSpawnMapSlots.generated.h"

class UPawnMapSlotSpawnerComponent;
/**
 *
 */
UCLASS()
class ROV_API URSpawnMapSlots : public UBaseRunnable
{
    GENERATED_BODY()

public:
    virtual void ActivateThread() override;
    UBaseRunnable *InsertVariables(UPawnMapSlotSpawnerComponent *spawnComponent, TArray<FLocationDto> locations);

protected:
    bool LoadHasSlotAlready(UPawnMapSlotSpawnerComponent* comp, int x, int y);    

UPROPERTY()
    TArray<FLocationDto> Locations;

    UPROPERTY()
    UPawnMapSlotSpawnerComponent *SpawnComponent;
};
