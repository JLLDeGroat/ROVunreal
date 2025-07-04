// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBaseDtos.h"
#include "../Enums/ROVEnums.h"
#include "FResourceDtos.generated.h"

/**
 *
 */


USTRUCT()
struct FResourceGetCityAmountResponseDto {
	GENERATED_BODY()
public:
	FResourceGetCityAmountResponseDto() {

	}

	TArray<FResourceDto> GetResources() { return Resources; }
protected:
	UPROPERTY() TArray<FResourceDto> Resources;
};

USTRUCT()
struct FResourceGetCityAmountRequestDto {
	GENERATED_BODY()
public:
	FResourceGetCityAmountRequestDto() {

	}

	void SetCityId(FString cityId) { CityId = cityId; }
protected:
	UPROPERTY() FString CityId;
};

USTRUCT()
struct FResourceGetCityAmountResponseApiDto {
	GENERATED_BODY()
public:
	FResourceGetCityAmountResponseApiDto() {
		Success = false;
		Error = "";
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FResourceGetCityAmountResponseDto GetPayload() { return Payload; }

protected:
	UPROPERTY() bool Success;
	UPROPERTY() FString Error;
	UPROPERTY() FResourceGetCityAmountResponseDto Payload;
};