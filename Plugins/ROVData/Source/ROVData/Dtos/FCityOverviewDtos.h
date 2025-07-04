#pragma once

#include "CoreMinimal.h"
#include "../Enums/ROVEnums.h"
#include "FBaseDtos.h"
#include "FCityOverviewDtos.generated.h"

USTRUCT(BlueprintType)
struct FOverviewLocationDto
{
	GENERATED_BODY()

	// Default constructor
	FOverviewLocationDto()
	{
		X = -1;
		Y = -1;
	}

	int GetX() { return X; }
	int GetY() { return Y; }

protected:
	UPROPERTY(BlueprintReadWrite)
	int X;
	UPROPERTY(BlueprintReadWrite)
	int Y;
};

USTRUCT(BlueprintType)
struct FCityBonusDto
{
	GENERATED_BODY()

public:
	FCityBonusDto() {}

	ECityBonusType GetCityBonusType() { return CityBonusType; }
	float GetPercentage() { return Percentage; }
	EBuildingType GetBuildingType() { return BuildingType; }
	EROVUnitType GetUnitType() { return UnitType; }

protected:
	UPROPERTY()
	ECityBonusType CityBonusType;
	UPROPERTY()
	float Percentage;
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	EROVUnitType UnitType;
};

// Struct to represent the City Bonus list response
USTRUCT(BlueprintType)
struct FCityBonusGetListResponseDto
{
	GENERATED_BODY()
public:
	FCityBonusGetListResponseDto()
	{
	}

	TArray<FCityBonusDto> GetCityBonuses() { return CityBonuses; }

protected:
	UPROPERTY()
	TArray<FCityBonusDto> CityBonuses;
};

USTRUCT()
struct FOverviewUnitDto
{
	GENERATED_BODY()
public:
	FOverviewUnitDto()
	{
		UnitType = EROVUnitType::INVALID;
		Amount = 0;
	}

	EROVUnitType GetUnitType() { return UnitType; }
	int GetAmount() { return Amount; }

protected:
	UPROPERTY()
	EROVUnitType UnitType;
	UPROPERTY()
	int Amount;
};

USTRUCT()
struct FOverviewResourceDto
{
	GENERATED_BODY()
public:
	FOverviewResourceDto(EResourceType rType)
	{
		ResourceType = rType;
		Amount = -1;
		MaxAmount = -1;
	}

	FOverviewResourceDto()
	{
		ResourceType = EResourceType::INVALID;
		Amount = -1;
		MaxAmount = -1;
	}

	EResourceType GetResourceType() { return ResourceType; }
	int GetAmount() { return Amount; }
	int GetMaxAmount() { return MaxAmount; }
	void Update(int amount) { Amount = amount; }

protected:
	UPROPERTY()
	EResourceType ResourceType;
	UPROPERTY()
	int Amount;
	UPROPERTY()
	int MaxAmount;
};

USTRUCT()
struct FOverViewArmyDto
{
	GENERATED_BODY()
public:
	FOverViewArmyDto()
	{
		Name = "";
	}

	FString GetName() { return Name; }
	TArray<FOverviewUnitDto> GetUnits() { return Units; }

protected:
	UPROPERTY()
	FString Name;
	UPROPERTY()
	TArray<FOverviewUnitDto> Units;
};

USTRUCT()
struct FOverviewGarrisonDto
{
	GENERATED_BODY()
public:
	FOverviewGarrisonDto()
	{
		Army = FOverViewArmyDto();
	}

	FOverViewArmyDto *GetArmy() { return &Army; }

protected:
	UPROPERTY()
	FOverViewArmyDto Army;
};

USTRUCT()
struct FOverviewTrainingQueueDto
{
	GENERATED_BODY()
public:
	FOverviewTrainingQueueDto()
	{
		UnitType = EROVUnitType::INVALID;
		Amount = -1;
		StartTime = "";
		FinishTime = "";
	}

	// FString GetBuildingId() { return BuildingId; }
	FGuid GetBuildingId() { return FBase::ToGuid(BuildingId); }
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

