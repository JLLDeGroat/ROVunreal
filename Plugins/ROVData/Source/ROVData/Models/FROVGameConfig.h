// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FROVGameConfig.generated.h"

/**
 *
 */
USTRUCT()
struct FROVGameConfig {
	GENERATED_BODY()
public:
	FROVGameConfig() {
		Section1Resource = 1;
		Section2Resource = 2;
		Section3Resource = 3;
		Section4Resource = 4;
		Section5Resource = 5;
		Section6Resource = 6;
		Section7Resource = 7;
		Section8Resource = 8;
	}

	
	UPROPERTY() uint8 Section1Resource;
	UPROPERTY() uint8 Section2Resource;
	UPROPERTY() uint8 Section3Resource;
	UPROPERTY() uint8 Section4Resource;
	UPROPERTY() uint8 Section5Resource;
	UPROPERTY() uint8 Section6Resource;
	UPROPERTY() uint8 Section7Resource;
	UPROPERTY() uint8 Section8Resource;

protected:

};