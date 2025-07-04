// Fill out your copyright notice in the Description page of Project Settings.


#include "CityResourceWidget.h"
#include "../../Delegates/UIDelegates.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Models/FROVGameConfig.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

UCityResourceWidget::UCityResourceWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer) {

}

void UCityResourceWidget::NativeOnInitialized() {
	auto uiDelegate = UUIDelegates::GetInstance();
	uiDelegate->_OnLoginJourneyComplete.AddDynamic(this, &UCityResourceWidget::OnLoginJourneyComplete);
	uiDelegate->_OnUpdateResources.AddDynamic(this, &UCityResourceWidget::UpdateUIResources);
}

void UCityResourceWidget::OnLoginJourneyComplete() {
	FillOutResourceData(ResAmount1, ResIcon1, EResourceType::OrganicMaterial);
	FillOutResourceData(ResAmount2, ResIcon2, EResourceType::ConstructionSoil);
	FillOutResourceData(ResAmount3, ResIcon3, EResourceType::Adhesive);
	FillOutResourceData(ResAmount4, ResIcon4, EResourceType::StoneFragment);
	FillOutResourceData(ResAmount5, ResIcon5, EResourceType::OrganicMatter);
	FillOutResourceData(ResAmount6, ResIcon6, EResourceType::Clay);
	FillOutResourceData(ResAmount7, ResIcon7, EResourceType::IronFragment);
	FillOutResourceData(ResAmount8, ResIcon8, EResourceType::CopperFragment);
}

void UCityResourceWidget::FillOutResourceData(UTextBlock* block, UImage* img, EResourceType resourceType) {
	auto manager = UROVDataUtils::GetGameManager();
	auto overview = manager->GetCityOverviewData();
	auto amount = overview->GetResourceAmount(resourceType);
	auto maxAmount = overview->GetResourceMaxAmount(resourceType);

	block->SetText(FText::FromString(FString::SanitizeFloat(amount, 0) + "/" + FString::SanitizeFloat(maxAmount, 0)));
}


void UCityResourceWidget::UpdateUIResources(FResourceGetCityAmountResponseDto resourceDto) {
	FillOutResourceData(ResAmount1, ResIcon1, EResourceType::OrganicMaterial);
	FillOutResourceData(ResAmount2, ResIcon2, EResourceType::ConstructionSoil);
	FillOutResourceData(ResAmount3, ResIcon3, EResourceType::Adhesive);
	FillOutResourceData(ResAmount4, ResIcon4, EResourceType::StoneFragment);
	FillOutResourceData(ResAmount5, ResIcon5, EResourceType::OrganicMatter);
	FillOutResourceData(ResAmount6, ResIcon6, EResourceType::Clay);
	FillOutResourceData(ResAmount7, ResIcon7, EResourceType::IronFragment);
	FillOutResourceData(ResAmount8, ResIcon8, EResourceType::CopperFragment);

	//previous app

	auto resources = resourceDto.GetResources();
	auto gameData = UROVDataUtils::GetGameManager();
	auto gameConfig = gameData->GetGameConfig();

	for (int i = 0; i < resources.Num(); i++) {
		auto resourceType = resources[i].GetResourceType();
		auto resourceName = ROVEnums::ResourceAsString(resourceType);
		auto amount = resources[i].GetAmount();
		UDebugMessages::LogDisplay(this, resourceName + " : " + FString::SanitizeFloat(amount, 0));

		if ((EResourceType)gameConfig->Section1Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section1Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section2Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section3Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section4Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section5Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section6Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section7Resource == resourceType) {

		}
		else if ((EResourceType)gameConfig->Section8Resource == resourceType) {

		}

	}
}