// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCityStructure.h"
#include "../../../Interfaces/Building.h"
#include "Chiseler.generated.h"

/**
 *
 */
UCLASS()
class ROV_API AChiseler : public ABaseCityStructure, public IBuilding
{
	GENERATED_BODY()
public:
	AChiseler(const FObjectInitializer &ObjectInitializer);

	virtual void PrepareLevelOne() override;
	virtual void PrepareLevelTen() override;
	virtual void PrepareLevelTwenty() override;
	virtual void PrepareLevelThirty() override;
	virtual void PrepareLevelFourty() override;
	virtual void PrepareLevelFifty() override;
};
