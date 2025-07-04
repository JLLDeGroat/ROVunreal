// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Dtos/FResourceDtos.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "UObject/NoExportTypes.h"
#include "UIDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoginJourneyComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmptySlotClicked, int, SlotId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnBuildingBeginConstruction, FDateTime, StartTime, FDateTime, EndTime, EBuildingType, BuildingType, FGuid, BuildingId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnBuildingBeginDeConstruction, FDateTime, StartTime, FDateTime, EndTime, EBuildingType, BuildingType, FGuid, BuildingId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnTraininBeginProgress, FDateTime, StartTime, FDateTime, EndTime, FGuid, BuildingId, EROVUnitType, UnitType, int,Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestUpdatedResourceCount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateResources, FResourceGetCityAmountResponseDto, CityAmountResponseDto);

UCLASS()
class ROV_API UUIDelegates : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UUIDelegates *GetInstance()
	{
		static UUIDelegates *uiDelegates = 0;
		if (!uiDelegates)
		{
			uiDelegates = NewObject<UUIDelegates>();
			uiDelegates->AddToRoot();
		}
		return uiDelegates;
	}

	FOnLoginJourneyComplete _OnLoginJourneyComplete;
	FOnEmptySlotClicked _OnEmptySlotClicked;
	FOnBuildingBeginConstruction _OnBuildingBeginConstruction;
	FOnBuildingBeginDeConstruction _OnBuildingBeginDeConstruction;
FOnTraininBeginProgress _OnTraininBeginProgress;
	// public, use this to request up to date resource information
	FOnRequestUpdatedResourceCount _OnRequestUpdatedResourceCount;

	// this is private, and only used within the ACityManagerActor class
	FOnUpdateResources _OnUpdateResources;
};
