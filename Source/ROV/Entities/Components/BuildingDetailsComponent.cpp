// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingDetailsComponent.h"
#include "../../Delegates/CityDelegates.h"

// Sets default values for this component's properties
UBuildingDetailsComponent::UBuildingDetailsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UBuildingDetailsComponent::BeginPlay()
{
	Super::BeginPlay();

	auto cityDelegates = UCityDelegates::GetInstance();
	if (cityDelegates)
	{
		cityDelegates->_OnStartBuildingUpgrade.AddDynamic(this, &UBuildingDetailsComponent::OnStartBuildingUpgrade);
	}
}

void UBuildingDetailsComponent::OnStartBuildingUpgrade(FGuid BuildingId, FDateTime Start, FDateTime End)
{
	if (Id == BuildingId)
	{
		StartTime = Start;
		FinishTime = End;
	}
}