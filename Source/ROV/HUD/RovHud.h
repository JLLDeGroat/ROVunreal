// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RovHud.generated.h"

class UMainMenuBaseWidget;
class UMainCityWidget;

/**
 * 
 */
UCLASS()
class ROV_API ARovHud : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UMainCityWidget* GetMainCityWidget();

protected:

	UPROPERTY() UMainMenuBaseWidget* MainMenuWidget;
	UPROPERTY() UMainCityWidget* MainCityWidget;


	UFUNCTION() void OnLoginJourneyComplete();
};
