// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "BuildingDetailsComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROV_API UBuildingDetailsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBuildingDetailsComponent();
	virtual void BeginPlay() override;

	FGuid GetBuildingId() { return Id; }
	void SetBuildingId(FGuid id) { Id = id; }

	void SetLevel(int level) { Level = level; }
	int GetLevel() { return Level; }

	void SetBuildingType(EBuildingType type) { BuildingType = type; }
	EBuildingType GetBuildingType() { return BuildingType; }

	void SetResourceType(EResourceType rType) { ResourceType = rType; }
	EResourceType GetResourceType() { return ResourceType; }

	bool GetIsResourceBuilding() { return ResourceType != EResourceType::INVALID; }
	bool GetIsTrainingBuilding() { return BuildingType == EBuildingType::Barracks; }
	bool GetIsCityBuilding() { return BuildingType == EBuildingType::City; }

	void SetStartTime(FDateTime dateTime) { StartTime = dateTime; }
	void SetFinishTime(FDateTime dateTime) { FinishTime = dateTime; }

	void ClearStartTime() { StartTime = FDateTime(0); }
	void ClearFinishTime() { FinishTime = FDateTime(0); }

	bool GetIsUpgrading() { return StartTime.GetTicks() > 0 && FinishTime.GetTicks() > 0; }

	FDateTime GetStartTime() { return StartTime; }
	FDateTime GetFinishTime() { return FinishTime; }

protected:
	UFUNCTION()
	void OnStartBuildingUpgrade(FGuid BuildingId, FDateTime Start, FDateTime End);

	UPROPERTY()
	FGuid Id;
	UPROPERTY()
	EBuildingType BuildingType;
	UPROPERTY()
	EResourceType ResourceType;
	UPROPERTY()
	int Level;

	UPROPERTY()
	FDateTime StartTime;
	UPROPERTY()
	FDateTime FinishTime;
};