	int GetAmount() { return Amount; }
	EROVUnitType GetUnitType() { return UnitType; }

protected:
	UPROPERTY()
	FString BuildingId;
	UPROPERTY()
	FString StartTime;
	UPROPERTY()
	FString FinishTime;
	UPROPERTY()
	int Amount;
	UPROPERTY()
	EROVUnitType UnitType;

	UPROPERTY()
	FDateTime ParsedStartTime;
	UPROPERTY()
	FDateTime ParsedFinishTime;
};

USTRUCT()
struct FOverviewResearchQueueDto
{
	GENERATED_BODY()
public:
	FOverviewResearchQueueDto()
	{
		ResearchType = EResearchType::INVALID;
		Amount = -1;
		StartUpdate = "";
		FinishUpdate = "";
	}
	EResearchType GetResearchType() { return ResearchType; }
	int GetAmount() { return Amount; }
	FString GetStartUpdate() { return StartUpdate; }
	FString GetFinishUpdate() { return FinishUpdate; }

protected:
	UPROPERTY()
	EResearchType ResearchType;
	UPROPERTY()
	int Amount;
	UPROPERTY()
	FString StartUpdate;
	UPROPERTY()
	FString FinishUpdate;
};

USTRUCT()
struct FOverViewBuildingDto
{
	GENERATED_BODY()
public:
	FOverViewBuildingDto()
	{
		Constructor();
	}

	FOverViewBuildingDto(EBuildingType buildingType, FString buildingId, int level, EResourceType resourceType = EResourceType::INVALID)
	{
		Constructor();
		BuildingType = buildingType;
		Level = level;
		BuildingId = buildingId;
		ResourceProducedType = resourceType;
	}

	int GetLevel() { return Level; }
	EBuildingType GetBuildingType() { return BuildingType; }
	FString GetBuildingId() { return BuildingId; }
	FDateTime GetStartTime()
	{
		if (ParsedStartTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*StartUpdate, ParsedStartTime);

		return ParsedStartTime;
	}
	FDateTime GetFinishTime()
	{
		if (ParsedFinishTime.GetTicks() == 0)
			FDateTime::ParseIso8601(*FinishUpdate, ParsedFinishTime);
		return ParsedFinishTime;
	}

	bool GetIsUpgrading()
	{
		return StartUpdate.Len() > 0 || FinishUpdate.Len() > 0;
	}

	void LevelUp()
	{
		Level += 1;
		StartUpdate = "";
		FinishUpdate = "";
	}

	FOverviewTrainingQueueDto *GetTrainingQueue() { return &TrainingQueue; }
	FOverviewResearchQueueDto *GetResearchQueue() { return &ResearchQueue; }

	EResourceType GetResourceType() { return ResourceProducedType; }

	bool GetIsDeconstructing() { return IsDeconstructing; }

protected:
	UPROPERTY()
	int Level;
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	FString BuildingId;
	UPROPERTY()
	FString StartUpdate;
	UPROPERTY()
	FString FinishUpdate;

	UPROPERTY()
	FDateTime ParsedStartTime;
	UPROPERTY()
	FDateTime ParsedFinishTime;

	UPROPERTY()
	FOverviewTrainingQueueDto TrainingQueue;
	UPROPERTY()
	FOverviewResearchQueueDto ResearchQueue;
	UPROPERTY()
	EResourceType ResourceProducedType;

	UPROPERTY()
	bool IsDeconstructing;

private:
	void Constructor()
	{
		Level = -1;
		BuildingType = EBuildingType::INVALID;
		BuildingId = "";
		StartUpdate = "";
		FinishUpdate = "";
		ResourceProducedType = EResourceType::INVALID;

		TrainingQueue = FOverviewTrainingQueueDto();
		ResearchQueue = FOverviewResearchQueueDto();
	}
};

