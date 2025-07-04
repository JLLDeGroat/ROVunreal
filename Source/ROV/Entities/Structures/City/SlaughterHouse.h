// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCityStructure.h"
#include "../../../Interfaces/Building.h"
#include "SlaughterHouse.generated.h"

/**
 *
 */
UCLASS()
class ROV_API ASlaughterHouse : public ABaseCityStructure, public IBuilding
{
	GENERATED_BODY()

public:
	ASlaughterHouse(const FObjectInitializer& ObjectInitializer);

	virtual void PrepareLevelOne() override;
	virtual void PrepareLevelTen() override;
	virtual void PrepareLevelTwenty() override;
	virtual void PrepareLevelThirty() override;
	virtual void PrepareLevelFourty() override;
	virtual void PrepareLevelFifty() override;
};
