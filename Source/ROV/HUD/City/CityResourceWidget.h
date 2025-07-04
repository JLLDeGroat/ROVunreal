// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ROVData/Enums/ROVEnums.h"
#include "CityResourceWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class ROV_API UCityResourceWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UCityResourceWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;

	UFUNCTION() void UpdateUIResources(FResourceGetCityAmountResponseDto resourceDto);

protected:

	UFUNCTION() void OnLoginJourneyComplete();

	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount1;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon1;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount2;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon2;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount3;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon3;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount4;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon4;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount5;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon5;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount6;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon6;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount7;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon7;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResAmount8;
	UPROPERTY(meta = (BindWidget)) UImage* ResIcon8;

private:

	void FillOutResourceData(UTextBlock* block, UImage* img, EResourceType resourceType);
};