USTRUCT()
struct FOverViewBuildingSlotDto
{
	GENERATED_BODY()
public:
	FOverViewBuildingSlotDto(int slotId)
	{
		Constructor();
		Slot = slotId;
	}
	FOverViewBuildingSlotDto()
	{
		Constructor();
	}

	int GetSlot() { return Slot; }
	FOverViewBuildingDto *GetBuilding() { return &Building; }

	bool HasValidBuilding()
	{
		return Building.GetBuildingType() != EBuildingType::INVALID &&
			   Building.GetLevel() >= 0;
	}

	FOverViewBuildingDto *AddBuilding(EBuildingType buildingType, FString id, int level)
	{
		Building = FOverViewBuildingDto(buildingType, id, level);
		return GetBuilding();
	}

protected:
	UPROPERTY()
	int Slot;
	UPROPERTY()
	FOverViewBuildingDto Building;

private:
	void Constructor()
	{
		Slot = -1;
		Building = FOverViewBuildingDto();
	}
};

USTRUCT()
struct FOverViewCityDto
{
	GENERATED_BODY()
public:
	FOverViewCityDto()
	{
		CityId = "";
		Garrison = FOverviewGarrisonDto();
		CityLevel = -1;
	}

	FString GetCityId() { return CityId; }
	FGuid GetCityIdAsGuid()
	{
		FGuid guid;
		FGuid::Parse(CityId, guid);
		return guid;
	}
	TArray<FOverViewBuildingSlotDto> &GetBuildingSlots() { return BuildingSlots; }
	FOverviewGarrisonDto *GetGarrison() { return &Garrison; }
	TArray<FOverviewResourceDto> GetResources() { return Resources; }

	FOverviewResourceDto *GetResource(EResourceType resourceType)
	{
		for (int i = 0; i < Resources.Num(); i++)
		{
			if (Resources[i].GetResourceType() == resourceType)
				return &Resources[i];
		}

		return &Resources[Resources.Emplace(FOverviewResourceDto(resourceType))];
	}

	int GetCityLevel() { return CityLevel; }

	int GetResourceAmount(EResourceType resourceType)
	{
		for (int i = 0; i < Resources.Num(); i++)
			if (Resources[i].GetResourceType() == resourceType)
				return Resources[i].GetAmount();

		auto newR = FOverviewResourceDto();

		return 0;
	}

	int GetResourceMaxAmount(EResourceType resourceType)
	{
		for (int i = 0; i < Resources.Num(); i++)
			if (Resources[i].GetResourceType() == resourceType)
				return Resources[i].GetMaxAmount();

		return 0;
	}

	FOverViewBuildingSlotDto *CreateSlot(int slotId)
	{
		FOverViewBuildingSlotDto slot = FOverViewBuildingSlotDto(slotId);
		return &BuildingSlots[BuildingSlots.Emplace(slot)];
	}

	FDateTime GetStartTime()
	{
		if (ParsedUpgradeStart.GetTicks() == 0)
			FDateTime::ParseIso8601(*UpgradeStart, ParsedUpgradeStart);

		return ParsedUpgradeStart;
	}
	FDateTime GetFinishTime()
	{
		if (ParsedUpgradeFinish.GetTicks() == 0)
			FDateTime::ParseIso8601(*UpgradeFinish, ParsedUpgradeFinish);
		return ParsedUpgradeFinish;
	}
	bool GetIsUpgrading()
	{
		return UpgradeStart.Len() > 0 || UpgradeFinish.Len() > 0;
	}

	FOverviewLocationDto *GetLocation() { return &Location; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	TArray<FOverViewBuildingSlotDto> BuildingSlots;
	UPROPERTY()
	FOverviewGarrisonDto Garrison;
	UPROPERTY()
	TArray<FOverviewResourceDto> Resources;
	UPROPERTY()
	int CityLevel;

	UPROPERTY()
	FString UpgradeStart;
	UPROPERTY()
	FString UpgradeFinish;

	UPROPERTY()
	FDateTime ParsedUpgradeStart;
	UPROPERTY()
	FDateTime ParsedUpgradeFinish;

	UPROPERTY()
	FOverviewLocationDto Location;
};

USTRUCT()
struct FOverviewCityRequestDto
{
	GENERATED_BODY()
public:
	FOverviewCityRequestDto()
	{
		GetDefault = true;
	}

