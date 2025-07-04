// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetUtils.h"
#include "../HUD/City/MainCityWidget.h"
#include "../HUD/Map/MainMapWidget.h"
#include "../HUD/RovHud.h"
#include "../HUD/RovMapHud.h"
#include "../Controller/ROVController.h"
#include "../HUD/City/ComponentWidgets/ResourceCostItemWidget.h"
#include "../HUD/City/Building/Components/UnitDetailItem.h"
#include "../HUD/Map/Slots/Components/ArmyPresenceDetailItemWidget.h"
#include "../HUD/Map/Slots/Components/UnitAttackAmountItemWidget.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"

FString UWidgetUtils::GetTimeInHoursMinsSeconds(const FDateTime &StartTime, const FDateTime &EndTime)
{
	// Calculate the time difference between the start and end times
	FTimespan TimeDifference = EndTime - StartTime;

	// Extract days, hours, minutes, and seconds from the difference
	int32 TotalDays = TimeDifference.GetDays();
	int32 TotalHours = TimeDifference.GetHours();
	int32 TotalMinutes = TimeDifference.GetMinutes();
	int32 TotalSeconds = TimeDifference.GetSeconds();

	FString FormattedTime;

	// Only include days if not zero
	if (TotalDays > 0)
	{
		FormattedTime += FString::Printf(TEXT("%d:"), TotalDays);
	}

	// Only include hours if not zero
	if (TotalHours > 0)
	{
		FormattedTime += FString::Printf(TEXT("%d:"), TotalHours);
	}

	// Only include minutes if not zero
	if (TotalMinutes > 0)
	{
		FormattedTime += FString::Printf(TEXT("%d:"), TotalMinutes);
	}

	// Only include seconds if not zero
	if (TotalSeconds > 0)
	{
		// FString str = TotalSeconds >= 10 ? FString::SanitizeFloat(TotalSeconds, 0) : "0" + FString::SanitizeFloat(TotalSeconds, 0);
		// FormattedTime += FString::Printf(TEXT("%d"), str);
		FormattedTime += TotalSeconds >= 10 ? FString::SanitizeFloat(TotalSeconds, 0) : "0" + FString::SanitizeFloat(TotalSeconds, 0);
	}

	// Remove the trailing slash if present
	FormattedTime.RemoveFromEnd(TEXT("/"));

	return FormattedTime;
}

UMainCityWidget *UWidgetUtils::GetMainCityWidget(UObject *context)
{
	auto controller = context->GetWorld()->GetFirstPlayerController();
	auto hud = controller->GetHUD<ARovHud>();
	return hud->GetMainCityWidget();
}

UMainMapWidget *UWidgetUtils::GetMainMapWidget(UObject *context)
{
	auto controller = context->GetWorld()->GetFirstPlayerController();
	auto hud = controller->GetHUD<ARovMapHud>();
	return hud->GetMainMapWidget();
}

FString UWidgetUtils::GetBuildingNameFromEnum(EBuildingType buildingType)
{
	switch (buildingType)
	{
	case EBuildingType::IronDigger:
		return "Iron Digger";
	case EBuildingType::Barracks:
		return "Barracks";
	case EBuildingType::ChemicalPlant:
		return "Chemical Plant";
	case EBuildingType::Chiseler:
		return "Chiseler";
	case EBuildingType::City:
		return "City";
	case EBuildingType::CityWall:
		return "Walls";
	case EBuildingType::CopperDigger:
		return "Copper Mine";
	case EBuildingType::CropHouse:
		return "Crop House";
	case EBuildingType::Heater:
		return "Heater";
	case EBuildingType::Jeweler:
		return "Jeweler";
	case EBuildingType::Mulcher:
		return "Mulcher";
	case EBuildingType::PeatreeDish:
		return "Pea Tree Dish";
	case EBuildingType::SlaughterHouse:
		return "Slaughter House";
	case EBuildingType::SoulQuarrey:
		return "Soul Quarrey";
	case EBuildingType::TinDigger:
		return "Tin Digger";
	case EBuildingType::TreeRipper:
		return "Tree Ripper";

	default:
		return "UNDEFINED";
	}
}

FString UWidgetUtils::GetUnitNameFromEnum(EROVUnitType unitType)
{
	switch (unitType)
	{
	case EROVUnitType::CeleryStickman:
		return "Celery Stick-man";
	case EROVUnitType::Peasant:
		return "Peasant";
	case EROVUnitType::ArrowRoot:
		return "Arrow Root";

	default:
		return "UNDEFINED";
	}
}

bool UWidgetUtils::IsAtMaxLevel(int currentLevel)
{
	return currentLevel >= 50;
}

UResourceCostItemWidget *UWidgetUtils::CreateResourceCostItemWidget(UUserWidget *widget)
{
	FSoftClassPath hudUIRef("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/ComponentWidgets/ResourceCostItem_Bp.ResourceCostItem_Bp_C'");
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UResourceCostItemWidget>())
		return CreateWidget<UResourceCostItemWidget>(widget, hudUIWidgetClass);

	return nullptr;
}

UUnitDetailItem *UWidgetUtils::CreateUnitDetailItemWidget(UUserWidget *widget)
{
	FSoftClassPath hudUIRef("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/Buildings/Components/UnitDetailItem_Bp.UnitDetailItem_Bp_C'");
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UUnitDetailItem>())
		return CreateWidget<UUnitDetailItem>(widget, hudUIWidgetClass);

	return nullptr;
}

UArmyPresenceDetailItemWidget *UWidgetUtils::CreateArmyPresenceDetailItem(UUserWidget *widget)
{
	FSoftClassPath hudUIRef("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/Map/Slots/Components/ArmyPresenceDetailItemWidget_Bp.ArmyPresenceDetailItemWidget_Bp_C'");
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UArmyPresenceDetailItemWidget>())
		return CreateWidget<UArmyPresenceDetailItemWidget>(widget, hudUIWidgetClass);

	return nullptr;
}

UUnitAttackAmountItemWidget *UWidgetUtils::CreateArmyAttackItem(UUserWidget *widget)
{
	FSoftClassPath hudUIRef("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/Map/Slots/Components/UnitAttackAmountItemWidget_Bp.UnitAttackAmountItemWidget_Bp_C'");
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UUnitAttackAmountItemWidget>())
		return CreateWidget<UUnitAttackAmountItemWidget>(widget, hudUIWidgetClass);

	return nullptr;
}

int UWidgetUtils::GetResourceTier(EResourceType resourceType)
{
	auto gameManager = UROVDataUtils::GetGameManager();
	return gameManager->GetResourceTier(resourceType);
}
int UWidgetUtils::GetBonusStorageFromResource(EResourceType resourceType, int buildingLevel)
{
	int tier = GetResourceTier(resourceType);

	int baseAmount = buildingLevel * (2000 / tier);

	if (buildingLevel > 40)
		baseAmount += 3000 / tier;
	if (buildingLevel > 30)
		baseAmount += 3000 / tier;
	if (buildingLevel > 20)
		baseAmount += 3000 / tier;
	if (buildingLevel > 10)
		baseAmount += 3000 / tier;

	return baseAmount;
}