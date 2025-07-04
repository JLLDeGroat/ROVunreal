// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Enums/ROVEnums.h"
#include "FBuildingDtos.h"
#include "FCityOverviewDtos.h"
#include "FBaseDtos.h"
#include "FUnitDtos.h"
#include "FCityUpgradeDtos.h"
#include "FGatewayClientDtos.generated.h"

/**
 *
 */
USTRUCT()
struct FAccountCreateResponseDto
{
	GENERATED_BODY()
public:
	FAccountCreateResponseDto()
	{
		username = "";
		email = "";
		apiKey = "";
		uid = "";
	}

	FString GetUsername() { return username; }
	FString GetApiKey() { return apiKey; }
	FString GetEmail() { return email; }
	FString GetUid() { return uid; }

protected:
	UPROPERTY()
	FString username;
	UPROPERTY()
	FString email;
	UPROPERTY()
	FString apiKey;
	UPROPERTY()
	FString uid;
};

USTRUCT()
struct FApiDto
{
	GENERATED_BODY()
public:
	FApiDto()
	{
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FString GetPayload() { return Payload; }

	void SetPayLoad(FString payload) { Payload = payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FString Payload;
};

USTRUCT()
struct FOverViewCityApiDto
{
	GENERATED_BODY()
public:
	FOverViewCityApiDto()
	{
		Error = "";
		Success = false;
		Payload = FOverViewCityDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FOverViewCityDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	// UPROPERTY() FString Payload;
	UPROPERTY()
	FOverViewCityDto Payload;
};

USTRUCT()
struct FBuildingSlotContentsApiDto
{
	GENERATED_BODY()
public:
	FBuildingSlotContentsApiDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingSlotBuildingsResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingSlotBuildingsResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingSlotBuildingsResponseDto Payload;
};

USTRUCT()
struct FCityBonusGetListResponseApiDto
{
	GENERATED_BODY()
public:
	FCityBonusGetListResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FCityBonusGetListResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FCityBonusGetListResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FCityBonusGetListResponseDto Payload;
};

USTRUCT()
struct FResourceRateResponseApiDto
{
	GENERATED_BODY()
public:
	FResourceRateResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FResourceRateResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FResourceRateResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FResourceRateResponseDto Payload;
};

USTRUCT(BlueprintType)
struct FResourceTypeDto
{
	GENERATED_BODY()

	// Constructor
	FResourceTypeDto()
		: Tier(0), ResourceType(EResourceType::INVALID) // Assuming Default is a value in EResourceType
		  ,
		  DefaultMaxAmount(0)
	{
	}

	int GetTier() { return Tier; }
	EResourceType GetResourceType() { return ResourceType; }
	int GetDefaultMaxAmount() { return DefaultMaxAmount; }

protected:
	UPROPERTY()
	int Tier;
	UPROPERTY()
	EResourceType ResourceType;
	UPROPERTY()
	int DefaultMaxAmount;
};

USTRUCT(BlueprintType)
struct FResourceTypesResponseDto
{
	GENERATED_BODY()

	// Constructor
	FResourceTypesResponseDto()
	{
	}

	TArray<FResourceTypeDto> GetResourceTypes() { return ResourceTypes; }

protected:
	UPROPERTY()
	TArray<FResourceTypeDto> ResourceTypes;
};

USTRUCT()
struct FResourceTypesResponseApiDto
{
	GENERATED_BODY()
public:
	FResourceTypesResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FResourceTypesResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FResourceTypesResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FResourceTypesResponseDto Payload;
};

USTRUCT()
struct FBuildingTypesResponseApiDto
{
	GENERATED_BODY()
public:
	FBuildingTypesResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingTypesResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingTypesResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingTypesResponseDto Payload;
};

USTRUCT()
struct FBuildingTrainingDetailsRequestDto
{
	GENERATED_BODY()
public:
	FBuildingTrainingDetailsRequestDto()
	{
		BuildingType = 0;
	}

	void SetBuildingType(EBuildingType buildingType) { BuildingType = (uint8)buildingType; }

	void SetBuildingId(FGuid guid) { BuildingId = FBase::ToString(guid); }

protected:
	UPROPERTY()
	uint8 BuildingType;
	UPROPERTY()
	FString BuildingId;
};

USTRUCT()
struct FTrainingTrainableUnitDto
{
	GENERATED_BODY()
public:
	FTrainingTrainableUnitDto()
	{
	}
	TArray<FResourceDto> GetUnitCosts() { return UnitCosts; }
	EROVUnitType GetUnitType() { return UnitType; }

protected:
	UPROPERTY()
	TArray<FResourceDto> UnitCosts;
	UPROPERTY()
	EROVUnitType UnitType;
};

USTRUCT()
struct FBuildingTrainingDetailsResponseDto
{
	GENERATED_BODY()
public:
	FBuildingTrainingDetailsResponseDto()
	{
	}

	TArray<FTrainingTrainableUnitDto> GetTrainableUnits() { return TrainableUnits; }

protected:
	UPROPERTY()
	TArray<FTrainingTrainableUnitDto> TrainableUnits;
};

USTRUCT()
struct FBuildingTrainingDetailsResponseApiDto
{
	GENERATED_BODY()
public:
	FBuildingTrainingDetailsResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingTrainingDetailsResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingTrainingDetailsResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingTrainingDetailsResponseDto Payload;
};

USTRUCT()
struct FTrainingGetQueueReseponseApiDto
{
	GENERATED_BODY()
public:
	FTrainingGetQueueReseponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FOverviewTrainingQueueDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FOverviewTrainingQueueDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FOverviewTrainingQueueDto Payload;
};

USTRUCT()
struct FTrainingStartTrainingRequestDto
{
	GENERATED_BODY()
public:
	FTrainingStartTrainingRequestDto()
	{
	}

	void SetCityId(FString cityId) { CityId = cityId; }
	void SetBuildingId(FString buildingId) { BuildingId = buildingId; }
	void SetAmount(int amount) { Amount = amount; }
	void SetUnitType(EROVUnitType unitType) { UnitType = (uint8)unitType; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	FString BuildingId;
	UPROPERTY()
	int Amount;
	UPROPERTY()
	uint8 UnitType;
};

USTRUCT(BlueprintType)
struct FOverviewProgressItemDto
{
	GENERATED_BODY()

protected:
	// Generic items
	UPROPERTY()
	EProgressType ProgressType;
	UPROPERTY()
	FDateTime StartTime;
	UPROPERTY()
	FDateTime EndTime;
	// Training items
	UPROPERTY()
	EROVUnitType TrainingUnitType;
	UPROPERTY()
	int32 TrainingUnitAmount;
	// March items
	UPROPERTY()
	TArray<FUnitAmountDto> UnitsInMarch;
	// Building items
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	int32 BuildingLevel;

public:
	// Generic items
	EProgressType GetProgressType() const { return ProgressType; }
	FDateTime GetStartTime() const { return StartTime; }
	FDateTime GetEndTime() const { return EndTime; }
	// Training items
	EROVUnitType GetTrainingUnitType() const { return TrainingUnitType; }
	int32 GetTrainingUnitAmount() const { return TrainingUnitAmount; }
	// March items
	const TArray<FUnitAmountDto> &GetUnitsInMarch() const { return UnitsInMarch; }
	// Building items
	EBuildingType GetBuildingType() const { return BuildingType; }
	int32 GetBuildingLevel() const { return BuildingLevel; }
};

USTRUCT(BlueprintType)
struct FCitySingleProgressResponseDto
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FOverviewProgressItemDto ProgressOverview;

public:
	// Getter for ProgressOverview
	const FOverviewProgressItemDto &GetProgressOverview() const { return ProgressOverview; }
};

USTRUCT(BlueprintType)
struct FCitySingleProgressResponseApiDto
{
	GENERATED_BODY()

public:
	FCitySingleProgressResponseApiDto()
	{
	}
	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FCitySingleProgressResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FCitySingleProgressResponseDto Payload;
};

USTRUCT(BlueprintType)
struct FBuildingUpgradeCostResponseDto
{
	GENERATED_BODY()

public:
	FBuildingUpgradeCostResponseDto()
	{
	}

	FBuildingUpgradeDto GetBuildingUpgradeDetails() { return BuildingUpgradeDetails; }
	FBuildingCostDto GetBuildCost() { return BuildCost; }

protected:
	UPROPERTY()
	FBuildingUpgradeDto BuildingUpgradeDetails;
	UPROPERTY()
	FBuildingCostDto BuildCost;
};

USTRUCT()
struct FBuildingUpgradeCostResponseApiDto
{
	GENERATED_BODY()
public:
	FBuildingUpgradeCostResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingUpgradeCostResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingUpgradeCostResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingUpgradeCostResponseDto Payload;
};

USTRUCT(BlueprintType)
struct FBuildingUpgradeRequestDto
{
	GENERATED_BODY()
public:
	FBuildingUpgradeRequestDto()
	{
	}

	void SetCityId(FString city) { CityId = city; }
	void SetBuildingId(FString buildingId) { BuildingId = buildingId; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	FString BuildingId;
};

USTRUCT(BlueprintType)
struct FBuildingUpgradeResponseDto
{
	GENERATED_BODY()

public:
	FBuildingUpgradeResponseDto()
	{
	}

	FGuid GetBuildingId() { return FBase::ToGuid(BuildingId); }
	FDateTime GetFinishTime()
	{
		if (ParsedFinishTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*FinishTime, ParsedFinishTime);
		return ParsedFinishTime;
	}

	FDateTime GetStartTime()
	{
		if (ParsedFinishTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*StartTime, ParsedStartTime);
		return ParsedStartTime;
	}

protected:
	UPROPERTY()
	FString FinishTime;

	UPROPERTY()
	FDateTime ParsedFinishTime;

	UPROPERTY()
	FString StartTime;

	UPROPERTY()
	FDateTime ParsedStartTime;

	UPROPERTY()
	FString BuildingId;
};

USTRUCT(BlueprintType)
struct FBuildingUpgradeResponseApiDto
{
	GENERATED_BODY()
public:
	FBuildingUpgradeResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingUpgradeResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingUpgradeResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingUpgradeResponseDto Payload;
};

USTRUCT(BlueprintType)
struct FBuildingDeconstructResponseApiDto
{
	GENERATED_BODY()
public:
	FBuildingDeconstructResponseApiDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingDeconstructResponseDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingDeconstructResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingDeconstructResponseDto Payload;
};
