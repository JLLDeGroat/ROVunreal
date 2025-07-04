// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGenericApiResponse.generated.h"


USTRUCT(BlueprintType)
struct FGenericApiResponse
{
	GENERATED_BODY()
public:
	FGenericApiResponse()
	{
		Error = "";
		Success = false;
	}

	FString GetError() { return Error; }
	bool GetSuccess() { return Success; }
	FString GetPayload() { return Payload; }

	void SetError(FString error) { Error = error; }
	void SetSuccess(bool success) { Success = success; }
	void SetPayload(FString str) { Payload = str; }

protected:
	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString Error;
	UPROPERTY()
	FString Payload;
};