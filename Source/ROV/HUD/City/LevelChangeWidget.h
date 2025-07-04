// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelChangeWidget.generated.h"

class UTextBlock;
class UButton;
/**
 *
 */
UCLASS()
class ROV_API ULevelChangeWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeOnInitialized() override;

public:
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *LevelText;
	UPROPERTY(meta = (BindWidget))
	UButton *LevelBtn;

	UFUNCTION()
	void OnLevelBtnClicked();
};
