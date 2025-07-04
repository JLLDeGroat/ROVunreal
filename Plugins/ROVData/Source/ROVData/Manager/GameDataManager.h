// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Models/FROVModels.h"
#include "../Dtos/FGatewayClientDtos.h"
#include "../Dtos/FCityOverviewDtos.h"
#include "../Models/FROVGameConfig.h"
#include "../Interfaces/ROVGameData.h"
#include "GameDataManager.generated.h"

/**
 *
 */
UCLASS()
class ROVDATA_API UGameDataManager : public UObject, public IROVGameData
{
	GENERATED_BODY()

public:

	UGameDataManager(const FObjectInitializer& ObjectInitializer);

	FGameDataModel* GetGameData() { return &GameData; }
	void SetGameData(FGameDataModel* model) { GameData = FGameDataModel(*model); }

	FOverViewCityDto* GetCityOverviewData() { return &CityOverview; }
	void SetCityOverviewData(FOverViewCityDto* model) { CityOverview = FOverViewCityDto(*model); }

	virtual FROVGameConfig* GetGameConfig() { return &GameConfig; }
	virtual void SetGameConfig(FROVGameConfig* gameConfig) { GameConfig = FROVGameConfig(*gameConfig); }

	virtual FOverViewBuildingSlotDto* GetSlotOverviewByBuildingId(FGuid buildingId) override;
	virtual FOverViewBuildingSlotDto* GetSlotOverviewBySlotId(int slotId) override;

	virtual FOverViewBuildingDto* AddBuildingToSlot(int slotId, EBuildingType buildingType, FString id, int level) override;
	virtual void UpdateResourceItem(EResourceType resourceType, int amount) override;

	virtual FCityBonusGetListResponseDto* GetCityBonuses(FGuid cityId) override;
	virtual void AddCityBonuses(FGuid cityId, FCityBonusGetListResponseDto cityBonusDtos) override;

	void SetResourceRatesDto(FResourceRateResponseDto* ResourceRates) override;
	virtual FResourceRateResponseDto* GetResourceRates() override;
	virtual int GetHourlyAmount(int level, int tier) override;

	virtual void SetResourceTypes(FResourceTypesResponseDto* resourceRate) override;
	virtual int GetResourceTier(EResourceType rType) override;

	virtual void SetBuildingTypes(FBuildingTypesResponseDto* buildingTypes) override;
	virtual FBuildingTypeDto* GetBuildingType(EBuildingType buildingType) override;

	virtual FString GetBuildingDescription(EBuildingType buildingType) override;

protected:
	UPROPERTY() FGameDataModel GameData;
	UPROPERTY() FOverViewCityDto CityOverview;
	UPROPERTY() FROVGameConfig GameConfig;
	UPROPERTY() TMap<FGuid, FCityBonusGetListResponseDto> CityBonuses;
	UPROPERTY() FResourceRateResponseDto ResourceRates;
	UPROPERTY() FResourceTypesResponseDto ResourceTypes;
	UPROPERTY() FBuildingTypesResponseDto BuildingTypes;
};
