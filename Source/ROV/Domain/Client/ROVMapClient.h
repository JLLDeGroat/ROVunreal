// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Interfaces/GatewayMapClient.h"
#include "Base/BaseROVClient.h"
#include "ROVMapClient.generated.h"

/**
 *
 */
UCLASS()
class ROV_API UROVMapClient : public UBaseROVClient, public IGatewayMapClient
{
	GENERATED_BODY()

public:
	virtual void GetInitialMapLocation(FString cityId, int radius, TFunction<void(FGenericApiResponse responseDto)> callBack) override;
	virtual void GetLocationsAroundLocation(int x, int y, int radius, TFunction<void(FGenericApiResponse responseDto)> callBack) override;
	virtual void GetLocationDetails(int x, int y, FString cityId, EOccupiedType occupationType, TFunction<void(FGenericApiResponse responseDto)> callBack) override;
};
