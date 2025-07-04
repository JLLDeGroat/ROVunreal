// Fill out your copyright notice in the Description page of Project Settings.


#include "CityGameMode.h"
#include "../Controller/ROVController.h"
#include "../Pawns/ROVPawn.h"
#include "../ROVCharacter.h"
#include "../ROVPlayerController.h"
#include "../HUD/RovHud.h"

ACityGameMode::ACityGameMode() {
	PlayerControllerClass = AROVController::StaticClass();
	DefaultPawnClass = AROVPawn::StaticClass();
	HUDClass = ARovHud::StaticClass();
}

void ACityGameMode::StartPlay() {
	Super::StartPlay();

}
