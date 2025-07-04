// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "CoreMinimal.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Dtos/FGenericApiResponse.h"
#include "GatewayMapClient.generated.h"

struct FOverviewCityRequestDto;
struct FBuildingBuildRequestDto;
struct FApiDto;
/**
 *
 */
UINTERFACE(BlueprintType)
class ROV_API UGatewayMapClient : public UInterface
{
	GENERATED_BODY()
public:
};

class ROV_API IGatewayMapClient
{
	GENERATED_BODY()
public:
	virtual void GetInitialMapLocation(FString cityId, int radius, TFunction<void(FGenericApiResponse responseDto)> callBack) = 0;
	virtual void GetLocationsAroundLocation(int x, int y, int radius, TFunction<void(FGenericApiResponse responseDto)> callBack) = 0;

	virtual void GetLocationDetails(int x, int y, FString cityId, EOccupiedType occupationType, TFunction<void(FGenericApiResponse responseDto)> callBack) = 0;
};
