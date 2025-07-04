// Fill out your copyright notice in the Description page of Project Settings.


#include "Barracks.h"

ABarracks::ABarracks(const FObjectInitializer& ObjectInitializer)
	: ABaseCityStructure(ObjectInitializer) {

}

void ABarracks::PrepareLevelOne() {
	LoadAndSetBuildingMesh("bar1_1", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Barracks/lvl1_Cube.lvl1_Cube'");
	LoadAndSetBuildingMesh("bar1_2", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Barracks/lvl1_Cube_009.lvl1_Cube_009'");
	LoadAndSetBuildingMesh("bar1_3", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Barracks/lvl1_Cylinder_041.lvl1_Cylinder_041'");
	LoadAndSetBuildingMesh("bar1_4", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Barracks/lvl1_Cylinder_135.lvl1_Cylinder_135'");
	LoadAndSetBuildingMesh("bar1_5", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Barracks/lvl1_Cylinder_152.lvl1_Cylinder_152'");
	LoadAndSetBuildingMesh("bar1_6", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Barracks/lvl1_Cylinder_154.lvl1_Cylinder_154'");
}
void ABarracks::PrepareLevelTen() {

}
void ABarracks::PrepareLevelTwenty() {

}
void ABarracks::PrepareLevelThirty() {

}
void ABarracks::PrepareLevelFourty() {

}
void ABarracks::PrepareLevelFifty() {

}