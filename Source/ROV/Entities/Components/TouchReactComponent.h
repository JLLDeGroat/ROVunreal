// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TouchReactComponent.generated.h"

class ISlot;
class IBuilding;
class AMapSlot;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROV_API UTouchReactComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTouchReactComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReactToTouch();

private:

	void ReactToSlotTouch(TScriptInterface<ISlot> slot);
	void ReactToBuildingTouch(AActor* building);
	void ReactToMapSlot(AMapSlot* mapSlot);
};
