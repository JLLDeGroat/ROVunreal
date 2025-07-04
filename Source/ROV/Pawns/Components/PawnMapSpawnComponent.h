// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "PawnMapSpawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROV_API UPawnMapSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPawnMapSpawnComponent();
	virtual void BeginPlay() override;

protected:

};
