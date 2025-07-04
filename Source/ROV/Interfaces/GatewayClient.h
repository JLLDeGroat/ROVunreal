// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "CoreMinimal.h"
#include "ROVData/Enums/ROVEnums.h"
#include "GatewayClient.generated.h"

struct FOverviewCityRequestDto;
struct FBuildingBuildRequestDto;
struct FApiDto;
/**
 *
 */
UINTERFACE(BlueprintType)
class ROV_API UGatewayClient : public UInterface
{
	GENERATED_BODY()
public:
};

class ROV_API IGatewayClient
{
	GENERATED_BODY()
public:
	virtual void SetToken(FString token) = 0;
	virtual void SetApiKey(FString key) = 0;

	virtual void Initialise(FString deviceId, TFunction<void(FString content)> callBack) = 0;
	virtual void Login(FString deviceId, TFunction<void(FString content)> callBack) = 0;
	virtual void Authorise(TFunction<void(FString content)> callBack) = 0;

	virtual void CityOverview(FOverviewCityRequestDto *requestDto, TFunction<void(FString content)> callBack) = 0;

	virtual void AttemptToBuild(FBuildingBuildRequestDto *requestDto, TFunction<void(FString content)> callBack) = 0;

	virtual void GetSlotContents(FString cityId, TFunction<void(FString content)> callBack) = 0;

	virtual void GetCityResources(FString cityId, TFunction<void(FString content)> callBack) = 0;

	virtual void GetBuildingDetails(FString cityId, FString buildingId, TFunction<void(FString content)> callBack) = 0;
	virtual void GetCityBonuses(FString cityId, TFunction<void(FString content)> callback) = 0;

	virtual void UpgradeBuilding(FString buildingId, FString cityId, TFunction<void(FString content)> callBack) = 0;
	virtual void DeconstructBuilding(FString buildingId, FString cityId, TFunction<void(FString content)> callBack)=0;

	virtual void GetCityUpgradeDetails(FString cityId, TFunction<void(FString content)> callBack) = 0;
	virtual void StartCityUpgrade(FString cityId, TFunction<void(FString content)> callBack) = 0;

	virtual FApiDto *GetResultAsApiDto(FString content, FApiDto *apiDto) = 0;
	virtual FApiDto *GetResultAsApiDtoWithStringResult(FString content, FApiDto *apiDto) = 0;

	virtual void GetBuildingTrainableUnits(EBuildingType buildingType, FGuid buildingId, TFunction<void(FString content)> callBack) = 0;
	virtual void GetBuildingTrainableUnits(EBuildingType buildingType, TFunction<void(FString content)> callBack) = 0;

	virtual void GetBuildingUpgradeCosts(FString cityId, FString buildingId, TFunction<void(FString content)> callBack) = 0;

	virtual void GetResourceRates(TFunction<void(FString content)> callback) = 0;
	virtual void GetResourceTypes(TFunction<void(FString content)> callback) = 0;
	virtual void GetBuildingTypes(TFunction<void(FString content)> callback) = 0;

	virtual void AttemptToTrainUnits(FString cityId, FString buildingId, int amount, EROVUnitType unitType, TFunction<void(FString content)> callback) = 0;
};
