// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceBuildingDetails.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../../Entities/Components/BuildingDetailsComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "../../../Utilities/WidgetUtils.h"
#include "../../../Domain/Client/ROVClient.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "JsonObjectConverter.h"
#include "../ComponentWidgets/CityProgressItemWidget.h"

void UResourceBuildingDetails::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UResourceBuildingDetails::SetupForBuilding(AActor *buildingActor)
{
	BaseSetup(buildingActor);

	ProgressItem->SetVisibility(ESlateVisibility::Hidden);
	SetResourceSectionVisibility(ESlateVisibility::Hidden);
	SetUpgradeWidgetVisibility(ESlateVisibility::Hidden);

	auto buildingDetails = buildingActor->GetComponentByClass<UBuildingDetailsComponent>();
	if (!buildingDetails)
		return UDebugMessages::LogError(this, "failed to get building details component");

	if (buildingDetails->GetIsUpgrading())
	{
		ProgressItem->SetVisibility(ESlateVisibility::Visible);
		ProgressItem->SetProgressValues(buildingDetails->GetStartTime(), buildingDetails->GetFinishTime(),
										buildingDetails->GetBuildingType(), buildingDetails->GetBuildingId());
		UpdateProgressWidgetsCallback();
	}
	else
	{
		SetResourceSectionVisibility(ESlateVisibility::Visible);
		SetUpgradeWidgetVisibility(ESlateVisibility::Visible);
		auto gameManager = UROVDataUtils::GetGameManager();

		auto hourlyAmount = gameManager->GetHourlyAmount(buildingDetails->GetLevel(),
														 gameManager->GetResourceTier(buildingDetails->GetResourceType()));

		auto bonusStorage = UWidgetUtils::GetBonusStorageFromResource(buildingDetails->GetResourceType(), buildingDetails->GetLevel());

		Rate->SetText(FText::FromString(FString::SanitizeFloat(hourlyAmount, 0) + " ph"));
		Description->SetText(FText::FromString(gameManager->GetBuildingDescription(buildingDetails->GetBuildingType())));
		StorageBonus->SetText(FText::FromString(FString::SanitizeFloat(bonusStorage, 0) + " Extra Storage"));
	}
}

void UResourceBuildingDetails::SetResourceSectionVisibility(ESlateVisibility visibility)
{
	Rate->SetVisibility(visibility);
	Description->SetVisibility(visibility);
}