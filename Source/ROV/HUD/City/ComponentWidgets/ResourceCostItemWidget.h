// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ResourceCostItemWidget.generated.h"

class UTextBlock;
class UImage;


UCLASS()
class ROV_API UResourceCostItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UResourceCostItemWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;

	void SetupResource(EResourceType rType, FString name, int amount);
	void SetMultiplier(int amount);

	EResourceType GetResourceType();
	int GetBaseAmount();

protected:

	UPROPERTY(meta = (BindWidget)) UTextBlock* Name;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Amount;
	UPROPERTY(meta = (BindWidget)) UImage* Image;

	UPROPERTY() EResourceType ResourceType;

private:

	UPROPERTY() int BaseAmount;
	UPROPERTY() int CurrentAmount;
	UPROPERTY() int Multiplier;

	UPROPERTY() bool bIsAffordable;

	void SetAmountValue();

};
