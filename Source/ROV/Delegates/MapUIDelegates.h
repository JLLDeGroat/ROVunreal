// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Dtos/FResourceDtos.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "UObject/NoExportTypes.h"
#include "MapUIDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMapLocationChange, int, X, int, Y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllowMapUiReactions);

UCLASS()
class ROV_API UMapUIDelegates : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UMapUIDelegates *GetInstance()
	{
		static UMapUIDelegates *mapUIDelegates = 0;
		if (!mapUIDelegates)
		{
			mapUIDelegates = NewObject<UMapUIDelegates>();
			mapUIDelegates->AddToRoot();
		}
		return mapUIDelegates;
	}

	FOnMapLocationChange _OnMapLocationChange;
	FOnAllowMapUiReactions _OnAllowMapUiReactions;
};
