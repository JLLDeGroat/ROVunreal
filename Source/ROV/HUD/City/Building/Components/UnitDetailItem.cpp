// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitDetailItem.h"
#include "Vgcore/Domain/Debug/DebugMessages.h"
void UUnitDetailItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUnitDetailItem::SetUnitAmount(int amount)
{
	Amount = amount;
}
void UUnitDetailItem::SetUnitType(EROVUnitType unitType)
{
	UnitType = unitType;
}

void UUnitDetailItem::SetupItem(int amount, EROVUnitType unitType)
{
	UnitType = unitType;
	Amount = amount;

	UDebugMessages::LogError(this, "TODO should set the unit type image too here");
}