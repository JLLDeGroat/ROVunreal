// Fill out your copyright notice in the Description page of Project Settings.

#include "TouchReactComponent.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../../Interfaces/Building.h"
#include "../../Interfaces/Slot.h"
#include "../../Delegates/UIDelegates.h"
#include "../../Utilities/WidgetUtils.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Manager/GameDataManager.h"
#include "../Components/BuildingDetailsComponent.h"
#include "../../HUD/City/MainCityWidget.h"
#include "../../HUD/City/Building/ResourceBuildingDetails.h"
#include "../../HUD/City/Building/TrainingBuildingDetails.h"
#include "../../HUD/City/Building/CityBuildingDetailsWidget.h"
#include "../../HUD/Map/MainMapWidget.h"
#include "../../HUD/Map/Slots/AiCitySlotWidget.h"
#include "../../HUD/Map/Slots/EmptySlotWidget.h"
#include "../../HUD/Map/Slots/PlayerCityWidget.h"
#include "../../Entities/MapSlot.h"
#include "ROVData/Enums/ROVEnums.h"

// Sets default values for this component's properties
UTouchReactComponent::UTouchReactComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTouchReactComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTouchReactComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTouchReactComponent::ReactToTouch()
{
	auto owner = GetOwner();
	UDebugMessages::LogDisplay(this, owner->GetName());

	bool reacted = false;

	TScriptInterface<ISlot> slot = owner;
	if (slot)
	{
		reacted = true;

		auto building = slot->GetBuilding();
		if (building)
			ReactToBuildingTouch(building);
		else
			ReactToSlotTouch(slot);
	}

	if (AMapSlot *mapSlot = Cast<AMapSlot>(owner))
		ReactToMapSlot(mapSlot);

	if (!reacted)
	{
		UDebugMessages::LogDisplay(this, "didnt react");
	}
}

void UTouchReactComponent::ReactToSlotTouch(TScriptInterface<ISlot> slot)
{
	auto slotId = slot->GetSlotNumber();

	auto uiInstance = UUIDelegates::GetInstance();
	uiInstance->_OnEmptySlotClicked.Broadcast(slotId);
}

void UTouchReactComponent::ReactToBuildingTouch(AActor *building)
{
	auto gameManager = UROVDataUtils::GetGameManager();
	auto cityWidget = UWidgetUtils::GetMainCityWidget(this);

	auto buildingDetails = building->GetComponentByClass<UBuildingDetailsComponent>();
	if (!buildingDetails)
		return UDebugMessages::LogError(this, "failed to get building details");

	if (buildingDetails->GetIsResourceBuilding())
	{
		auto resDetailsWidget = cityWidget->GetResourceBuildingDetailsWidget();
		resDetailsWidget->SetupForBuilding(building);
	}
	if (buildingDetails->GetIsTrainingBuilding())
	{
		auto trainingWidget = cityWidget->GetTraningBuildingDetails();
		trainingWidget->SetupForBuilding(building);
	}
	if (buildingDetails->GetIsCityBuilding())
	{
		auto cityBuildingWidget = cityWidget->GetCityBuildinigDetailsWidget();
		cityBuildingWidget->SetupForBuilding(building);
	}
}

void UTouchReactComponent::ReactToMapSlot(AMapSlot *mapSlot)
{
	auto occupationType = mapSlot->GetOccupationType();

	auto mapWidget = UWidgetUtils::GetMainMapWidget(this);

	if (occupationType == EOccupiedType::AICity)
	{
		mapWidget->GetAiSlotWidget()->SetupForSlot(mapSlot);
	}
	else if (occupationType == EOccupiedType::Environment ||
			 occupationType == EOccupiedType::INVALID)
	{
		mapWidget->GetEmptySlotWidget()->SetupForSlot(mapSlot);
	}
	else if (occupationType == EOccupiedType::PlayerCity)
	{
		mapWidget->GetPlayerCityWidget()->SetupForSlot(mapSlot);
	}
}