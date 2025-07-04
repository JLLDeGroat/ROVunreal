// Fill out your copyright notice in the Description page of Project Settings.

#include "CityManagerActor.h"
#include "../../Delegates/UIDelegates.h"
#include "../../Delegates/CityDelegates.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "ROVData/Dtos/FResourceDtos.h"
#include "../../Domain/Client/ROVClient.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
// Sets default values
ACityManagerActor::ACityManagerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACityManagerActor::BeginPlay()
{
	Super::BeginPlay();

	auto newGateWayClient = NewObject<UROVClient>();
	GatewayClient = newGateWayClient;

	auto uiDelegates = UUIDelegates::GetInstance();
	uiDelegates->_OnLoginJourneyComplete.AddDynamic(this, &ACityManagerActor::InitializeCity);
	uiDelegates->_OnRequestUpdatedResourceCount.AddDynamic(this, &ACityManagerActor::RequestUpdatedResourceCount);
}

void ACityManagerActor::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);
}

void ACityManagerActor::InitializeCity()
{
	UDebugMessages::LogDisplay(this, "InitializeCity");
	auto cityManager = UROVDataUtils::GetGameManager();
	auto cityOverview = cityManager->GetCityOverviewData();

	auto cityDelegates = UCityDelegates::GetInstance();
	cityDelegates->_OnInitializeBuildingSlot.Broadcast(99, GetCategoryOnLevel(cityOverview->GetCityLevel()), EBuildingType::City);

	GetWorld()->GetTimerManager().SetTimer(ResourceUpdateHandle, this, &ACityManagerActor::RequestUpdatedResourceCount, 60.0f, true);
}

EBuildingLevelMeshes ACityManagerActor::GetCategoryOnLevel(int level)
{
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

void ACityManagerActor::RequestUpdatedResourceCount()
{
	if (bIsCallingForResources)
	{
		UDebugMessages::LogDisplay(this, "already calling for res, skipping this run");
		return;
	}
	auto cityManager = UROVDataUtils::GetGameManager();
	auto cityOverview = cityManager->GetCityOverviewData();

	UDebugMessages::LogDisplay(this, "request updated resource count");

	if (cityOverview)
	{
		bIsCallingForResources = true;
		GatewayClient->GetCityResources(
			cityOverview->GetCityId(), [this](FString content)
			{
				UDebugMessages::LogDisplay(this, content);
				FResourceGetCityAmountResponseApiDto responseDto;
				if (UFileManagementUtilities::JsonToStruct(content, &responseDto)) {

					auto cityManager = UROVDataUtils::GetGameManager();
					auto gottenResources = responseDto.GetPayload().GetResources();
					for (int i = 0; i < gottenResources.Num(); i++) {
						auto thisResource = gottenResources[i];
						cityManager->UpdateResourceItem(thisResource.GetResourceType(), thisResource.GetAmount());
					}

					auto uiDelegates = UUIDelegates::GetInstance();
					uiDelegates->_OnUpdateResources.Broadcast(responseDto.GetPayload());
					bIsCallingForResources = false;
			} });
	}
	else
		UDebugMessages::LogError(this, "RequestUpdatedResourceCount no city overview, cannot request resource count");
}