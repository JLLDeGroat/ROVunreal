// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataManager.h"


UGameDataManager::UGameDataManager(const FObjectInitializer& ObjectInitializer)
	: UObject(ObjectInitializer) {
	GameData = FGameDataModel();
	CityOverview = FOverViewCityDto();
}

FOverViewBuildingSlotDto* UGameDataManager::GetSlotOverviewByBuildingId(FGuid buildingId) {
	auto guidAsString = buildingId.ToString(EGuidFormats::DigitsWithHyphens);
	auto allSlots = GetCityOverviewData()->GetBuildingSlots();

	auto city = GetCityOverviewData();
	for (int i = 0; i < GetCityOverviewData()->GetBuildingSlots().Num(); i++) {
		if (GetCityOverviewData()->GetBuildingSlots()[i].GetBuilding()->GetBuildingId() == buildingId.ToString(EGuidFormats::DigitsWithHyphens)) {
			return &GetCityOverviewData()->GetBuildingSlots()[i];
		}
	}

	return nullptr;
}

FOverViewBuildingSlotDto* UGameDataManager::GetSlotOverviewBySlotId(int slotId) {
	auto allSlots = GetCityOverviewData()->GetBuildingSlots();
	for (int i = 0; i < GetCityOverviewData()->GetBuildingSlots().Num(); i++)
		if (GetCityOverviewData()->GetBuildingSlots()[i].GetSlot() == slotId)
			return &GetCityOverviewData()->GetBuildingSlots()[i];

	return CityOverview.CreateSlot(slotId);
}

FOverViewBuildingDto* UGameDataManager::AddBuildingToSlot(int slotId, EBuildingType buildingType, FString id, int level) {
	auto slots = GetCityOverviewData()->GetBuildingSlots();

	for (int i = 0; i < slots.Num(); i++)
		if (slots[i].GetSlot() == slotId) {
			return slots[i].AddBuilding(buildingType, id, level);
		}

	return nullptr;
}

void UGameDataManager::UpdateResourceItem(EResourceType resourceType, int amount) {
	GetCityOverviewData()->GetResource(resourceType)->Update(amount);
}

FCityBonusGetListResponseDto* UGameDataManager::GetCityBonuses(FGuid cityId) {
	if (CityBonuses.Find(cityId))
		return &CityBonuses[cityId];

	return nullptr;
}
void UGameDataManager::AddCityBonuses(FGuid cityId, FCityBonusGetListResponseDto cityBonusDtos) {
	if (CityBonuses.Find(cityId))
		CityBonuses[cityId] = cityBonusDtos;
	else
		CityBonuses.Add(cityId, cityBonusDtos);
}

void UGameDataManager::SetResourceRatesDto(FResourceRateResponseDto* resourceRates) {
	ResourceRates = *resourceRates;
}
FResourceRateResponseDto* UGameDataManager::GetResourceRates() {
	return &ResourceRates;
}
int UGameDataManager::GetHourlyAmount(int level, int tier) {
	for (int i = 0; i < ResourceRates.GetResourceRates().Num(); i++) {
		if (ResourceRates.GetResourceRates()[i].GetLevel() == level &&
			ResourceRates.GetResourceRates()[i].GetTier() == tier)
			return ResourceRates.GetResourceRates()[i].GetAmount();
	}

	return 0;
}

void UGameDataManager::SetResourceTypes(FResourceTypesResponseDto* resourceType) {
	ResourceTypes = *resourceType;
}
int UGameDataManager::GetResourceTier(EResourceType rType) {
	for (int i = 0; i < ResourceTypes.GetResourceTypes().Num(); i++)
		if (ResourceTypes.GetResourceTypes()[i].GetResourceType() == rType)
			return ResourceTypes.GetResourceTypes()[i].GetTier();

	return 1;
}

void UGameDataManager::SetBuildingTypes(FBuildingTypesResponseDto* buildingTypes) {
	BuildingTypes = *buildingTypes;
}
FBuildingTypeDto* UGameDataManager::GetBuildingType(EBuildingType buildingType) {
	for (int i = 0; i < BuildingTypes.GetBuildingTypes().Num(); i++) {
		if (BuildingTypes.GetBuildingTypes()[i].GetBuildingType() == buildingType)
			return &BuildingTypes.GetBuildingTypes()[i];
	}

	return nullptr;
}

FString UGameDataManager::GetBuildingDescription(EBuildingType buildingType) {
	for (int i = 0; i < BuildingTypes.GetBuildingTypes().Num(); i++) {
		if (BuildingTypes.GetBuildingTypes()[i].GetBuildingType() == buildingType)
			return BuildingTypes.GetBuildingTypes()[i].GetDescription();
	}
	return "";
}