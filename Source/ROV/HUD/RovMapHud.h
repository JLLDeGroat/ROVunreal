// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RovMapHud.generated.h"

class UMainMapWidget;
/**
 *
 */
UCLASS()
class ROV_API ARovMapHud : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UMainMapWidget *GetMainMapWidget();

protected:
	UPROPERTY()
	UMainMapWidget *MainMapWidget;
};