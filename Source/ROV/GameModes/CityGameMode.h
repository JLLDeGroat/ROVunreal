// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CityGameMode.generated.h"


/**
 * 
 */
UCLASS()
class ROV_API ACityGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACityGameMode();
	virtual void StartPlay() override;
protected:


private:
	
};
