// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCityWidget.generated.h"

class UResourceBuildingDetails;
class UTrainingBuildingDetails;
class UCityProgressWidget;
class UCityBuildingDetailsWidget;
/**
 *
 */
UCLASS()
class ROV_API UMainCityWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainCityWidget(const FObjectInitializer &ObjectInitializer);

	UResourceBuildingDetails *GetResourceBuildingDetailsWidget();
	UTrainingBuildingDetails *GetTraningBuildingDetails();
	UCityProgressWidget *GetCityProgressWidget();
	UCityBuildingDetailsWidget *GetCityBuildinigDetailsWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UResourceBuildingDetails *ResourceBuildingDetails;
	UPROPERTY(meta = (BindWidget))
	UTrainingBuildingDetails *TrainingBuildingDetails;
	UPROPERTY(meta = (BindWidget))
	UCityProgressWidget *CityProgressWidget;
	UPROPERTY(meta = (BindWidget))
	UCityBuildingDetailsWidget *CityBuildinigDetailsWidget;
};
