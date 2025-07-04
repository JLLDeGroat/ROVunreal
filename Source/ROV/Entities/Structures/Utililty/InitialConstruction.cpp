// Fill out your copyright notice in the Description page of Project Settings.


#include "InitialConstruction.h"
#include "Components/StaticMeshComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

AInitialConstruction::AInitialConstruction(const FObjectInitializer& ObjectInitializer)
	: ABaseStructure(ObjectInitializer) {

	TableComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh"));
	RootComponent = TableComponent;
	TableComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//TableComponent->SetRelativeLocation(FVector(-220, -220, 0));

	PlanksComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanksMesh"));
	PlanksComponent->SetupAttachment(RootComponent);
	PlanksComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*PlanksComponent->SetWorldScale3D(FVector(.2f));*/

	Table2Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh2"));
	Table2Component->SetupAttachment(RootComponent);
	Table2Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//TableComponent->SetRelativeLocation(FVector(-220, -220, 0));

	Planks2Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanksMesh2"));
	Planks2Component->SetupAttachment(Table2Component);
	Planks2Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*PlanksComponent->SetWorldScale3D(FVector(.2f));*/

	Table3Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh3"));
	Table3Component->SetupAttachment(RootComponent);
	Table3Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//TableComponent->SetRelativeLocation(FVector(-220, -220, 0));

	Planks3Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanksMesh3"));
	Planks3Component->SetupAttachment(Table3Component);
	Planks3Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*PlanksComponent->SetWorldScale3D(FVector(.2f));*/

	Table4Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh4"));
	Table4Component->SetupAttachment(RootComponent);
	Table4Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//TableComponent->SetRelativeLocation(FVector(-220, -220, 0));

	Planks4Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanksMesh4"));
	Planks4Component->SetupAttachment(Table4Component);
	Planks4Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*PlanksComponent->SetWorldScale3D(FVector(.2f));*/

	Table5Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh5"));
	Table5Component->SetupAttachment(RootComponent);
	Table5Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//TableComponent->SetRelativeLocation(FVector(-220, -220, 0));

	Planks5Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanksMesh5"));
	Planks5Component->SetupAttachment(Table5Component);
	Planks5Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*PlanksComponent->SetWorldScale3D(FVector(.2f));*/
}

void AInitialConstruction::BeginPlay() {
	Super::BeginPlay();
}

void AInitialConstruction::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	auto tableMesh = GetStaticMesh("/Script/Engine.StaticMesh'/Game/Entities/BuildingSlot/Mesh/buildingslot_IC_Table.buildingslot_IC_Table'");
	if (tableMesh) {
		TableComponent->SetStaticMesh(tableMesh);
		Table2Component->SetStaticMesh(tableMesh);
		Table3Component->SetStaticMesh(tableMesh);
		Table4Component->SetStaticMesh(tableMesh);
		Table5Component->SetStaticMesh(tableMesh);

		Table2Component->SetRelativeLocation(FVector(-2000, -1800, 0));
		Table3Component->SetRelativeLocation(FVector(1300, -1100, 0));
		Table4Component->SetRelativeLocation(FVector(2400, 800, 0));
		Table5Component->SetRelativeLocation(FVector(-1800, 200, 0));

		Table2Component->SetRelativeRotation(FRotator(0, 42, 0));
		Table3Component->SetRelativeRotation(FRotator(0, 121, 0));
		Table4Component->SetRelativeRotation(FRotator(0, 270, 0));
		Table5Component->SetRelativeRotation(FRotator(0, 10, 0));
	}

	auto plankMesh = GetStaticMesh("/Script/Engine.StaticMesh'/Game/Entities/BuildingSlot/Mesh/buildingslot_IC_Planks.buildingslot_IC_Planks'");
	if (plankMesh) {
		PlanksComponent->SetStaticMesh(plankMesh);
		Planks2Component->SetStaticMesh(plankMesh);
		Planks3Component->SetStaticMesh(plankMesh);
		Planks4Component->SetStaticMesh(plankMesh);
		Planks5Component->SetStaticMesh(plankMesh);

		PlanksComponent->SetRelativeLocation(FVector(0, -100, 100));
		Planks2Component->SetRelativeLocation(FVector(0, -100, 100));
		Planks3Component->SetRelativeLocation(FVector(0, -100, 100));
		Planks4Component->SetRelativeLocation(FVector(0, -100, 100));
		Planks5Component->SetRelativeLocation(FVector(0, -100, 100));
	}

	TableComponent->SetWorldScale3D(FVector(.05f));
	PlanksComponent->SetWorldScale3D(FVector(.05f));
	Table2Component->SetWorldScale3D(FVector(.05f));
	Planks2Component->SetWorldScale3D(FVector(.05f));
	Table3Component->SetWorldScale3D(FVector(.05f));
	Planks3Component->SetWorldScale3D(FVector(.05f));
	Table4Component->SetWorldScale3D(FVector(.05f));
	Planks4Component->SetWorldScale3D(FVector(.05f));
	Table5Component->SetWorldScale3D(FVector(.05f));
	Planks5Component->SetWorldScale3D(FVector(.05f));
}