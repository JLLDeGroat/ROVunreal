// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnMapSlotSpawnerComponent.generated.h"

class AMapSlot;
class URSpawnMapSlots;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROV_API UPawnMapSlotSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPawnMapSlotSpawnerComponent();

public:
	void SpawnSlotsAroundLoc(int x, int y);
	void SpawnSlotsAroundCityLoc(FString city, int x, int y);

	bool GetSlotAlreadyExists(int x, int y);
	void AddMapSlot(AMapSlot* slot);

	void CloseAllThreads();
protected:
	UPROPERTY()
	TArray<AMapSlot *> MapSlots;
	UPROPERTY()
	TArray<URSpawnMapSlots*> SlotThreads;
};
