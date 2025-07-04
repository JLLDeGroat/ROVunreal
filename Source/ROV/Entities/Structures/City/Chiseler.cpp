// Fill out your copyright notice in the Description page of Project Settings.


#include "Chiseler.h"

AChiseler::AChiseler(const FObjectInitializer &ObjectInitializer)
	: ABaseCityStructure(ObjectInitializer)
{
}

void AChiseler::PrepareLevelOne()
{
	LoadAndSetBuildingMesh("bar1_1", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Chiseler/Lvl1Platform.Lvl1Platform'");
	LoadAndSetBuildingMesh("bar1_2", "/Script/Engine.StaticMesh'/Game/Entities/Structures/City/Chiseler/Lvl1Rock.Lvl1Rock'");
}
void AChiseler::PrepareLevelTen()
{
}
void AChiseler::PrepareLevelTwenty()
{
}
void AChiseler::PrepareLevelThirty()
{
}
void AChiseler::PrepareLevelFourty()
{
}
void AChiseler::PrepareLevelFifty()
{
}