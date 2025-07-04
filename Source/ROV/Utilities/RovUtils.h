// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ROVData/Enums/ROVEnums.h"
#include "RovUtils.generated.h"

class IGatewayMapClient;

UCLASS()
class ROV_API URovUtils : public UObject
{
	GENERATED_BODY()

public:
	static IGatewayMapClient *CreateGateWayClient(UObject* contextObj);
};
