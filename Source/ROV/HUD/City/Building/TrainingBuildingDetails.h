// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseBuildingDetailsWidget.h"
#include "TrainingBuildingDetails.generated.h"

class UTrainingItemWidget;
class UScrollBox;
/**
 *
 */
UCLASS()
class ROV_API UTrainingBuildingDetails : public UBaseBuildingDetailsWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	virtual void SetupForBuilding(AActor *buildingActor) override;

	virtual void HideWidget() override;

protected:
	UPROPERTY()
	FString TrainingItemWidgetRef = "/Script/UMGEditor.WidgetBlueprint'/Game/Widgets/City/Buildings/Components/TrainingItemWidget_Bp.TrainingItemWidget_Bp_C'";

	UPROPERTY()
	TArray<UTrainingItemWidget *> TrainingItems;
	UPROPERTY(meta = (BindWidget))
	UScrollBox *TrainingList;

private:
	UTrainingItemWidget *CreateTrainingItemWidget();
};
