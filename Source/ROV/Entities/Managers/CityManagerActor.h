// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "CityManagerActor.generated.h"

class IGatewayClient;

UCLASS()
class ROV_API ACityManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACityManagerActor();

	UFUNCTION() void InitializeCity();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION() void RequestUpdatedResourceCount();
private:

	EBuildingLevelMeshes GetCategoryOnLevel(int level);

	UPROPERTY() TScriptInterface<IGatewayClient> GatewayClient;
	FTimerHandle ResourceUpdateHandle;
	UPROPERTY() bool bIsCallingForResources;
};
