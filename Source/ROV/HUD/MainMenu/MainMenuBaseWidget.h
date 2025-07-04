// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuBaseWidget.generated.h"

class UProgressBar;
class UTextBlock;
class IGatewayClient;
class UGameDataManager;

/**
 *
 */
UCLASS()
class ROV_API UMainMenuBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMainMenuBaseWidget(const FObjectInitializer& ObjecctInitializer);

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget)) UProgressBar* InitProgress;
	UPROPERTY(meta = (BindWidget)) UTextBlock* InitMessage;

	//Debug Method
	UFUNCTION(BlueprintCallable) void ClearGameData();

	UFUNCTION(BlueprintCallable) void InitializeMainMenu();

	UPROPERTY() TScriptInterface<IGatewayClient> GatewayClient;

	//UFUNCTION(BlueprintImplementableEvent) void UpdateInitializerTextBlock(const FString& text);
	//UFUNCTION(BlueprintImplementableEvent) void UpdateInitializerProgressBar();
	//UFUNCTION(BlueprintImplementableEvent) void CompleteInitializerProgressBar();

	UFUNCTION() void OnDelayLoginCallback();


private:

	void OnInitialiseResponse(FString content);
	void OnAuthoriseResponse(FString content);
	void OnLoginResponse(FString content);
	void OnOverviewResponse(FString content);

	FTimerHandle DelayLoginHandle;

	void UpdateInitMessage(FString msg);
	void UpdateInitPercent(float amount = .25f);

};
