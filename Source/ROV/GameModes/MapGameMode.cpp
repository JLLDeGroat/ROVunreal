// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGameMode.h"
#include "../Controller/ROVController.h"
#include "../Pawns/ROVPawn.h"
#include "../ROVCharacter.h"
#include "../ROVPlayerController.h"
#include "../HUD/RovMapHud.h"

AMapGameMode::AMapGameMode() {
	PlayerControllerClass = AROVController::StaticClass();
	DefaultPawnClass = AROVPawn::StaticClass();
	HUDClass = ARovMapHud::StaticClass();

}

void AMapGameMode::StartPlay() {
	Super::StartPlay();

}
