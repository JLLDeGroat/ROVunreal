// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuBaseWidget.h"
#include "../../Domain/Client/ROVClient.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "VgFlMngmnt/Domain/SaveGameManager.h"
#include "ROVData/Models/FROVModels.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "ROVData/Dtos/FCityOverviewDtos.h"
#include "ROVData/Manager/GameDataManager.h"
#include "ROVData/Models/FROVGameConfig.h"
#include "ROVData/Public/ROVDataUtils.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../../Delegates/UIDelegates.h"
#include "../../Delegates/CityDelegates.h"
#include "../../Utilities/WidgetUtils.h"
#include "../City/MainCityWidget.h"
#include "../City/CityProgressWidget.h"

UMainMenuBaseWidget::UMainMenuBaseWidget(const FObjectInitializer &ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UMainMenuBaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GatewayClient = NewObject<UROVClient>();

	if (!InitMessage || !InitProgress)
		return UDebugMessages::LogError(this, "main menu base could not use either init message or init progress");

	bool clearGameData = false;
	if (clearGameData)
	{
		ClearGameData();
		UDebugMessages::LogWarning(this, "clearing game data");
	}

	InitializeMainMenu();
}
void UMainMenuBaseWidget::ClearGameData()
{
	auto saveGameManager = UFileManagementUtilities::GetSaveManager();
	saveGameManager->SaveGameData("");
}
void UMainMenuBaseWidget::InitializeMainMenu()
{
	auto saveGameManager = UFileManagementUtilities::GetSaveManager();
	auto gameDataJson = saveGameManager->LoadGameData();

	auto initialGuidIfFirstLoad = FGuid::NewGuid();
	auto gameManager = UROVDataUtils::GetGameManager();

	InitMessage->SetText(FText::FromString("Initializing."));
	InitProgress->SetPercent(InitProgress->GetPercent() + .25f);

	if (gameDataJson.IsEmpty())
	{
		auto gameData = gameManager->GetGameData();
		gameData->SetDevice(initialGuidIfFirstLoad.ToString());
		gameManager->SetGameData(gameData);
		saveGameManager->SaveGameData(UFileManagementUtilities::StructToJson(*gameData));

		auto newGameConfig = FROVGameConfig();
		gameManager->SetGameConfig(&newGameConfig);

		UpdateInitMessage("Initializing new account.");
		GatewayClient->Initialise(initialGuidIfFirstLoad.ToString(), [this](FString content)
								  { return OnInitialiseResponse(content); });
	}
	else
	{
		FGameDataModel gameDataModel;
		UFileManagementUtilities::JsonToStruct(gameDataJson, &gameDataModel);
		gameManager->SetGameData(&gameDataModel);

		UpdateInitMessage("Authorising device.");

		auto gameData = gameManager->GetGameData();
		GatewayClient->SetToken(gameData->GetToken());
		GatewayClient->SetApiKey(gameData->GetApiKey());
		GatewayClient->Authorise([this](FString content)
								 { return OnAuthoriseResponse(content); });
	}
}

void UMainMenuBaseWidget::OnInitialiseResponse(FString content)
{
	if (content.IsEmpty())
	{
		UpdateInitMessage("Failed to login.");
		return;
	}

	UpdateInitPercent();

	FApiDto apiDto;
	GatewayClient->GetResultAsApiDto(content, &apiDto);

	if (!apiDto.GetSuccess())
	{
		UpdateInitMessage("Failed to get good login response.");
		return;
	}

	FAccountCreateResponseDto response;
	if (UFileManagementUtilities::JsonToStruct(apiDto.GetPayload(), &response))
	{
		auto gameManager = UROVDataUtils::GetGameManager();
		auto gameData = gameManager->GetGameData();

		gameData->SetApiKey(response.GetApiKey());
		gameData->SetAccountId(response.GetUid());

		auto saveManager = UFileManagementUtilities::GetSaveManager();
		saveManager->SaveGameData(UFileManagementUtilities::StructToJson(*gameData));

		GatewayClient->SetApiKey(response.GetApiKey());
		GatewayClient->Authorise([this](FString content)
								 { return OnAuthoriseResponse(content); });
	}
	else
	{
		UpdateInitMessage("Failed to read login response.");
	}
}

