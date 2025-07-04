// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Interfaces/ROVGameData.h"
#include "../Enums/ROVUtilEnums.h"
#include "ROVDataUtils.generated.h"

/**
 * 
 */
UCLASS()
class ROVDATA_API UROVDataUtils : public UObject
{
	GENERATED_BODY()
	
public:

	static TScriptInterface<IROVGameData> GetGameManager(); 

	static EBuildingLevelMeshes GetMeshCategoryFromLevel(int level);
};
