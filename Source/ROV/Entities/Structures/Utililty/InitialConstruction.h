// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseStructure.h"
#include "InitialConstruction.generated.h"

class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class ROV_API AInitialConstruction : public ABaseStructure
{
	GENERATED_BODY()

public:

	AInitialConstruction(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* TableComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* PlanksComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Table2Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Planks2Component;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Table3Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Planks3Component;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Table4Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Planks4Component;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Table5Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* Planks5Component;
	
};
