// Fill out your copyright notice in the Description page of Project Settings.


#include "RovHud.h"
#include "MainMenu/MainMenuBaseWidget.h"
#include "City/MainCityWidget.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../Delegates/UIDelegates.h"

void ARovHud::BeginPlay() {
	Super::BeginPlay();

	FSoftClassPath hudUIRef(TEXT("WidgetBlueprint'/Game/Widgets/MainMenu/MainMenuBase_Bp.MainMenuBase_Bp_C'"));
	if (UClass* hudUIWidgetClass = hudUIRef.TryLoadClass<UMainMenuBaseWidget>())
	{
		auto hudWidget = CreateWidget<UMainMenuBaseWidget>(GetWorld(), hudUIWidgetClass);
		hudWidget->AddToViewport();
		MainMenuWidget = hudWidget;
	}

	FSoftClassPath hudCityUiRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/MainCityWidget_bp.MainCityWidget_bp_C'"));
	if (UClass* hudCityWidgetClass = hudCityUiRef.TryLoadClass<UMainCityWidget>())
	{
		auto hudCityWidget = CreateWidget<UMainCityWidget>(GetWorld(), hudCityWidgetClass);
		MainCityWidget = hudCityWidget;
		MainCityWidget->AddToViewport();
		MainCityWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	auto uiDelegates = UUIDelegates::GetInstance();
	uiDelegates->_OnLoginJourneyComplete.AddDynamic(this, &ARovHud::OnLoginJourneyComplete);
}

void ARovHud::OnLoginJourneyComplete() {
	if (!MainCityWidget) {
		UDebugMessages::LogError(this, "no city widget found in HUD");
		return;
	}

	MainCityWidget->SetVisibility(ESlateVisibility::Visible);
}

UMainCityWidget* ARovHud::GetMainCityWidget() {
	return MainCityWidget;
}