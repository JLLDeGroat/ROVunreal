// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseROVClient.h"
#include "../../Interfaces/GatewayClient.h"
#include "ROVClient.generated.h"

struct FOverviewCityRequestDto;
struct FBuildingBuildRequestDto;
/**
 *
 */
UCLASS()
class ROV_API UROVClient : public UBaseROVClient, public IGatewayClient
{
	GENERATED_BODY()
public:
	UROVClient();

	virtual void SetApiKey(FString key) override { _apiKey = key; }
	virtual void SetToken(FString token) override { _token = token; }

	virtual void Initialise(FString deviceId, TFunction<void(FString content)> callBack) override;
	virtual void Login(FString deviceId, TFunction<void(FString content)> callBack) override;
	virtual void Authorise(TFunction<void(FString content)> callBack) override;
	virtual void CityOverview(FOverviewCityRequestDto *requestDto, TFunction<void(FString content)> callBack) override;
	virtual void AttemptToBuild(FBuildingBuildRequestDto *requestDto, TFunction<void(FString content)> callBack) override;
	virtual void GetSlotContents(FString cityId, TFunction<void(FString content)> callBack) override;
	virtual void GetCityResources(FString cityId, TFunction<void(FString content)> callBack) override;
	virtual void GetBuildingDetails(FString cityId, FString buildingId, TFunction<void(FString content)> callBack) override;
	virtual void GetCityBonuses(FString cityId, TFunction<void(FString content)> callback) override;
	virtual void GetBuildingTrainableUnits(EBuildingType buildingType, FGuid buildingId, TFunction<void(FString content)> callBack) override;
	virtual void GetBuildingTrainableUnits(EBuildingType buildingType, TFunction<void(FString content)> callBack) override;
	virtual void UpgradeBuilding(FString buildingId, FString cityId, TFunction<void(FString content)> callBack) override;
	virtual void DeconstructBuilding(FString buildingId, FString cityId, TFunction<void(FString content)> callBack) override;
	virtual void GetResourceRates(TFunction<void(FString content)> callback) override;
	virtual void GetResourceTypes(TFunction<void(FString content)> callback) override;
	virtual void GetBuildingTypes(TFunction<void(FString content)> callback) override;

	virtual void AttemptToTrainUnits(FString cityId, FString buildingId, int amount, EROVUnitType unitType, TFunction<void(FString content)> callback) override;

	virtual void GetBuildingUpgradeCosts(FString cityId, FString buildingId, TFunction<void(FString content)> callBack) override;

	virtual void GetCityUpgradeDetails(FString cityId, TFunction<void(FString content)> callBack) override;
	virtual void StartCityUpgrade(FString cityId, TFunction<void(FString content)> callBack) override;

	virtual FApiDto *GetResultAsApiDto(FString content, FApiDto *apiDto) override;
	virtual FApiDto *GetResultAsApiDtoWithStringResult(FString content, FApiDto *apiDto) override;

private:
	
};
