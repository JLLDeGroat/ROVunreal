// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Slot.generated.h"

/**
 *
 */
UINTERFACE()
class ROV_API USlot : public UInterface
{
	GENERATED_BODY()

};

class ROV_API ISlot {
	GENERATED_BODY()
public:

	virtual int GetSlotNumber() = 0;
	virtual AActor* GetBuilding() = 0;

};

