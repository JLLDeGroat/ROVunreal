// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EBuildingSlotNames : uint8 {
	INVALID = 0,
	CityWall = 99
};

UENUM(BlueprintType)
enum class EBuildingType : uint8 {
	INVALID = 0,
	SlaughterHouse = 1,
	SoulQuarrey = 2,
	ChemicalPlant = 3,
	Chiseler = 4,
	Barracks = 5,
	Mulcher = 6,
	WetWorks = 7,
	IronDigger = 8,
	CopperDigger = 9,
	TinDigger = 10,
	TreeRipper = 11,
	Heater = 12,
	Jeweler = 13, // unused
	PeatreeDish = 14,
	City = 15,
	CityWall = 16,
	CropHouse = 17,
};

UENUM(BlueprintType)
enum class ECityBonusType : uint8 {
	INVALID = 0,
	SLHEfficiency = 1,
	SOQEfficiency = 2,
	CHPEfficiency = 3,
	CHEfficiency = 4,
	PeasantEfficiency = 5,
	Construction = 6,
	PeatreeDishResearch = 7
};

UENUM(BlueprintType)
enum class ECityType : uint8 {
	INVALID = 0,
	Player = 1,
	Ai = 2
};

UENUM(BlueprintType)
enum class EClanMemberRank : uint8 {
	INVALID = 0,
	God = 1,
	Master = 2,
	Commander = 3,
	Member = 4,
	Grunt = 5
};

UENUM(BlueprintType)
enum class EMarchType : uint8 {
	INVALID = 0,
	Attack = 1,
	Garrison = 2,
	CityReturn = 3,
	Colonise = 4
};

UENUM(BlueprintType)
enum class ENotificationType : uint8 {
	INVALID = 0,
	Battle = 1,
	Construction = 2,
	Upgrade = 3,
	Research = 4,
	Training = 5,
};

UENUM(BlueprintType)
enum class EOccupiedType : uint8 {
	INVALID = 0,
	PlayerCity = 1,
	AICity = 2,
	PlayerOutpost = 3,
	Environment = 4,
};

UENUM(BlueprintType)
enum class EProgressType : uint8 {
	INVALID = 0,
	Training = 1,
	Building = 2,
	Marching = 3,
	Researching = 4,
	Upgrading = 5,
};

UENUM(BlueprintType)
enum class EResearchType : uint8 {
	INVALID = 0,
	BiggahSlaugher = 1,
	GMO = 2,
};

UENUM(BlueprintType)
enum class EResourceType : uint8 {
	INVALID = 0,
	OrganicMaterial = 1,
	OrganicMatter = 2,
	ConstructionSoil = 3,
	Adhesive = 4,
	StoneFragment = 5,
	Clay = 6,
	IronFragment = 7,
	CopperFragment = 8,
	TinFragment = 9,
	Bark = 10,
	CarbonFragment = 11,
	Minerals = 12
};

UENUM(BlueprintType)
enum class EROVUnitType : uint8 {
	INVALID = 0,
	Peasant = 1,
	ArrowRoot = 2,
	CeleryStickman = 3,
};

class ROVDATA_API ROVEnums
{
public:
	template< typename T >
	static FORCEINLINE FString ToString(T EnumValue)
	{
		static_assert(TIsUEnumClass< T >::Value, "'T' template parameter to EnumToString must be a valid UEnum");
		return StaticEnum< T >()->GetNameStringByIndex((int32)EnumValue);
	}

	static FORCEINLINE FString BuildingTypeAsString(EBuildingType buildingType) {
		switch (buildingType) {
		case EBuildingType::SlaughterHouse: return "Slaughter House";
		case EBuildingType::SoulQuarrey: return "Soul Quarrey";
		case EBuildingType::ChemicalPlant: return "Chemical Plant";
		case EBuildingType::Chiseler: return "Chiseler";
		case EBuildingType::Barracks: return "Barracks";
		case EBuildingType::Mulcher: return "Mulcher";
		case EBuildingType::WetWorks: return "Wet Works";
		case EBuildingType::IronDigger: return "Iron Digger";
		case EBuildingType::CopperDigger: return "Copper Digger";
		case EBuildingType::TinDigger: return "Tin Digger";
		case EBuildingType::TreeRipper: return "Tree Ripper";
		case EBuildingType::Heater: return "Heater";
		case EBuildingType::Jeweler: return "Jeweler";
		case EBuildingType::PeatreeDish: "Peatree Dish";
		case EBuildingType::City: return "City";
		case EBuildingType::CityWall: return "City Wall";
		case EBuildingType::CropHouse: return "Crop House";
		}

		return "INVALID";
	}

	static FORCEINLINE FString ResourceAsString(EResourceType resource) {
		switch (resource) {
		case EResourceType::OrganicMaterial: return "Organic Material";
		case EResourceType::OrganicMatter: return "Organic Matter";
		case EResourceType::ConstructionSoil: return "Construction Soil";
		case EResourceType::Adhesive: return "Adhesive";
		case EResourceType::StoneFragment: return "Stone Fragment";
		case EResourceType::Clay: return "Clay";
		case EResourceType::IronFragment: return "Iron Fragment";
		case EResourceType::CopperFragment: return "Copper Fragment";
		case EResourceType::TinFragment: return "Tin Fragment";
		case EResourceType::Bark: return "Bark";
		case EResourceType::CarbonFragment: return "Carbon Fragment";
		case EResourceType::Minerals: return "Minerals";
		}

		return "INVALID";
	}

	static FORCEINLINE FString UnitAsString(EROVUnitType unitType) {
		switch (unitType) {
		case EROVUnitType::Peasant: return "Peasant";
		case EROVUnitType::ArrowRoot: return "Arrow Root";
		case EROVUnitType::CeleryStickman: return "Celery Stickman";
		}

		return "INVALID";
	}
};