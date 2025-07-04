// Fill out your copyright notice in the Description page of Project Settings.


#include "City.h"

ACity::ACity(const FObjectInitializer& ObjectInitializer)
	: ABaseCityStructure(ObjectInitializer) {

}

void ACity::PrepareLevelOne() {
	LoadAndSetBuildingMesh("city1_1", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/City/Mesh/Lvl1_FullChain.Lvl1_FullChain'");
	LoadAndSetBuildingMesh("city1_2", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/City/Mesh/Lvl1_FullChain.Lvl1_FullChain'", FVector(1), FVector(0, 145, 0));
	LoadAndSetBuildingMesh("city1_3", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/City/Mesh/Lvl1_Main_KeepLvl1_Main_Keep.Lvl1_Main_KeepLvl1_Main_Keep'");
	LoadAndSetBuildingMesh("city1_4", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/City/Mesh/Lvl1_PortCullis.Lvl1_PortCullis'");
	LoadAndSetBuildingMesh("city1_5", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/City/Mesh/Lvl1_stairs.Lvl1_stairs'");
	LoadAndSetBuildingMesh("city1_6", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/City/Mesh/Lvl1_Walls.Lvl1_Walls'");
}

void ACity::PrepareLevelTen() {

}
void ACity::PrepareLevelTwenty() {

}
void ACity::PrepareLevelThirty() {

}
void ACity::PrepareLevelFourty() {

}
void ACity::PrepareLevelFifty() {

}