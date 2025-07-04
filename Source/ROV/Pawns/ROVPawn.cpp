// Fill out your copyright notice in the Description page of Project Settings.

#include "ROVPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PawnMapSpawnComponent.h"
#include "Components/PawnMapSlotSpawnerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "../GameModes/MapGameMode.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

// Sets default values
AROVPawn::AROVPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArmComponent->TargetArmLength = 800.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	MapSpawnComponent = CreateDefaultSubobject<UPawnMapSpawnComponent>(TEXT("MapSpawn"));
	MapSlotSpawnerComponent = CreateDefaultSubobject<UPawnMapSlotSpawnerComponent>(TEXT("SlotSpawner"));
}

// Called when the game starts or when spawned
void AROVPawn::BeginPlay()
{
	Super::BeginPlay();

	auto world = GetWorld();
	if (!world)
		return UDebugMessages::LogError(this, "failed to get world");

	auto gameMode = world->GetAuthGameMode<AMapGameMode>();
	if (gameMode)
	{
		SpringArmComponent->TargetArmLength = 250.f;
	}
}

// Called every frame
void AROVPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AROVPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AROVPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	MapSlotSpawnerComponent->CloseAllThreads();
}