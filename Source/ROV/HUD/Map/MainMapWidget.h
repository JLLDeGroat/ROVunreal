// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMapWidget.generated.h"

class UMapDetailsWidget;
class UPlayerCityWidget;
class UEmptySlotWidget;
class UAiCitySlotWidget;
class UStartAttackWidget;
/**
 *
 */
UCLASS()
class ROV_API UMainMapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMapWidget(const FObjectInitializer &ObjectInitializer);

	UPlayerCityWidget *GetPlayerCityWidget() { return PlayerCityWidget; }
	UEmptySlotWidget *GetEmptySlotWidget() { return EmptySlotWidget; }
	UAiCitySlotWidget *GetAiSlotWidget() { return AiSlotWidget; }
	UStartAttackWidget *GetStartAttackWidget() { return StartAttackWidget; }

protected:
	UPROPERTY(meta = (BindWidget))
	UMapDetailsWidget *MapDetailsWidget;

	UPROPERTY(meta = (BindWidget))
	UPlayerCityWidget *PlayerCityWidget;
	UPROPERTY(meta = (BindWidget))
	UEmptySlotWidget *EmptySlotWidget;
	UPROPERTY(meta = (BindWidget))
	UAiCitySlotWidget *AiSlotWidget;
	UPROPERTY(meta = (BindWidget))
	UStartAttackWidget *StartAttackWidget;
};
