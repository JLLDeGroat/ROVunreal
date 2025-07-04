// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ROVPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPawnMapSpawnComponent;
class UPawnMapSlotSpawnerComponent;

UCLASS()
class ROV_API AROVPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AROVPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UCameraComponent* CameraComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPawnMapSpawnComponent* MapSpawnComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPawnMapSlotSpawnerComponent* MapSlotSpawnerComponent;

	void EndPlay(const EEndPlayReason::Type EndPlayReason);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
