// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSlotDetailsWidget.h"
#include "../../../../Delegates/MapUIDelegates.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../../../Entities/MapSlot.h"
#include "../../../../Domain/Client/ROVMapClient.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "../../../../Utilities/RovUtils.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"

void UBaseSlotDetailsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    CloseButton->OnClicked.AddDynamic(this, &UBaseSlotDetailsWidget::HideWidget);
}

void UBaseSlotDetailsWidget::HideWidget()
{
    SetVisibility(ESlateVisibility::Hidden);

    auto mapDelegates = UMapUIDelegates::GetInstance();
    if (mapDelegates)
        mapDelegates->_OnAllowMapUiReactions.Broadcast();
}
#pragma optimize("", off)
void UBaseSlotDetailsWidget::SetupForSlot(AMapSlot *slot)
{
    CurrentSlot = slot;

    auto rovClient = URovUtils::CreateGateWayClient(this);
    auto gameManager = UROVDataUtils::GetGameManager();
    auto city = gameManager->GetCityOverviewData()->GetCityId();

    rovClient->GetLocationDetails(
        slot->GetX(),
        slot->GetY(),
        city,
        slot->GetOccupationType(),
        [this](FGenericApiResponse apiResponse)
        {
            if (UFileManagementUtilities::JsonToStruct(apiResponse.GetPayload(), &OccupationDetails))
            {
                if (CurrentSlot->GetUid() == OccupationDetails.GetLocationUid())
                {
                    SlotDetailsRecieved();
                }
                else
                    UDebugMessages::LogError(this, "the location we just received");
            }
        });
}
#pragma optimize("", on)
void UBaseSlotDetailsWidget::SlotDetailsRecieved()
{
    UDebugMessages::UDebugMessages::LogError(this, "shouldnt run");
}
