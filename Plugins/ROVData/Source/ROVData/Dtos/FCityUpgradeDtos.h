#pragma once

#include "CoreMinimal.h"
#include "FBaseDtos.h"
#include "../Enums/ROVEnums.h"
#include "FCityUpgradeDtos.generated.h"

USTRUCT(BlueprintType)
struct FBuildingCityUpgradeDetailsRequestDto
{
    GENERATED_BODY()
public:
    FBuildingCityUpgradeDetailsRequestDto()
    {
        CityId = "";
    }

    void SetCityId(FString cityId) { CityId = cityId; }

protected:
    UPROPERTY()
    FString CityId;
};

USTRUCT(BlueprintType)
struct FBuildingCityUpgradeDetailsResponseDto
{
    GENERATED_BODY()

public:
    FBuildingCityUpgradeDetailsResponseDto()
    {
    }

    TArray<FResourceDto> GetResources() { return Resources; }
    FBuildingUpgradeDto GetBuildingUpgradeDetails() { return BuildingUpgradeDetails; }
    int GetLevel() { return Level; }

protected:
    UPROPERTY()
    TArray<FResourceDto> Resources;
    UPROPERTY()
    FBuildingUpgradeDto BuildingUpgradeDetails;

    UPROPERTY()
    int Level;
};

USTRUCT(BlueprintType)
struct FBuildingCityUpgradeDetailsResponseApiDto
{
    GENERATED_BODY()
public:
    FBuildingCityUpgradeDetailsResponseApiDto()
    {
        Error = "";
        Success = false;
        Payload = FBuildingCityUpgradeDetailsResponseDto();
    }

    FString GetError() { return Error; }
    bool GetSuccess() { return Success; }
    FBuildingCityUpgradeDetailsResponseDto GetPayload() { return Payload; }

protected:
    UPROPERTY()
    bool Success;
    UPROPERTY()
    FString Error;
    UPROPERTY()
    FBuildingCityUpgradeDetailsResponseDto Payload;
};

// upgrade request
USTRUCT(BlueprintType)
struct FCityUpgradeRequestDto
{
    GENERATED_BODY()
public:
    FCityUpgradeRequestDto()
    {
        CityId = "";
    }

    void SetCityId(FString cityId) { CityId = cityId; }

protected:
    UPROPERTY()
    FString CityId;
};

USTRUCT(BlueprintType)
struct FCityUpgradeResponseDto
{
    GENERATED_BODY()

public:
    FCityUpgradeResponseDto()
    {
    }

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
    FDateTime ParsedFinishTime;

    UPROPERTY()
    FString StartTime;

    UPROPERTY()
    FDateTime ParsedStartTime;
};

USTRUCT(BlueprintType)
struct FCityUpgradeResponseApiDto
{
    GENERATED_BODY()
public:
    FCityUpgradeResponseApiDto()
    {
        Error = "";
        Success = false;
        Payload = FCityUpgradeResponseDto();
    }

    FString GetError() { return Error; }
    bool GetSuccess() { return Success; }
    FCityUpgradeResponseDto GetPayload() { return Payload; }

protected:
    UPROPERTY()
    bool Success;
    UPROPERTY()
    FString Error;
    UPROPERTY()
    FCityUpgradeResponseDto Payload;
};