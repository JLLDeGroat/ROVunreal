// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStructure.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

// Sets default values
ABaseStructure::ABaseStructure(const FObjectInitializer& ObjectInitializer)
	: AActor(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootSceneComponent;

	BuildingMeshes.Empty();
}

void ABaseStructure::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	SetActorScale3D(FVector(.35f));
}

// Called when the game starts or when spawned
void ABaseStructure::BeginPlay()
{
	Super::BeginPlay();
	UDebugMessages::LogDisplay(this, "ABaseStructure BeginPlay");
}

// Called every frame
void ABaseStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseStructure::LoadAndSetBuildingMesh(FString compName, FString reference, FVector scale, FVector location, FRotator rotation) {
	auto mesh = GetStaticMesh(reference);

	FString fullComponentString = "mesh_" + compName;
	if (CheckMeshExists(fullComponentString)) {
		return;
	}

	auto comp = NewObject<UStaticMeshComponent>(this, FName(fullComponentString));

	comp->RegisterComponent();
	comp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (mesh) {
		comp->SetStaticMesh(mesh);
		comp->SetRelativeScale3D(scale);
		comp->SetRelativeLocation(location);
		comp->SetRelativeRotation(rotation);
		comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AddMeshToBuildingMeshes(comp);
	}
	else {
		UDebugMessages::LogError(this, "failed to load mesh " + reference);
	}
}

void ABaseStructure::DeleteBuildingMeshes() {
	for (int i = 0; i < BuildingMeshes.Num(); i++) {
		if (BuildingMeshes[i]) {
			BuildingMeshes[i]->SetVisibility(false);
			//BuildingMeshes[i]->DestroyComponent();
		}
	}
}

bool ABaseStructure::CheckMeshExists(FString componentName) {
	for (int i = 0; i < BuildingMeshes.Num(); i++) {
		if (BuildingMeshes[i] && BuildingMeshes[i]->GetName() == componentName) {
			UDebugMessages::LogError(this, "comp already exists");
			return true;
		}
	}
	return false;
}

UStaticMesh* ABaseStructure::GetStaticMesh(FString reference) {
	return Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *reference, NULL, LOAD_None, NULL));
}