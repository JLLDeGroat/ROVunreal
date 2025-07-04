// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/BaseStructure.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "ROVData/Enums/ROVEnums.h"
#include "../Interfaces/Slot.h"
#include "BuildingSlot.generated.h"

class UTouchReactComponent;
class USlotConstructorComponent;
class UTouchReceiveComponent;
class IBuilding;

UCLASS()
class ROV_API ABuildingSlot : public ABaseStructure, public ISlot
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingSlot(const FObjectInitializer &ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform &Transform) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTouchReceiveComponent *TouchReceiveComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTouchReactComponent *TouchReactComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USlotConstructorComponent *SlotConstructionComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent *RopesStaticMeshComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent *PolesStaticMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BuildingSlotId;

	UFUNCTION(/*CallInEditor*/)
	void OnInitialisedSlot(int slotId, EBuildingLevelMeshes buildingLevelMesh, EBuildingType buildingType);
	UFUNCTION(/*CallInEditor*/)
	void OnBuildingSuccessfullyBuilt(int slotId, EBuildingType buildingType);
	UFUNCTION(/*CallInEditor*/)
	void OnBuildingSuccessfullyUpgraded(int slotId);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual int GetSlotNumber() override { return BuildingSlotId; }
	virtual AActor *GetBuilding() override { return Building; }

private:
	UPROPERTY()
	AActor *Building;
};
