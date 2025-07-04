// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseBuildingDetailsWidget.h"
#include "ResourceBuildingDetails.generated.h"

class IGatewayClient;
class UTextBlock;
class UImage;
class UButton;

UCLASS()
class ROV_API UResourceBuildingDetails : public UBaseBuildingDetailsWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	virtual void SetupForBuilding(AActor* buildingActor) override;

protected:

	UPROPERTY(meta = (BindWidget)) UTextBlock* Description;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Rate;
	UPROPERTY(meta = (BindWidget)) UTextBlock* StorageBonus;

	UPROPERTY(meta = (BindWidget)) UImage* Image;

private:

void SetResourceSectionVisibility(ESlateVisibility visibility);
};
