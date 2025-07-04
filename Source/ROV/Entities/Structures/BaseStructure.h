// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStructure.generated.h"

class UStaticComponent;

UCLASS()
class ROV_API ABaseStructure : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseStructure(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) USceneComponent* RootSceneComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<UStaticMeshComponent*> BuildingMeshes;

	FORCEINLINE void AddMeshToBuildingMeshes(UStaticMeshComponent* meshComponent) {
		BuildingMeshes.Emplace(meshComponent);
	}

	void LoadAndSetBuildingMesh(FString compName, FString reference, FVector scale = FVector(1), FVector location = FVector::ZeroVector, FRotator rotation = FRotator::ZeroRotator);
	UStaticMesh* GetStaticMesh(FString reference);
	void DeleteBuildingMeshes();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool CheckMeshExists(FString componentName);

};
