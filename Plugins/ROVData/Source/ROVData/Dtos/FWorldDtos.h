// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBaseDtos.h"
#include "../Enums/ROVEnums.h"
#include "Templates/SharedPointer.h"
#include "FGenericApiResponse.h"
#include "FWorldDtos.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FOccupiedDetailsDto
{
	GENERATED_BODY()

	FOccupiedDetailsDto()
	{
	}

	EOccupiedType GetOccupiedType() { return OccupiedType; }

protected:
	UPROPERTY()
	EOccupiedType OccupiedType;
};

USTRUCT(BlueprintType)
struct FLocationDto
{
	GENERATED_BODY()

	FLocationDto()
	{
	}

	FString GetUid() { return Uid; }
	int GetX() { return X; }
	int GetY() { return Y; }
	bool GetOccupied() { return Occupied; }
	bool GetBattleLocation() { return BattleLocation; }

	FOccupiedDetailsDto *GetOccupiedDetails() { return &OccupiedDetails; }

protected:
	UPROPERTY()
	FString Uid;

	UPROPERTY()
	int X;

	UPROPERTY()
	int Y;

	UPROPERTY()
	bool Occupied;

	UPROPERTY()
	bool BattleLocation;

	UPROPERTY()
	FOccupiedDetailsDto OccupiedDetails;
};

USTRUCT(BlueprintType)
struct FMapLocationAroundCityRequestDto
{
	GENERATED_BODY()

	FMapLocationAroundCityRequestDto()
	{
	}

	void SetCityId(FString cityId) { CityId = cityId; }
	void SetRadius(int radius) { Radius = radius; }

protected:
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	int Radius;
};

USTRUCT(BlueprintType)
struct FMapLocationAroundLocationRequestDto
{
	GENERATED_BODY()

	FMapLocationAroundLocationRequestDto()
	{
	}

	void SetX(int x) { X = x; }
	void SetY(int y) { Y = y; }
	void SetRadius(int radius) { Radius = radius; }

protected:
	UPROPERTY()
	int X;
	UPROPERTY()
	int Y;
	UPROPERTY()
	int Radius;
};

USTRUCT(BlueprintType)
struct FMapLocationAroundCityResponseDto
{
	GENERATED_BODY()

	FMapLocationAroundCityResponseDto()
	{
	}

	TArray<FLocationDto> GetLocations() { return Locations; }

protected:
	UPROPERTY()
	TArray<FLocationDto> Locations;
};

USTRUCT(BlueprintType)
struct FMapLocationAroundLocationResponseDto
{
	GENERATED_BODY()

	FMapLocationAroundLocationResponseDto()
	{
	}

	TArray<FLocationDto> GetLocations() { return Locations; }

protected:
	UPROPERTY()
	TArray<FLocationDto> Locations;
};

USTRUCT()
struct FMapUnitOverviewDto
{
	GENERATED_BODY()
public:
	FMapUnitOverviewDto()
	{
		UnitType = EROVUnitType::INVALID;
		Amount = 0;
	}

	EROVUnitType GetUnitType() { return UnitType; }
	int GetAmount() { return Amount; }
	FString GetAmountDescription() { return AmountDescription; }

protected:
	UPROPERTY()
	EROVUnitType UnitType;
	UPROPERTY()
	int Amount;
	UPROPERTY()
	FString AmountDescription;
};

USTRUCT(BlueprintType)
struct FMapLocationOccupationDetailsResponseDto
{
	GENERATED_BODY()
public:
	FMapLocationOccupationDetailsResponseDto()
	{
	}

	bool GetIsOwnerOfCity() { return IsOwnerOfCity; }
	FString GetName() { return Name; }
	int GetAiLevel() { return AiLevel; }
	FString GetEnvironmentType() { return EnvironmentType; }
	bool GetIsClaimed() { return IsClaimed; }
	TArray<FMapUnitOverviewDto> GetGarrison() { return Garrison; }
	FString GetLocationUid() { return LocationUid; }

protected:
	UPROPERTY()
	bool IsOwnerOfCity;
	UPROPERTY()
	FString Name;
	UPROPERTY()
	int AiLevel;
	UPROPERTY()
	FString EnvironmentType;
	UPROPERTY()
	bool IsClaimed;
	UPROPERTY()
	TArray<FMapUnitOverviewDto> Garrison;
	UPROPERTY()
	FString LocationUid;
};

USTRUCT(BlueprintType)
struct FMapLocationOccupationDetailsRequestDto
{
	GENERATED_BODY()
public:
	FMapLocationOccupationDetailsRequestDto()
	{
	}

	void SetX(int x) { X = x; }
	void SetY(int y) { Y = y; }
	void SetCityId(FString cityId) { CityId = cityId; }
	void SetOccupiedType(EOccupiedType ocType) { OccupiedType = (uint8)ocType; }

protected:
	UPROPERTY()
	int X;
	UPROPERTY()
	int Y;
	UPROPERTY()
	FString CityId;
	UPROPERTY()
	uint8 OccupiedType;
};
