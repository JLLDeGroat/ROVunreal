// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TouchReceiveComponent.generated.h"

/**
 *
 */
UCLASS()
class ROV_API UTouchReceiveComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTouchReceiveComponent(const FObjectInitializer &ObjectInitializer);
};
