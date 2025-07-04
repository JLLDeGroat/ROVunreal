// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceCostItemWidget.h"
#include "Components/TextBlock.h"
#include "../../../Utilities/WidgetUtils.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"

UResourceCostItemWidget::UResourceCostItemWidget(const FObjectInitializer &ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UResourceCostItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	bIsAffordable = false;
}

void UResourceCostItemWidget::SetupResource(EResourceType rType, FString name, int amount)
{
	ResourceType = rType;
	Multiplier = 1;
	BaseAmount = amount;
	SetAmountValue();
	Name->SetText(FText::FromString(name));

	FString reference = "/Script/Engine.Font'/Game/Fonts/ImperiumSerif_Font.ImperiumSerif_Font'";
	auto fontObj = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, *reference, NULL, LOAD_None, NULL));
	
	FSlateFontInfo FontInfo;
	FontInfo.FontObject = fontObj;
	FontInfo.Size = 15;
	Name->SetFont(FontInfo);

	auto gameManager = UROVDataUtils::GetGameManager();
	auto resourceAmount = gameManager->GetCityOverviewData()->GetResource(rType);
	FSlateColor color = FSlateColor(FLinearColor(198, 0, 0, 1));
	if (resourceAmount->GetAmount() >= amount)
	{
		bIsAffordable = true;
		color = FSlateColor(FLinearColor(0, 198, 0, 1));
	}

	Amount->SetColorAndOpacity(color);
}

void UResourceCostItemWidget::SetMultiplier(int amount)
{
	Multiplier = amount;
	SetAmountValue();
}

void UResourceCostItemWidget::SetAmountValue()
{
	CurrentAmount = BaseAmount * Multiplier;
	Amount->SetText(FText::FromString(FString::SanitizeFloat(CurrentAmount, 0)));
}

EResourceType UResourceCostItemWidget::GetResourceType()
{
	return ResourceType;
}
int UResourceCostItemWidget::GetBaseAmount()
{
	return BaseAmount;
}