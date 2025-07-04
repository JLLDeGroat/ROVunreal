// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Enums/ROVEnums.h"
#include "../Enums/ROVUtilEnums.h"
#include "ROVGameData.generated.h"

struct FGameDataModel;
struct FOverViewCityDto;
struct FROVGameConfig;
struct FOverViewBuildingSlotDto;
struct FOverViewBuildingDto;
struct FCityBonusGetListResponseDto;
struct FResourceRateResponseDto;
struct FResourceTypesResponseDto;
struct FBuildingTypesResponseDto;
struct FBuildingTypeDto;
/**
 *
 */
UINTERFACE(BlueprintType)
class ROVDATA_API UROVGameData : public UInterface
{
	GENERATED_BODY()
public:
};

class ROVDATA_API IROVGameData {
	GENERATED_BODY()
public:

	virtual FGameDataModel* GetGameData() = 0;
	virtual void SetGameData(FGameDataModel* gameData) = 0;

	virtual FOverViewCityDto* GetCityOverviewData() = 0;
	virtual void SetCityOverviewData(FOverViewCityDto* overviewData) = 0;

	virtual FROVGameConfig* GetGameConfig() = 0;
	virtual void SetGameConfig(FROVGameConfig* gameConfig) = 0;

	virtual FOverViewBuildingSlotDto* GetSlotOverviewByBuildingId(FGuid buildingId) = 0;
	virtual FOverViewBuildingSlotDto* GetSlotOverviewBySlotId(int slotId) = 0;

	virtual FOverViewBuildingDto* AddBuildingToSlot(int slotId, EBuildingType buildingType, FString id, int level) = 0;

	virtual void UpdateResourceItem(EResourceType resourceType, int amount) = 0;

	virtual FCityBonusGetListResponseDto* GetCityBonuses(FGuid cityId) = 0;
	virtual void AddCityBonuses(FGuid cityId, FCityBonusGetListResponseDto cityBonusDtos) = 0;

	virtual void SetResourceRatesDto(FResourceRateResponseDto* ResourceRates) = 0;
	virtual FResourceRateResponseDto* GetResourceRates() = 0;
	virtual int GetHourlyAmount(int level, int tier) = 0;

	virtual void SetResourceTypes(FResourceTypesResponseDto* resourceRate) = 0;
	virtual int GetResourceTier(EResourceType rType) = 0;

	virtual void SetBuildingTypes(FBuildingTypesResponseDto* buildingTypes) = 0;
	virtual FBuildingTypeDto* GetBuildingType(EBuildingType buildingType) = 0;

	virtual FString GetBuildingDescription(EBuildingType buildingType) = 0;
};


