// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBaseDtos.h"
#include "../Enums/ROVEnums.h"
#include "FUnitDtos.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FUnitAmountDto
{
	GENERATED_BODY()

protected:
	UPROPERTY() int32 Amount;
	UPROPERTY() EROVUnitType UnitType;

public:
	// Getter for Amount
	int32 GetAmount() const { return Amount; }

	// Getter for UnitType
	EROVUnitType GetUnitType() const { return UnitType; }
};