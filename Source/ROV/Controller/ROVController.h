// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ROVController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
/**
 *
 */
UCLASS()
class ROV_API AROVController : public APlayerController
{
	GENERATED_BODY()

public:
	AROVController();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endplayReason) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *SetCameraLocationClickInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *SetCameraLocationTouchInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *ReactorClickInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *ReactorTouchInput;

	/** Input handlers for SetDestination action. */

	void OnSetCamLocStarted_Click();
	void OnSetCamLocTriggered_Click();
	void OnSetCamLocReleased_Click();
	void OnSetCamLocCancelled_Click();

	void OnCameraStopMoving();

	void OnSetCamLocStarted_Touch();
	void OnSetCamLocTriggered_Touch();
	void OnSetCamLocReleased_Touch();
	void OnSetCamLocCancelled_Touch();

	void ReactorTouchInputStarted_Touch();
	void ReactorTouchInputTriggered_Touch();
	void ReactorTouchInputReleased_Touch();
	void ReactorTouchInputCancelled_Touch();

	UFUNCTION()
	void OnAllowReaction();

protected:
	UPROPERTY()
	FVector2D StartLocation;
	UPROPERTY()
	FVector2D PreviousLocation;
	UPROPERTY()
	FVector2D CurrentLocation;
	UPROPERTY()
	bool CameraMovementEnabled;

	UPROPERTY()
	bool bCameraMovementOverridesTouchEnvironment;
	UPROPERTY()
	bool bCanTouchEnvironment;
};
