// Fill out your copyright notice in the Description page of Project Settings.

#include "RovUtils.h"
#include "../HUD/City/MainCityWidget.h"
#include "../HUD/Map/MainMapWidget.h"
#include "../HUD/RovHud.h"
#include "../HUD/RovMapHud.h"
#include "../Controller/ROVController.h"
#include "../HUD/City/ComponentWidgets/ResourceCostItemWidget.h"
#include "../HUD/City/Building/Components/UnitDetailItem.h"
#include "../HUD/Map/Slots/Components/ArmyPresenceDetailItemWidget.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "../Interfaces/GatewayMapClient.h"
#include "../Domain/Client/ROVMapClient.h"

IGatewayMapClient *URovUtils::CreateGateWayClient(UObject *contextObj)
{
	auto obj = NewObject<UROVMapClient>(contextObj);
	return (IGatewayMapClient *)obj;
}

