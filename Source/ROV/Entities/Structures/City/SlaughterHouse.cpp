// Fill out your copyright notice in the Description page of Project Settings.


#include "SlaughterHouse.h"

ASlaughterHouse::ASlaughterHouse(const FObjectInitializer& ObjectInitializer)
	: ABaseCityStructure(ObjectInitializer) {

}

void ASlaughterHouse::PrepareLevelOne() {
	LoadAndSetBuildingMesh("sl1_1", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/SlaughterHouse/Mesh/lvl1_Cube.lvl1_Cube'");
	LoadAndSetBuildingMesh("sl1_2", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/SlaughterHouse/Mesh/lvl1_Cube_005.lvl1_Cube_005'");
	LoadAndSetBuildingMesh("sl1_3", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/SlaughterHouse/Mesh/lvl1_Cylinder_050.lvl1_Cylinder_050'");
	LoadAndSetBuildingMesh("sl1_4", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/SlaughterHouse/Mesh/lvl1_Cylinder_069.lvl1_Cylinder_069'");
}

void ASlaughterHouse::PrepareLevelTen() {

}
void ASlaughterHouse::PrepareLevelTwenty() {

}
void ASlaughterHouse::PrepareLevelThirty() {

}
void ASlaughterHouse::PrepareLevelFourty() {

}
void ASlaughterHouse::PrepareLevelFifty() {

}