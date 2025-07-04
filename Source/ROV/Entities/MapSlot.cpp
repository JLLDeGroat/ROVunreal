// Fill out your copyright notice in the Description page of Project Settings.

#include "MapSlot.h"
#include "Components/BoxComponent.h"
#include "Components/TouchReactComponent.h"
#include "Components/TouchReceiveComponent.h"

// Sets default values
AMapSlot::AMapSlot(const FObjectInitializer &ObjectInitializer)
    : AActor(ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    TouchReceiveComponent = CreateDefaultSubobject<UTouchReceiveComponent>(TEXT("TouchReceive"));
    RootComponent = TouchReceiveComponent;

    TouchReactComponent = CreateDefaultSubobject<UTouchReactComponent>(TEXT("TouchReact"));

    DebugBoxComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    DebugBoxComponent->SetupAttachment(RootComponent);
    DebugBoxComponent->SetStaticMesh(GetStaticMesh("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
}

// Called when the game starts or when spawned
void AMapSlot::BeginPlay()
{
    Super::BeginPlay();
}

void AMapSlot::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);

    TouchReceiveComponent->SetBoxExtent(FVector(25, 25, 10));
    TouchReceiveComponent->SetVisibility(true);
    TouchReceiveComponent->bHiddenInGame = false;
    DebugBoxComponent->SetWorldScale3D(FVector(0.5f));
}

UStaticMesh *AMapSlot::GetStaticMesh(FString reference)
{
    return Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *reference, NULL, LOAD_None, NULL));
}

void AMapSlot::SetupOccupation(EOccupiedType occupationType)
{
    OccupationType = occupationType;
    FString reference = "/Script/Engine.Material'/Game/Materials/EmptySlot_M.EmptySlot_M'";
    if (OccupationType == EOccupiedType::INVALID)
    {
        reference = "/Script/Engine.Material'/Game/Materials/EmptySlot_M.EmptySlot_M'";
    }

    if (OccupationType == EOccupiedType::PlayerCity)
    {
        reference = "/Script/Engine.Material'/Game/Materials/CitySlot_M.CitySlot_M'";
    }

    if (OccupationType == EOccupiedType::AICity)
    {
        reference = "/Script/Engine.Material'/Game/Materials/AiCityClot_M.AiCityClot_M'";
    }

    auto emptyMat = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *reference, NULL, LOAD_None, NULL));

    DebugBoxComponent->SetMaterial(0, emptyMat);
}

EOccupiedType AMapSlot::GetOccupationType()
{
    return OccupationType;
}

void AMapSlot::SetUid(FString uid)
{
    Uid = uid;
}
FString AMapSlot::GetUid()
{
    return Uid;
}