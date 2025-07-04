// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ROVData/Dtos/FWorldDtos.h"
#include "BaseROVClient.generated.h"

/**
 *
 */
UCLASS()
class ROV_API UBaseROVClient : public UObject
{
	GENERATED_BODY()

protected:

	virtual void SetApiKey(FString key) { _apiKey = key; }
	virtual void SetToken(FString token) { _token = token; }

	FHttpRequestRef CreateRequest(FString url, FString method = "POST");
	FHttpRequestRef InsertROVHeaders(FHttpRequestRef request);
	void ProcessRequest(FHttpRequestRef request, TFunction<void(FString content)> callBack);
	void ProcessRequest(FHttpRequestRef request, TFunction<void(FGenericApiResponse responseDto)> callBack);
	// void ProcessGetRequest(FHttpRequestRef request, TFunction<void(FString content)> callBack);

	UPROPERTY()
	FString _baseUrl = "http://localhost:5223";
	UPROPERTY()
	FString _apiKeyHeaderName = "rov-apikey";
	UPROPERTY()
	FString _tokenHeaderName = "rov-token";

	UPROPERTY()
	FString _apiKey;
	UPROPERTY()
	FString _token;
};
