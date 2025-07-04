// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotConstructorComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../../Interfaces/Building.h"
#include "../Structures/City/City.h"
#include "../Structures/City/SlaughterHouse.h"
#include "../Structures/Utililty/InitialConstruction.h"
#include "../Structures/City/Barracks.h"
#include "../Structures/City/SoulQuarrey.h"
#include "../Structures/City/Chiseler.h"

// Sets default values for this component's properties
USlotConstructorComponent::USlotConstructorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USlotConstructorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void USlotConstructorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UClass *USlotConstructorComponent::GetClassFromBuildingType(EBuildingType buildingType)
{
	UClass *clss = nullptr;
	switch (buildingType)
	{
	case EBuildingType::City:
		clss = ACity::StaticClass();
		break;
	case EBuildingType::SlaughterHouse:
		clss = ASlaughterHouse::StaticClass();
		break;
	case EBuildingType::Barracks:
		clss = ABarracks::StaticClass();
		break;
	case EBuildingType::SoulQuarrey:
		clss = ASoulQuarrey::StaticClass();
		break;
	case EBuildingType::Chiseler:
		clss = AChiseler::StaticClass();
		break;

	default:
		UDebugMessages::LogError(this, "no buildingtype found USlotConstructorComponent::GetClassFromBuildingType");
	}

	check(clss);

	return clss;
}

void USlotConstructorComponent::SetupBuildingMeshFromLevelCat(TScriptInterface<IBuilding> building, EBuildingLevelMeshes buildingLevelMesh)
{
	switch (buildingLevelMesh)
	{
	case EBuildingLevelMeshes::LV0:
		AddInitialConstructionMesh();
		break;
	case EBuildingLevelMeshes::LV1:
		building->PrepareLevelOne();
		break;

	default:
		UDebugMessages::LogError(this, "no levelMesh set for building USlotConstructorComponent::SetupBuildingMeshFromLevelCat");
		break;
	}
}

void USlotConstructorComponent::AddInitialConstructionMesh()
{
	auto owner = GetOwner();
	auto world = owner->GetWorld();

	if (world)
	{
		if (ConstructionMesh)
			RemoveConstructionMesh();

		ConstructionMesh = world->SpawnActor<AInitialConstruction>(owner->GetActorLocation(), FRotator(0));

		if (ConstructionMesh)
			UDebugMessages::LogDisplay(this, "spawned new construction mesh");
	}
}
void USlotConstructorComponent::RemoveConstructionMesh()
{
	if (ConstructionMesh)
		ConstructionMesh->Destroy();
}
