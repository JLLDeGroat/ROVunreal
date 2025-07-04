// Fill out your copyright notice in the Description page of Project Settings.

#include "ROVController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "../Pawns/ROVPawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "InputMappingContext.h"
#include "../Entities/Components/TouchReactComponent.h"
#include "../Delegates/CityDelegates.h"
#include "../Delegates/MapUIDelegates.h"
#include "../Pawns/Components/PawnMapSlotSpawnerComponent.h"
#include "../GameModes/MapGameMode.h"

AROVController::AROVController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	DefaultMappingContext = LoadObject<UInputMappingContext>(this, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Player/PlayerInputMapping.PlayerInputMapping'"));
	SetCameraLocationClickInput = LoadObject<UInputAction>(this, TEXT("/Script/EnhancedInput.InputAction'/Game/Player/InputActions/IA_CameraLocation_Click.IA_CameraLocation_Click'"));
	SetCameraLocationTouchInput = LoadObject<UInputAction>(this, TEXT("/Script/EnhancedInput.InputAction'/Game/Player/InputActions/IA_CameraLocation_Touch.IA_CameraLocation_Touch'"));

	ReactorTouchInput = LoadObject<UInputAction>(this, TEXT("/Script/EnhancedInput.InputAction'/Game/Player/InputActions/IA_ReactSelect_Touch.IA_ReactSelect_Touch'"));

	PreviousLocation = FVector2D::ZeroVector;
	bCanTouchEnvironment = true;
	bCameraMovementOverridesTouchEnvironment = false;

	auto cityDelegates = UCityDelegates::GetInstance();
	if (cityDelegates)
		cityDelegates->_OnAllowUiReactions.AddDynamic(this, &AROVController::OnAllowReaction);

	auto mapDelegates = UMapUIDelegates::GetInstance();
	if (mapDelegates)
		mapDelegates->_OnAllowMapUiReactions.AddDynamic(this, &AROVController::OnAllowReaction);
}

void AROVController::BeginPlay()
{
	Super::BeginPlay();
	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AROVController::EndPlay(const EEndPlayReason::Type endplayReason)
{
	UDebugMessages::LogDisplay(this, "removing delegate OnAllowReaction");
	auto cityDelegates = UCityDelegates::GetInstance();
	if (cityDelegates)
		cityDelegates->_OnAllowUiReactions.RemoveDynamic(this, &AROVController::OnAllowReaction);
}

void AROVController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup touch input events
		EnhancedInputComponent->BindAction(SetCameraLocationTouchInput, ETriggerEvent::Started, this, &AROVController::OnSetCamLocStarted_Touch);
		EnhancedInputComponent->BindAction(SetCameraLocationTouchInput, ETriggerEvent::Triggered, this, &AROVController::OnSetCamLocTriggered_Touch);
		EnhancedInputComponent->BindAction(SetCameraLocationTouchInput, ETriggerEvent::Completed, this, &AROVController::OnSetCamLocReleased_Touch);
		EnhancedInputComponent->BindAction(SetCameraLocationTouchInput, ETriggerEvent::Canceled, this, &AROVController::OnSetCamLocCancelled_Touch);

		EnhancedInputComponent->BindAction(ReactorTouchInput, ETriggerEvent::Started, this, &AROVController::ReactorTouchInputStarted_Touch);
		EnhancedInputComponent->BindAction(ReactorTouchInput, ETriggerEvent::Triggered, this, &AROVController::ReactorTouchInputTriggered_Touch);
		EnhancedInputComponent->BindAction(ReactorTouchInput, ETriggerEvent::Completed, this, &AROVController::ReactorTouchInputReleased_Touch);
		EnhancedInputComponent->BindAction(ReactorTouchInput, ETriggerEvent::Canceled, this, &AROVController::ReactorTouchInputCancelled_Touch);
	}
	else
	{
		UDebugMessages::LogError(this, "Failed to ru, enhanced Input Component");
	}
}

void AROVController::OnSetCamLocStarted_Touch()
{

	float locX, locY;
	bool isPressed;
	GetInputTouchState(ETouchIndex::Touch1, locX, locY, isPressed);

	PreviousLocation = FVector2D(locY, locX);
	StartLocation = PreviousLocation;
}
void AROVController::OnSetCamLocTriggered_Touch()
{

	float locX, locY;
	bool isPressed;
	GetInputTouchState(ETouchIndex::Touch1, locX, locY, isPressed);

	CurrentLocation = FVector2D(locY, locX);

	if (FVector2D::Distance(CurrentLocation, PreviousLocation) > 10 || CameraMovementEnabled)
	{
		bCameraMovementOverridesTouchEnvironment = true;
		CameraMovementEnabled = true;
		auto thisLoc = CurrentLocation - PreviousLocation;
		thisLoc *= -1;
		auto thisLocVector = FVector3d(thisLoc.X * -1, thisLoc.Y, 0);
		GetPawn()->AddActorWorldOffset(thisLocVector);

		PreviousLocation = CurrentLocation;
	}
}
void AROVController::OnSetCamLocReleased_Touch()
{
	OnCameraStopMoving();
}
void AROVController::OnSetCamLocCancelled_Touch()
{
	OnCameraStopMoving();
}

void AROVController::OnCameraStopMoving()
{

	auto distance = FVector2D::Distance(StartLocation, CurrentLocation);
	if (GetWorld()->GetAuthGameMode<AMapGameMode>())
	{
		auto pawn = GetPawn();
		if (distance > 50)
		{
			auto spawnComponent = pawn->GetComponentByClass<UPawnMapSlotSpawnerComponent>();

			auto pawnLoc = pawn->GetActorLocation();
			int32 gridX = FMath::RoundToInt(pawnLoc.X / 50.0f);
			int32 gridY = FMath::RoundToInt(pawnLoc.Y / 50.0f);

			spawnComponent->SpawnSlotsAroundLoc(gridX, gridY);
		}
	}

	CameraMovementEnabled = false;
	PreviousLocation = FVector2D(0);
	CurrentLocation = FVector2D(0);
}

void AROVController::ReactorTouchInputStarted_Touch()
{
}
void AROVController::ReactorTouchInputTriggered_Touch()
{
}
void AROVController::ReactorTouchInputReleased_Touch()
{
	if (bCameraMovementOverridesTouchEnvironment)
	{
		bCameraMovementOverridesTouchEnvironment = false;
		return;
	}
	FHitResult Hit;

	float locX, locY;
	bool isPressed;
	GetInputTouchState(ETouchIndex::Touch1, locX, locY, isPressed);
	GetHitResultAtScreenPosition(FVector2D(locX, locY), ECC_GameTraceChannel1, false, Hit);

	if (Hit.bBlockingHit && Hit.GetActor())
	{
		UDebugMessages::LogDisplay(this, Hit.GetActor()->GetName());
		auto touchComp = Hit.GetActor()->GetComponentByClass<UTouchReactComponent>();

		if (touchComp && bCanTouchEnvironment)
		{
			touchComp->ReactToTouch();
			bCanTouchEnvironment = false;
			UDebugMessages::LogDisplay(this, "reacting to touch");
		}
		else
			UDebugMessages::LogDisplay(this, "cannot react to touch, already reacting");
	}
}
void AROVController::ReactorTouchInputCancelled_Touch()
{
	UDebugMessages::LogDisplay(this, "ReactorTouchInput Cancelled");
}

void AROVController::OnAllowReaction()
{
	bCanTouchEnvironment = true;
}
