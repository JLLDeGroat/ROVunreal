// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSlot.h"
#include "../Delegates/CityDelegates.h"
#include "Components/TouchReactComponent.h"
#include "Components/TouchReceiveComponent.h"
#include "Components/SlotConstructorComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Dtos/FCityOverviewDtos.h"
#include "../Interfaces/Building.h"
#include "Structures/BaseCityStructure.h"
#include "Components/BuildingDetailsComponent.h"

// Sets default values
ABuildingSlot::ABuildingSlot(const FObjectInitializer &ObjectInitializer)
	: ABaseStructure(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TouchReceiveComponent = CreateDefaultSubobject<UTouchReceiveComponent>(TEXT("TouchReceive"));
	TouchReceiveComponent->SetBoxExtent(FVector(250, 250, 10));
	RootComponent = TouchReceiveComponent;

	TouchReactComponent = CreateDefaultSubobject<UTouchReactComponent>(TEXT("TouchReact"));

	SlotConstructionComponent = CreateDefaultSubobject<USlotConstructorComponent>(TEXT("SlotConstruction"));

	RopesStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ropes"));
	RopesStaticMeshComponent->SetupAttachment(RootComponent);
	RopesStaticMeshComponent->SetStaticMesh(GetStaticMesh("/Script/Engine.StaticMesh'/Game/Entities/BuildingSlot/Mesh/buildingslot_Cube_004.buildingslot_Cube_004'"));
	RopesStaticMeshComponent->SetRelativeLocation(FVector(-220, -220, 0));
	RopesStaticMeshComponent->SetWorldScale3D(FVector(.2f));

	PolesStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("poles"));
	PolesStaticMeshComponent->SetupAttachment(RootComponent);
	PolesStaticMeshComponent->SetStaticMesh(GetStaticMesh("/Script/Engine.StaticMesh'/Game/Entities/BuildingSlot/Mesh/buildingslot_Cylinder_006.buildingslot_Cylinder_006'"));
	PolesStaticMeshComponent->SetRelativeLocation(FVector(-220, -220, 0));
	PolesStaticMeshComponent->SetWorldScale3D(FVector(.2f));
}

// Called when the game starts or when spawned
void ABuildingSlot::BeginPlay()
{
	Super::BeginPlay();

	auto cityDelegates = UCityDelegates::GetInstance();
	cityDelegates->_OnInitializeBuildingSlot.AddDynamic(this, &ABuildingSlot::OnInitialisedSlot);
	cityDelegates->_OnSuccessBuildBuilding.AddDynamic(this, &ABuildingSlot::OnBuildingSuccessfullyBuilt);
	cityDelegates->_OnSuccessulBuildingUpgrade.AddDynamic(this, &ABuildingSlot::OnBuildingSuccessfullyUpgraded);
}

void ABuildingSlot::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);
	// offset super
	SetActorScale3D(FVector(1));
}

// Called every frame
void ABuildingSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildingSlot::OnInitialisedSlot(int slotId, EBuildingLevelMeshes buildingLevelMesh, EBuildingType buildingType)
{
	UDebugMessages::LogDisplay(this, "OnInitialisedSlot DELEGATE HANDLED");

	if (BuildingSlotId == slotId)
	{
		UDebugMessages::LogDisplay(this, "this is correct OnInitialisedSlot ");
		DeleteBuildingMeshes();
		if (RopesStaticMeshComponent)
		{
			RopesStaticMeshComponent->SetVisibility(false);
			// RopesStaticMeshComponent->DestroyComponent();
		}
		if (PolesStaticMeshComponent)
		{
			PolesStaticMeshComponent->SetVisibility(false);
			// PolesStaticMeshComponent->DestroyComponent();
		}
		if (Building)
		{
			UDebugMessages::LogError(this, "Building already exists here");
			return;
		}

		FTransform transform;
		transform.SetLocation(GetActorLocation());
		auto spawnedBuilding = GetWorld()->SpawnActor<ABaseCityStructure>(SlotConstructionComponent->GetClassFromBuildingType(buildingType), transform);

		if (!spawnedBuilding)
		{
			UDebugMessages::LogError(this, "failed to create building on slot");
			return;
		}

		Building = spawnedBuilding;
		SlotConstructionComponent->SetupBuildingMeshFromLevelCat(spawnedBuilding, buildingLevelMesh);

		if (BuildingSlotId == 99)
		{
			auto gameManager = UROVDataUtils::GetGameManager();
			auto cityDetails = gameManager->GetCityOverviewData();
			auto buildingDetails = Building->GetComponentByClass<UBuildingDetailsComponent>();

			buildingDetails->SetBuildingType(EBuildingType::City);
			buildingDetails->SetLevel(cityDetails->GetCityLevel());
		}
	}
}

void ABuildingSlot::OnBuildingSuccessfullyBuilt(int slotId, EBuildingType buildingType)
{
	if (BuildingSlotId == slotId)
	{
		SlotConstructionComponent->AddInitialConstructionMesh();
	}
}
#pragma optimize("", off)
void ABuildingSlot::OnBuildingSuccessfullyUpgraded(int slotId)
{
	if (slotId == BuildingSlotId)
	{
		if (SlotConstructionComponent)
			SlotConstructionComponent->RemoveConstructionMesh();

		auto gameManager = UROVDataUtils::GetGameManager();

		auto slot = gameManager->GetSlotOverviewBySlotId(slotId);

		auto meshCategory = UROVDataUtils::GetMeshCategoryFromLevel(slot->GetBuilding()->GetLevel());
		OnInitialisedSlot(slotId, meshCategory, slot->GetBuilding()->GetBuildingType());

		auto buildingDetails = Building->GetComponentByClass<UBuildingDetailsComponent>();

		if (!buildingDetails)
		{
			UDebugMessages::LogError(this, "failed to initialise the building");
			return;
		}

		FGuid guid;
		if (FGuid::Parse(slot->GetBuilding()->GetBuildingId(), guid))
			buildingDetails->SetBuildingId(guid);

		buildingDetails->SetBuildingType(slot->GetBuilding()->GetBuildingType());
		buildingDetails->SetLevel(slot->GetBuilding()->GetLevel());
		buildingDetails->SetResourceType(slot->GetBuilding()->GetResourceType());

		if (slot->GetBuilding()->GetIsUpgrading())
		{
			buildingDetails->SetStartTime(slot->GetBuilding()->GetStartTime());
			buildingDetails->SetFinishTime(slot->GetBuilding()->GetFinishTime());
		}
		else
		{
			buildingDetails->ClearStartTime();
			buildingDetails->ClearFinishTime();
		}
	}
}
#pragma optimize("", on)