// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCityStructure.h"
#include "../Components/BuildingDetailsComponent.h"

ABaseCityStructure::ABaseCityStructure(const FObjectInitializer& ObjectInitializer) :
	ABaseStructure(ObjectInitializer) {

	BuildingDetailsComponent = CreateDefaultSubobject<UBuildingDetailsComponent>(TEXT("BuildingDetails"));
}