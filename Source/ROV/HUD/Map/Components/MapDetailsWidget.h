// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapDetailsWidget.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class ROV_API UMapDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:

	UFUNCTION() void OnLocationChanged(int x, int y);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LocationY;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *LocationX;
};