void UMainMenuBaseWidget::OnAuthoriseResponse(FString content)
{
	UDebugMessages::LogDisplay(this, "OnAuthoriseResponse " + content);
	auto gameManager = UROVDataUtils::GetGameManager();
	auto gameData = gameManager->GetGameData();

	FApiDto apiDto;
	GatewayClient->GetResultAsApiDtoWithStringResult(content, &apiDto);

	if (apiDto.GetSuccess())
	{
		UpdateInitPercent();
		UpdateInitMessage("Authorized");
		gameData->SetToken(apiDto.GetPayload());
		gameManager->SetGameData(gameData);
		UFileManagementUtilities::GetSaveManager()->SaveGameData(UFileManagementUtilities::StructToJson(*gameData));

		GatewayClient->SetToken(apiDto.GetPayload());
		GatewayClient->Login(gameData->GetDevice(), [this](FString content)
							 { return OnLoginResponse(content); });
	}
	else
	{
		UpdateInitMessage("Failed To Authorize");
	}
}
void UMainMenuBaseWidget::OnLoginResponse(FString content)
{
	UDebugMessages::LogDisplay(this, "OnLoginResponse " + content);
	auto gameManager = UROVDataUtils::GetGameManager();
	auto gameData = gameManager->GetGameData();

	FOverviewCityRequestDto getOverviewRequest = FOverviewCityRequestDto();
	getOverviewRequest.SetAccountId(gameData->GetAccountId());

	UpdateInitPercent();

	GatewayClient->CityOverview(&getOverviewRequest, [this](FString content)
								{ return OnOverviewResponse(content); });
}
#pragma optimize("", off)
void UMainMenuBaseWidget::OnOverviewResponse(FString content)
{
	UDebugMessages::LogDisplay(this, "OnLoginResponse " + content);

	FOverViewCityApiDto cityApi;
	if (UFileManagementUtilities::JsonToStruct(content, &cityApi))
	{
		UpdateInitPercent();
		UpdateInitMessage("Acquiring overview.");

		auto cityApiPayload = cityApi.GetPayload();
		auto gameManager = UROVDataUtils::GetGameManager();
		gameManager->SetCityOverviewData(&cityApiPayload);

		auto cityDelegates = UCityDelegates::GetInstance();
		if (!cityDelegates)
			return UDebugMessages::LogError(this, "failed to get debug messages");

		GatewayClient->GetCityBonuses(
			gameManager->GetCityOverviewData()->GetCityId(),
			[this](FString content)
			{
				auto gameManager = UROVDataUtils::GetGameManager();
				FCityBonusGetListResponseApiDto bonusApiDto;
				if (UFileManagementUtilities::JsonToStruct(content, &bonusApiDto))
				{
					gameManager->AddCityBonuses(gameManager->GetCityOverviewData()->GetCityIdAsGuid(), bonusApiDto.GetPayload());
				}
			});

		GatewayClient->GetResourceRates(
			[this](FString content)
			{
				auto gameManager = UROVDataUtils::GetGameManager();

				FResourceRateResponseApiDto resRates;
				if (UFileManagementUtilities::JsonToStruct(content, &resRates))
				{
					auto payload = resRates.GetPayload();
					gameManager->SetResourceRatesDto(&payload);
				}
			});

		GatewayClient->GetResourceTypes(
			[this](FString content)
			{
				auto gameManager = UROVDataUtils::GetGameManager();

				FResourceTypesResponseApiDto resTypes;
				if (UFileManagementUtilities::JsonToStruct(content, &resTypes))
				{
					auto payload = resTypes.GetPayload();
					gameManager->SetResourceTypes(&payload);
				}
			});

		GatewayClient->GetBuildingTypes(
			[this](FString content)
			{
				auto gameManager = UROVDataUtils::GetGameManager();

				FBuildingTypesResponseApiDto buildingTypes;
				if (UFileManagementUtilities::JsonToStruct(content, &buildingTypes))
				{
					auto payload = buildingTypes.GetPayload();
					gameManager->SetBuildingTypes(&payload);
				}
			});

		auto slots = gameManager->GetCityOverviewData()->GetBuildingSlots();

		for (auto slot : slots)
			if (slot.GetBuilding() && slot.GetBuilding()->GetBuildingType() != EBuildingType::INVALID)
				cityDelegates->_OnSuccessulBuildingUpgrade.Broadcast(slot.GetSlot());

		auto cityWidget = UWidgetUtils::GetMainCityWidget(this);
		auto progressWidget = cityWidget->GetCityProgressWidget();
		for (int i = 0; i < slots.Num(); i++)
		{
			auto building = slots[i].GetBuilding();
			if (building)
			{
				auto uiDelegates = UUIDelegates::GetInstance();
				if (uiDelegates)
				{
					if (building->GetTrainingQueue()->GetAmount() > 0)
					{
						uiDelegates->_OnTraininBeginProgress.Broadcast(building->GetTrainingQueue()->GetStartTime(),
																	   building->GetTrainingQueue()->GetFinishTime(),
																	   FBase::ToGuid(building->GetBuildingId()),
																	   building->GetTrainingQueue()->GetUnitType(),
																	   building->GetTrainingQueue()->GetAmount());
					}

					if (building->GetIsUpgrading())
					{
						uiDelegates->_OnBuildingBeginConstruction.Broadcast(building->GetStartTime(), building->GetFinishTime(),
																  building->GetBuildingType(), FBase::ToGuid(building->GetBuildingId()));
					}
				}
				else
					UDebugMessages::LogError(this, "failed to get delegate instance");
			}
		}

		auto useTimeDelay = false;
		if (useTimeDelay)
			GetWorld()->GetTimerManager().SetTimer(DelayLoginHandle, this, &UMainMenuBaseWidget::OnDelayLoginCallback, 2.0f, false);
		else
		{
			UDebugMessages::LogDisplay(this, "Broadcasting delegate _OnLoginJourneyComplete");
			auto uiDelegates = UUIDelegates::GetInstance();
			uiDelegates->_OnLoginJourneyComplete.Broadcast();
			RemoveFromParent();
		}
	}
	else
	{
		UpdateInitMessage("Failed to acquire overview.");
	}
}
#pragma optimize("", on)
void UMainMenuBaseWidget::OnDelayLoginCallback()
{
	UDebugMessages::LogDisplay(this, "Broadcasting delegate _OnLoginJourneyComplete");
	auto uiDelegates = UUIDelegates::GetInstance();
	uiDelegates->_OnLoginJourneyComplete.Broadcast();
	RemoveFromParent();
}

void UMainMenuBaseWidget::UpdateInitMessage(FString msg)
{
	InitMessage->SetText(FText::FromString("Initializing new account."));
}
void UMainMenuBaseWidget::UpdateInitPercent(float amount)
{
	auto current = InitProgress->GetPercent();
	auto newCurrent = current + amount;
	InitProgress->SetPercent(newCurrent);
}