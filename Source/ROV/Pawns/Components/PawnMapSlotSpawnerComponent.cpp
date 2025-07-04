// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnMapSlotSpawnerComponent.h"
#include "../../Domain/Client/ROVMapClient.h"
#include "ROVData/Dtos/FWorldDtos.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../../Entities/MapSlot.h"
#include "../../Runnables/Map/RSpawnMapSlots.h"
#include "../../Delegates/MapUIDelegates.h"

// Sets default values for this component's properties
UPawnMapSlotSpawnerComponent::UPawnMapSlotSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPawnMapSlotSpawnerComponent::SpawnSlotsAroundLoc(int x, int y)
{
	auto delegates = UMapUIDelegates::GetInstance();
	if (delegates)
		delegates->_OnMapLocationChange.Broadcast(x, y);

	auto client = NewObject<UROVMapClient>(this);
	client->GetLocationsAroundLocation(
		x, y, 10, [this](FGenericApiResponse responseDto)
		{
			auto payload = responseDto.GetPayload();

			FMapLocationAroundLocationResponseDto dto;
			if (UFileManagementUtilities::JsonToStruct(responseDto.GetPayload(), &dto))
			{
				auto obj = (URSpawnMapSlots*)NewObject<URSpawnMapSlots>()
					->InsertVariables(this, dto.GetLocations())	
					->Initialise(GetWorld())
					->Begin();
					SlotThreads.Emplace(obj);
			}
			else{
				UDebugMessages::LogDisplay(this, "failed");
			} });
	// client->GetInitialMapLocation()
}
#pragma optimize("", off)
void UPawnMapSlotSpawnerComponent::SpawnSlotsAroundCityLoc(FString city, int x, int y)
{
	auto delegates = UMapUIDelegates::GetInstance();
	if (delegates)
		delegates->_OnMapLocationChange.Broadcast(x, y);

	auto client = NewObject<UROVMapClient>(this);
	client->GetInitialMapLocation(
		city, 10, [this](FGenericApiResponse responseDto)
		{
			auto payload = responseDto.GetPayload();

			FMapLocationAroundCityResponseDto dto;
			if (UFileManagementUtilities::JsonToStruct(responseDto.GetPayload(), &dto))
			{
				auto obj = (URSpawnMapSlots*)NewObject<URSpawnMapSlots>()
					->InsertVariables(this, dto.GetLocations())	
					->Initialise(GetWorld())
					->Begin();

				SlotThreads.Emplace(obj);
			}
			else{
				UDebugMessages::LogDisplay(this, "failed");
			} });
}

bool UPawnMapSlotSpawnerComponent::GetSlotAlreadyExists(int x, int y)
{
	for (auto slot : MapSlots)
	{
		if (!IsValid(this))
			return false;

		if (!slot)
			continue;

		if (x == slot->GetX() && y == slot->GetY())
			return true;
	}

	return false;
}

void UPawnMapSlotSpawnerComponent::AddMapSlot(AMapSlot *slot)
{
	MapSlots.Emplace(slot);
}

void UPawnMapSlotSpawnerComponent::CloseAllThreads()
{
	for (auto thread : SlotThreads)
		if (thread)
			thread->EnsureCompletion();
}

#pragma optimize("", on)
