// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROVData/Enums/ROVUtilEnums.h"
#include "ROVData/Enums/ROVEnums.h"
#include "MapSlot.generated.h"

class UTouchReactComponent;
class UTouchReceiveComponent;
class UBoxComponent;

UCLASS()
class ROV_API AMapSlot : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMapSlot(const FObjectInitializer &ObjectInitializer);

    FORCEINLINE int GetX() { return X; }
    FORCEINLINE int GetY() { return Y; }

    void SetXAndY(int x, int y)
    {
        X = x;
        Y = y;
    }

    void SetupOccupation(EOccupiedType occupationType);
    EOccupiedType GetOccupationType();

    void SetUid(FString uid);
    FString GetUid();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform &Transform) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UTouchReactComponent *TouchReactComponent;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UTouchReceiveComponent *TouchReceiveComponent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UStaticMeshComponent *DebugBoxComponent;

    UStaticMesh *GetStaticMesh(FString reference);

    UPROPERTY()
    int X;
    UPROPERTY()
    int Y;
    UPROPERTY()
    EOccupiedType OccupationType;
    UPROPERTY()
    FString Uid;

public:
    // Called every frame

private:
};
