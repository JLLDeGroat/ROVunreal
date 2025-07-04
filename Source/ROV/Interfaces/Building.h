// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Building.generated.h"

/**
 *
 */
UINTERFACE()
class ROV_API UBuilding : public UInterface
{
	GENERATED_BODY()

};

class ROV_API IBuilding {
	GENERATED_BODY()
public:

	virtual void PrepareLevelOne() = 0;
	virtual void PrepareLevelTen() = 0;
	virtual void PrepareLevelTwenty() = 0;
	virtual void PrepareLevelThirty() = 0;
	virtual void PrepareLevelFourty() = 0;
	virtual void PrepareLevelFifty() = 0;

};



