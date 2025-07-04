#pragma once

#include "CoreMinimal.h"
#include "FBaseDtos.h"
#include "../Enums/ROVEnums.h"
#include "FBuildingDtos.generated.h"

USTRUCT()
struct FBuildingDetailsResponseDto
{
	GENERATED_BODY()
public:
	FBuildingDetailsResponseDto()
	{
	}

	int GetResourcePerHour() { return ResourcePerHour; }
	TArray<EROVUnitType> GetTrainableUnits() { return TrainableUnits; }
	EResourceType GetResourceGenerated() { return ResourceGenerated; }
	int GetResourceTier() { return ResourceTier; }
	int GetCurrentLevel() { return CurrentLevel; }
	bool GetIsUpgrading() { return IsUpgrading; }
	bool GetIsDeconstructing() { return IsDeconstructing; }

protected:
	UPROPERTY()
	int ResourcePerHour;
	UPROPERTY()
	TArray<EROVUnitType> TrainableUnits;
	UPROPERTY()
	EResourceType ResourceGenerated;
	UPROPERTY()
	int ResourceTier;
	UPROPERTY()
	int CurrentLevel;
	UPROPERTY()
	bool IsUpgrading;
	UPROPERTY()
	bool IsDeconstructing;
};

USTRUCT()
struct FBuildingDetailsRequestDto
{
	GENERATED_BODY()
public:
	FBuildingDetailsRequestDto() {}
	FBuildingDetailsRequestDto(FString cId, FString bId)
	{
		CityId = cId;
		BuildingId = bId;
	}

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	FString BuildingId;
};

USTRUCT()
struct FBuildingSlotBuildingItemsDto
{
	GENERATED_BODY()
public:
	FBuildingSlotBuildingItemsDto()
	{
		BuildingType = EBuildingType::INVALID;
		Name = "";
		Description = "";
	}

	EBuildingType GetBuildingType() { return BuildingType; }
	FString GetName() { return Name; }
	FString GetDescription() { return Description; }
	FBuildingCostDto GetBuildingCost() { return BuildingCost; }

protected:
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	FString Name;
	UPROPERTY()
	FString Description;
	UPROPERTY()
	FBuildingCostDto BuildingCost;
};

USTRUCT()
struct FBuildingSlotBuildingsResponseDto
{
	GENERATED_BODY()
public:
	FBuildingSlotBuildingsResponseDto()
	{
	}

	TArray<FBuildingSlotBuildingItemsDto> GetBuildingItems() { return BuildingSlotBuildings; }

protected:
	UPROPERTY()
	TArray<FBuildingSlotBuildingItemsDto> BuildingSlotBuildings;
};

USTRUCT()
struct FBuildingBuildRequestDto
{
	GENERATED_BODY()
public:
	FBuildingBuildRequestDto()
	{
		CityId = "";
		Slot = -1;
		/*BuildingType = EBuildingType::INVALID;*/
		BuildingType = 0;
	}

	void SetCityId(FString cityId) { CityId = cityId; }
	void SetSlot(int slot) { Slot = slot; }
	void SetBuildingType(EBuildingType buildingType) { BuildingType = (uint8)buildingType; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	int Slot;
	UPROPERTY()
	uint8 BuildingType;
};

USTRUCT()
struct FBuildingBuildResponsePayloadDto
{
	GENERATED_BODY()
public:
	FBuildingBuildResponsePayloadDto()
	{
		BuildingId = "";
		CityId = "";
	}

	FGuid GetBuildingId() { return FBase::ToGuid(BuildingId); }
	EBuildingType GetBuildingType() const { return BuildingType; }
	FGuid GetCityId() { return FBase::ToGuid(CityId); }

	FDateTime GetStartTime()
	{
		if (ParsedStartTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*StartTime, ParsedStartTime);

		return ParsedStartTime;
	}
	FDateTime GetFinishTime()
	{
		if (ParsedFinishTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*FinishTime, ParsedFinishTime);
		return ParsedFinishTime;
	}

protected:
	UPROPERTY()
	FString FinishTime;
	UPROPERTY()
	FString StartTime;
	UPROPERTY()
	FString BuildingId;
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	FDateTime ParsedStartTime;
	UPROPERTY()
	FDateTime ParsedFinishTime;
};

USTRUCT()
struct FBuildingBuildResponseDto
{
	GENERATED_BODY()
public:
	FBuildingBuildResponseDto()
	{
		Error = "";
		Success = false;
		Payload = FBuildingBuildResponsePayloadDto();
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FBuildingBuildResponsePayloadDto GetPayload() { return Payload; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FBuildingBuildResponsePayloadDto Payload;
};

#pragma region Upgrade Requests

USTRUCT()
struct FBuildingUpgradeCostRequestDto
{
	GENERATED_BODY()
public:
	FBuildingUpgradeCostRequestDto()
	{
	}

	void SetCityId(FString cityId) { CityId = cityId; }
	void SetBuildingId(FString buildingId) { BuildingId = buildingId; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	FString BuildingId;
};

USTRUCT()
struct FBuildingUpgradeDto
{
	GENERATED_BODY()
public:
	FBuildingUpgradeDto()
	{
	}

	EBuildingType GetBuildingType() { return BuildingType; }
	float GetTimeMultiplier() { return TimeMultiplier; }
	float GetCostMultiplier() { return CostMultiplier; }
	int GetCurrentLevel() { return CurrentLevel; }
	FString GetUpgradeTime() { return UpgradeTime; }

protected:
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	float TimeMultiplier;
	UPROPERTY()
	float CostMultiplier;
	UPROPERTY()
	int CurrentLevel;
	UPROPERTY()
	FString UpgradeTime;
};

#pragma endregion

#pragma region Deconstruct Request

USTRUCT()
struct FBuildingDeconstructRequestDto
{
	GENERATED_BODY()
public:
	FBuildingDeconstructRequestDto()
	{
	}

	void SetCityId(FString cityId) { CityId = cityId; }
	void SetBuildingId(FString buildingId) { BuildingId = buildingId; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	FString BuildingId;
};

USTRUCT()
struct FBuildingDeconstructResponseDto
{
	GENERATED_BODY()
public:
	FBuildingDeconstructResponseDto()
	{
	}

	FGuid GetBuildingId() { return FBase::ToGuid(BuildingId); }
	EBuildingType GetBuildingType() const { return BuildingType; }

	FDateTime GetStartTime()
	{
		if (ParsedStartTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*StartTime, ParsedStartTime);

		return ParsedStartTime;
	}
	FDateTime GetFinishTime()
	{
		if (ParsedFinishTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*FinishTime, ParsedFinishTime);
		return ParsedFinishTime;
	}

protected:
	UPROPERTY()
	FString FinishTime;
	UPROPERTY()
	FString StartTime;
	UPROPERTY()
	FString BuildingId;
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	FDateTime ParsedStartTime;
	UPROPERTY()
	FDateTime ParsedFinishTime;
};

#pragma endregion