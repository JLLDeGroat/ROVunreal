// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ArmyPresenceDetailItemWidget.generated.h"

class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class ROV_API UArmyPresenceDetailItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void SetPresenceAmount(FString value);
	void SetPresenceAmount(int amount);

	void SetImage(EROVUnitType unitType);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *PresenceAmount;

	UPROPERTY(meta = (BindWidget))
	UImage *PresenceImage;
};
