// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStructure.h"
#include "BaseCityStructure.generated.h"

class UBuildingDetailsComponent;
/**
 * 
 */
UCLASS()
class ROV_API ABaseCityStructure : public ABaseStructure
{
	GENERATED_BODY()
	
public:

	ABaseCityStructure(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UBuildingDetailsComponent* BuildingDetailsComponent;

};
