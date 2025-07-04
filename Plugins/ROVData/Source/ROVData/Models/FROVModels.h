#pragma once

#include "CoreMinimal.h"
#include "FROVModels.generated.h"

/**
 *
 */
USTRUCT()
struct FGameDataModel {
	GENERATED_BODY()
public:
	FGameDataModel() {
		Username = "";
		Email = "";
		ApiKey = "";
		Uid = "";
		Token = "";
		Device = "";
	}

	void SetToken(FString token) { Token = token; }
	FString GetToken() { return Token; }

	void SetUsername(FString username) { Username = username; }
	FString GetUsername() { return Username; }

	void SetApiKey(FString apiKey) { ApiKey = apiKey; }
	FString GetApiKey() { return ApiKey; }

	void SetAccountId(FString accountId) { Uid = accountId; }
	FString GetAccountId() { return Uid; }

	FString GetDevice() { return Device; }
	void SetDevice(FString dev) { Device = dev; }

protected:
	UPROPERTY() FString Username;
	UPROPERTY() FString Email;
	UPROPERTY() FString ApiKey;
	UPROPERTY() FString Uid;
	UPROPERTY() FString Token;
	UPROPERTY() FString Device;
};