// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainingBuildingDetails.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "../../../Entities/Components/BuildingDetailsComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../ComponentWidgets/CityProgressItemWidget.h"
#include "../../../Domain/Client/ROVClient.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "Components/TextBlock.h"
#include "VgFlmngmnt/Domain/FileManagementUtilities.h"
#include "Components/ScrollBox.h"
#include "Components/TrainingItemWidget.h"
#include "../../../Utilities/WidgetUtils.h"

void UTrainingBuildingDetails::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
#pragma optimize("", off)

void UTrainingBuildingDetails::SetupForBuilding(AActor *buildingActor)
{
	BaseSetup(buildingActor);
	auto dataManager = UROVDataUtils::GetGameManager();

	TrainingItems.Empty();
	TrainingList->ClearChildren();

	auto detailsComponent = BuildingActor->GetComponentByClass<UBuildingDetailsComponent>();
	if (!detailsComponent)
		UDebugMessages::LogError(this, "failed to get details component");

	TrainingList->SetVisibility(ESlateVisibility::Hidden);
	ProgressItem->SetVisibility(ESlateVisibility::Hidden);

	GatewayClient->GetBuildingTrainableUnits(
		detailsComponent->GetBuildingType(),
		detailsComponent->GetBuildingId(),
		[this](FString content)
		{
			FBuildingTrainingDetailsResponseApiDto trainableUnitsListResponseDto;
			FTrainingGetQueueReseponseApiDto queueResponseDto;
			if (UFileManagementUtilities::JsonToStruct(content, &trainableUnitsListResponseDto))
			{

				auto payload = trainableUnitsListResponseDto.GetPayload();

				if (payload.GetTrainableUnits().IsEmpty())
				{
					UDebugMessages::LogDisplay(this, "failed to get training list, testing if response was a queue");
					if (UFileManagementUtilities::JsonToStruct(content, &queueResponseDto))
					{
						ProgressItem->SetVisibility(ESlateVisibility::Visible);
						auto queue = queueResponseDto.GetPayload();

						if (queueResponseDto.GetPayload().GetAmount() > 0)
							UDebugMessages::LogDisplay(this, "queue exists with greater than 0 amount");

						ProgressItem->SetProgressValues(queue.GetStartTime(), queue.GetFinishTime(), queue.GetUnitType(), queue.GetBuildingId(), queue.GetAmount());
						UpdateProgressWidgetsCallback();
					}
					return;
				}

				auto detailsComponent = BuildingActor->GetComponentByClass<UBuildingDetailsComponent>();
				if (!detailsComponent)
					UDebugMessages::LogError(this, "failed to get details component");

				TrainingList->SetVisibility(ESlateVisibility::Visible);
				for (int i = 0; i < payload.GetTrainableUnits().Num(); i++)
				{
					auto newWidget = CreateTrainingItemWidget();
					TrainingList->AddChild(newWidget);

					for (int x = 0; x < payload.GetTrainableUnits()[i].GetUnitCosts().Num(); x++)
					{
						newWidget->AddResourceCost(
							payload.GetTrainableUnits()[i].GetUnitCosts()[x].GetAmount(),
							payload.GetTrainableUnits()[i].GetUnitCosts()[x].GetResourceType());
					}
					newWidget->SetupMaxAmounts();
					newWidget->SetUnitType(payload.GetTrainableUnits()[i].GetUnitType());
					newWidget->SetUnitName(UWidgetUtils::GetUnitNameFromEnum(payload.GetTrainableUnits()[i].GetUnitType()));
					newWidget->SetBuildingId(detailsComponent->GetBuildingId());
				}
			}
		});
}

UTrainingItemWidget *UTrainingBuildingDetails::CreateTrainingItemWidget()
{
	FSoftClassPath hudUIRef(*TrainingItemWidgetRef);
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UTrainingItemWidget>())
		return CreateWidget<UTrainingItemWidget>(this, hudUIWidgetClass);

	return nullptr;
}

void UTrainingBuildingDetails::HideWidget()
{
	Super::HideWidget();
	GetWorld()->GetTimerManager().ClearTimer(UpdateProgressWidgetsHandle);
	UDebugMessages::LogDisplay(this, "Cleared Training Queue Timer");
}

#pragma optimize("", on)