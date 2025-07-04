// Fill out your copyright notice in the Description page of Project Settings.

#include "ROVDataUtils.h"
#include "../Interfaces/ROVGameData.h"
#include "../Manager/GameDataManager.h"

TScriptInterface<IROVGameData> UROVDataUtils::GetGameManager()
{
	static UGameDataManager *gameManager = 0;
	if (!gameManager)
	{
		gameManager = NewObject<UGameDataManager>();
		gameManager->AddToRoot();
	}

	return gameManager;
}

EBuildingLevelMeshes UROVDataUtils::GetMeshCategoryFromLevel(int level)
{
	if (level == 0)
		return EBuildingLevelMeshes::LV0;

	if (level > 49)
		return EBuildingLevelMeshes::LV50;
	else if (level > 39)
		return EBuildingLevelMeshes::LV40;
	else if (level > 29)
		return EBuildingLevelMeshes::LV30;
	else if (level > 19)
		return EBuildingLevelMeshes::LV20;
	else if (level > 9)
		return EBuildingLevelMeshes::LV10;
	else
		return EBuildingLevelMeshes::LV1;
}