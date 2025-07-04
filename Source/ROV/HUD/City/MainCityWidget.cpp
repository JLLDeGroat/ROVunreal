// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCityWidget.h"
#include "Building/ResourceBuildingDetails.h"
#include "Building/TrainingBuildingDetails.h"
#include "Building/CityBuildingDetailsWidget.h"

UMainCityWidget::UMainCityWidget(const FObjectInitializer &ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

UResourceBuildingDetails *UMainCityWidget::GetResourceBuildingDetailsWidget()
{
	return ResourceBuildingDetails;
}
UTrainingBuildingDetails *UMainCityWidget::GetTraningBuildingDetails()
{
	return TrainingBuildingDetails;
}
UCityProgressWidget *UMainCityWidget::GetCityProgressWidget()
{
	return CityProgressWidget;
}
UCityBuildingDetailsWidget *UMainCityWidget::GetCityBuildinigDetailsWidget()
{
	return CityBuildinigDetailsWidget;
}