	void SetAccountId(FString acc) { AccountId = acc; }

	// default is true
	void SetDefault(bool value) { GetDefault = value; }

protected:
	UPROPERTY()
	bool GetDefault;
	UPROPERTY()
	FString AccountId;
};

USTRUCT()
struct FCityBonusGetRequestDto
{
	GENERATED_BODY()
public:
	FCityBonusGetRequestDto()
	{
	}

	void SetCityId(FString id) { CityId = id; }
	void SetCityBonusType(ECityBonusType bonusType) { CityBonusType = (uint8)bonusType; }

protected:
	UPROPERTY()
	uint8 CityBonusType;
	UPROPERTY()
	FString CityId;
};

USTRUCT()
struct FResourceRateDto
{
	GENERATED_BODY()
public:
	FResourceRateDto()
	{
	}

	int GetAmount() { return Amount; }
	int GetLevel() { return Level; }
	int GetTier() { return Tier; }

protected:
	UPROPERTY()
	int Amount;
	UPROPERTY()
	int Level;
	UPROPERTY()
	int Tier;
};

USTRUCT()
struct FResourceRateResponseDto
{
	GENERATED_BODY()
public:
	FResourceRateResponseDto()
	{
	}

	TArray<FResourceRateDto> GetResourceRates() { return ResourceRates; }

protected:
	UPROPERTY()
	TArray<FResourceRateDto> ResourceRates;
};

USTRUCT(BlueprintType)
struct FBuildingTypeDto
{
	GENERATED_BODY()

	FBuildingTypeDto()
		: BuildingType(EBuildingType::INVALID),
		  MaxLevel(0),
		  CostMultiplier(1.0f),
		  BuildTimeMultiplier(1.0f),
		  bIsTrainingBuilding(false),
		  bIsResearchBuilding(false),
		  bIsResourceBuilding(false),
		  ResourceType(EResourceType::INVALID)
	{
	}

	EBuildingType GetBuildingType() { return BuildingType; }
	FString GetDescription() { return Description; }
	FString GetName() { return Description; }
	int32 GetMaxLevel() { return MaxLevel; }
	float GetCostMultiplier() { return CostMultiplier; }
	float GetBuildTimeMultiplier() { return BuildTimeMultiplier; }
	bool GetbIsTrainingBuilding() { return bIsTrainingBuilding; }
	bool GetbIsResearchBuilding() { return bIsResearchBuilding; }
	bool GetbIsResourceBuilding() { return bIsResearchBuilding; }
	EResourceType GetResourceType() { return ResourceType; }

protected:
	UPROPERTY(BlueprintReadWrite)
	EBuildingType BuildingType;
	UPROPERTY(BlueprintReadWrite)
	FString Description;
	UPROPERTY(BlueprintReadWrite)
	FString Name;
	UPROPERTY(BlueprintReadWrite)
	int32 MaxLevel;
	UPROPERTY(BlueprintReadWrite)
	float CostMultiplier;
	UPROPERTY(BlueprintReadWrite)
	float BuildTimeMultiplier;
	UPROPERTY(BlueprintReadWrite)
	bool bIsTrainingBuilding;
	UPROPERTY(BlueprintReadWrite)
	bool bIsResearchBuilding;
	UPROPERTY(BlueprintReadWrite)
	bool bIsResourceBuilding;
	UPROPERTY(BlueprintReadWrite)
	EResourceType ResourceType;
};

USTRUCT(BlueprintType)
struct FBuildingTypesResponseDto
{
	GENERATED_BODY()

	// Default constructor
	FBuildingTypesResponseDto()
	{
		BuildingTypes.Empty();
	}

	TArray<FBuildingTypeDto> GetBuildingTypes() { return BuildingTypes; }

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FBuildingTypeDto> BuildingTypes;
};