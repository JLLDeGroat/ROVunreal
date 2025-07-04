// Fill out your copyright notice in the Description page of Project Settings.

#include "RovMapHud.h"
#include "MainMenu/MainMenuBaseWidget.h"
#include "Map/MainMapWidget.h"
#include "City/MainCityWidget.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../Delegates/UIDelegates.h"

void ARovMapHud::BeginPlay()
{
	Super::BeginPlay();

	FSoftClassPath hudUIRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/Map/MainMapWidget_Bp.MainMapWidget_Bp_C'"));
	if (UClass *hudUIWidgetClass = hudUIRef.TryLoadClass<UMainMapWidget>())
	{
		auto hudWidget = CreateWidget<UMainMapWidget>(GetWorld(), hudUIWidgetClass);
		hudWidget->AddToViewport();
		MainMapWidget = hudWidget;
	}
}

UMainMapWidget *ARovMapHud::GetMainMapWidget()
{
	return MainMapWidget;
}