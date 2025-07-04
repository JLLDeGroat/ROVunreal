// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ROVData/Enums/ROVEnums.h"
#include "WidgetUtils.generated.h"

class UMainCityWidget;
class UResourceCostItemWidget;
class UUserWidget;
class UUnitDetailItem;
class UMainMapWidget;
class UArmyPresenceDetailItemWidget;
class UUnitAttackAmountItemWidget;

UCLASS()
class ROV_API UWidgetUtils : public UObject
{
	GENERATED_BODY()

public:
	static FString GetTimeInHoursMinsSeconds(const FDateTime &StartTime, const FDateTime &EndTime);

	static UMainCityWidget *GetMainCityWidget(UObject *context);
	static UMainMapWidget *GetMainMapWidget(UObject *context);

	static FString GetBuildingNameFromEnum(EBuildingType buildingType);
	static FString GetUnitNameFromEnum(EROVUnitType unitType);

	static bool IsAtMaxLevel(int currentLevel);

	static UResourceCostItemWidget *CreateResourceCostItemWidget(UUserWidget *widget);
	static UUnitDetailItem *CreateUnitDetailItemWidget(UUserWidget *widget);
	static UArmyPresenceDetailItemWidget* CreateArmyPresenceDetailItem(UUserWidget* widget);
	static UUnitAttackAmountItemWidget* CreateArmyAttackItem(UUserWidget* widget);

	// all this method does is call GetResourceTier from IROVGame
	static int GetResourceTier(EResourceType resourceType);
	static int GetBonusStorageFromResource(EResourceType resourceType, int buildingLevel);
};
