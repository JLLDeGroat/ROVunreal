// Fill out your copyright notice in the Description page of Project Settings.


#include "CityProgressItemWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "../../../Utilities/WidgetUtils.h"
#include "ROVData/Dtos/FBuildingDtos.h"
#include "../../../Domain/Client/ROVClient.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "../../../Delegates/CityDelegates.h"

void UCityProgressItemWidget::NativeConstruct() {
	Super::NativeConstruct();

	GatewayClient = NewObject<UROVClient>();
}


void UCityProgressItemWidget::SetProgressValues(FDateTime startTime, FDateTime finishTime, EBuildingType buildingType, FGuid buildingId) {
	StartTime = startTime;
	FinishTime = finishTime;
	BuildingType = buildingType;
	Id = buildingId;

	ProgressName->SetText(FText::FromString(ROVEnums::BuildingTypeAsString(buildingType)));
}
void UCityProgressItemWidget::SetProgressValues(FDateTime startTime, FDateTime finishTime, EROVUnitType unitType, FGuid buildingId, int amount) {
	StartTime = startTime;
	FinishTime = finishTime;
	UnitType = unitType;
	Id = buildingId;
	Amount = amount;

	ProgressName->SetText(FText::FromString(ROVEnums::UnitAsString(unitType) + " x" + FString::SanitizeFloat(amount, 0)));
}

void UCityProgressItemWidget::CalculateProgress() {
	FDateTime now = FDateTime::UtcNow();

	auto totalSeconds = (FinishTime - StartTime).GetTotalSeconds();
	auto secondsTillCompletion = (FinishTime - now).GetTotalSeconds();

	auto secondProgress = totalSeconds - secondsTillCompletion;

	if (secondsTillCompletion <= 0 && !bCheckingOnResult) {
		ProgressBar->SetPercent(1);
		UDebugMessages::LogDisplay(this, "calculate progress complete");
		bCheckingOnResult = true;
		if (BuildingType != EBuildingType::INVALID) {
			CheckOnBuildingComplete();
		}
		else if (UnitType != EROVUnitType::INVALID) {
			CheckOnTrainingComplete();
		}
	}

	float percentage = (float)secondProgress / (float)totalSeconds;
	ProgressBar->SetPercent(percentage);
	ProgressTime->SetText(FText::FromString(UWidgetUtils::GetTimeInHoursMinsSeconds(FDateTime::UtcNow(), FinishTime)));
}

void UCityProgressItemWidget::CheckOnBuildingComplete() {
	auto gameManager = UROVDataUtils::GetGameManager();
	GatewayClient->GetBuildingDetails(gameManager->GetCityOverviewData()->GetCityId(), Id.ToString(EGuidFormats::DigitsWithHyphens), [this](FString content)
		{
			FApiDto apiDto;
			FBuildingDetailsResponseDto result;

			GatewayClient->GetResultAsApiDto(content, &apiDto);
			if (UFileManagementUtilities::JsonToStruct(apiDto.GetPayload(), &result)) {
				if (!result.GetIsUpgrading()) {
					auto gameManager = UROVDataUtils::GetGameManager();
					auto slot = gameManager->GetSlotOverviewByBuildingId(Id);

					if (slot->GetBuilding())
						slot->GetBuilding()->LevelUp();
					else
						slot->AddBuilding(BuildingType, Id.ToString(EGuidFormats::DigitsWithHyphens), result.GetCurrentLevel());

					auto cityDelegate = UCityDelegates::GetInstance();
					if (!cityDelegate)
						return UDebugMessages::LogError(this, "failed to get city delegates");

					cityDelegate->_OnSuccessulBuildingUpgrade.Broadcast(slot->GetSlot());

					bIsComplete = true;
				}
			}
			else {
				UDebugMessages::LogError(this, "UCityProgressItemWidget::CheckOnBuildingComplete Failed to get Json");
			}
			bCheckingOnResult = false;
		});
}

void UCityProgressItemWidget::CheckOnTrainingComplete() {
	bIsComplete = true;
}

bool UCityProgressItemWidget::GetIsComplete() {
	return bIsComplete;
}