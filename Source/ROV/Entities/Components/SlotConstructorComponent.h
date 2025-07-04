// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "SlotConstructorComponent.generated.h"

class IBuilding;
class AInitialConstruction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROV_API USlotConstructorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USlotConstructorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UClass* GetClassFromBuildingType(EBuildingType buildingType);
	void SetupBuildingMeshFromLevelCat(TScriptInterface<IBuilding> building, EBuildingLevelMeshes buildingLevelMesh);

	void AddInitialConstructionMesh();
	void RemoveConstructionMesh();
protected:

	UPROPERTY() AInitialConstruction* ConstructionMesh;

};
