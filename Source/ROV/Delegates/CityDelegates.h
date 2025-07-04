// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "UObject/NoExportTypes.h"
#include "CityDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInitializeBuildingSlot, int, SlotId, EBuildingLevelMeshes, BuildingLevelMesh, EBuildingType, BuildingType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSuccessBuildBuilding, int, SlotId, EBuildingType, BuildingType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSuccessulBuildingUpgrade, int, SlotId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStartBuildingUpgrade, FGuid, BuildingId, FDateTime, Start, FDateTime, End);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllowUiReactions);

UCLASS()
class ROV_API UCityDelegates : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) static UCityDelegates* GetInstance() {
		static UCityDelegates* cityDelegates = 0; if (!cityDelegates)
		{
			cityDelegates = NewObject<UCityDelegates>();
			cityDelegates->AddToRoot();
		}
		return cityDelegates;
	}

	FOnInitializeBuildingSlot _OnInitializeBuildingSlot;
	FOnSuccessBuildBuilding _OnSuccessBuildBuilding;
	FOnSuccessulBuildingUpgrade _OnSuccessulBuildingUpgrade;
	FOnAllowUiReactions _OnAllowUiReactions;
	FOnStartBuildingUpgrade _OnStartBuildingUpgrade;
};