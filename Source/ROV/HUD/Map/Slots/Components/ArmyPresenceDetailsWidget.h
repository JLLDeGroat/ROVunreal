// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "ArmyPresenceDetailsWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UArmyPresenceDetailItemWidget;
/**
 *
 */
UCLASS()
class ROV_API UArmyPresenceDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void AddPresenceItem(EROVUnitType unitType, int amount);
	void AddPresenceItem(EROVUnitType unitType, FString description);

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox *LeftList;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox *RightList;

	UPROPERTY()
	TArray<UArmyPresenceDetailItemWidget *> Items;

private:
	UVerticalBox *GetNextInsertion();
};
