// Fill out your copyright notice in the Description page of Project Settings.

#include "ROVClient.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "ROVData/Dtos/FBuildingDtos.h"
#include "ROVData/Dtos/FResourceDtos.h"
#include "ROVData/Dtos/FCityUpgradeDtos.h"

UROVClient::UROVClient()
{
}

void UROVClient::Initialise(FString deviceId, TFunction<void(FString content)> callBack)
{
	ProcessRequest(CreateRequest("/login/initialize/" + deviceId, "GET"), callBack);
}

void UROVClient::Login(FString deviceId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/login/device/" + deviceId, "GET");
	request = InsertROVHeaders(request);
	ProcessRequest(request, callBack);
}

void UROVClient::Authorise(TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/token/create", "GET");
	request = InsertROVHeaders(request);
	ProcessRequest(request, callBack);
}

void UROVClient::CityOverview(FOverviewCityRequestDto *requestDto, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/overview/default", "POST");
	request = InsertROVHeaders(request);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(*requestDto));
	ProcessRequest(request, callBack);
}

void UROVClient::AttemptToBuild(FBuildingBuildRequestDto *requestDto, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/build", "POST");
	request = InsertROVHeaders(request);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(*requestDto));
	ProcessRequest(request, callBack);
}

void UROVClient::GetSlotContents(FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/slot/contents", "POST");
	request = InsertROVHeaders(request);
	request->SetContentAsString("{}");
	ProcessRequest(request, callBack);
}

void UROVClient::GetCityResources(FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/get/resources", "POST");
	request = InsertROVHeaders(request);

	FResourceGetCityAmountRequestDto requestDto;
	requestDto.SetCityId(cityId);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
	ProcessRequest(request, callBack);
}
#pragma optimize("", off)
void UROVClient::GetBuildingDetails(FString cityId, FString buildingId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/general/details");
	request = InsertROVHeaders(request);

	FBuildingDetailsRequestDto requestDto = FBuildingDetailsRequestDto(cityId, buildingId);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
	ProcessRequest(request, callBack);
}
void UROVClient::GetCityBonuses(FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/bonuses");
	request = InsertROVHeaders(request);

	FCityBonusGetRequestDto requestDto = FCityBonusGetRequestDto();

	requestDto.SetCityId(cityId);
	requestDto.SetCityBonusType(ECityBonusType::CHEfficiency); // here as default
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
	ProcessRequest(request, callBack);
}

void UROVClient::GetBuildingTrainableUnits(EBuildingType buildingType, FGuid buildingId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/trainingdetails");
	request = InsertROVHeaders(request);

	FBuildingTrainingDetailsRequestDto requestDto = FBuildingTrainingDetailsRequestDto();
	requestDto.SetBuildingType(buildingType);
	requestDto.SetBuildingId(buildingId);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
	ProcessRequest(request, callBack);
}

void UROVClient::GetBuildingTrainableUnits(EBuildingType buildingType, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/trainingdetails");
	request = InsertROVHeaders(request);

	FBuildingTrainingDetailsRequestDto requestDto = FBuildingTrainingDetailsRequestDto();
	requestDto.SetBuildingType(buildingType);
	requestDto.SetBuildingId(FGuid::FGuid());
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
	ProcessRequest(request, callBack);
}

void UROVClient::UpgradeBuilding(FString buildingId, FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/upgrade");
	request = InsertROVHeaders(request);

	FBuildingUpgradeRequestDto requestDto = FBuildingUpgradeRequestDto();
	requestDto.SetBuildingId(buildingId);
	requestDto.SetCityId(cityId);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
	ProcessRequest(request, callBack);
}

void UROVClient::GetResourceRates(TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/resourcerate/all");
	request = InsertROVHeaders(request);
	ProcessRequest(request, callBack);
}

void UROVClient::GetResourceTypes(TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/resourcetype/all");
	request = InsertROVHeaders(request);
	ProcessRequest(request, callBack);
}

void UROVClient::GetBuildingTypes(TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/buildingtypes/all");
	request = InsertROVHeaders(request);
	ProcessRequest(request, callBack);
}

void UROVClient::AttemptToTrainUnits(FString cityId, FString buildingId, int amount, EROVUnitType unitType, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/start/training");
	request = InsertROVHeaders(request);

	FTrainingStartTrainingRequestDto requestDto = FTrainingStartTrainingRequestDto();
	requestDto.SetCityId(cityId);
	requestDto.SetBuildingId(buildingId);
	requestDto.SetAmount(amount);
	requestDto.SetUnitType(unitType);

	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));

	ProcessRequest(request, callBack);
}

void UROVClient::GetBuildingUpgradeCosts(FString cityId, FString buildingId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/upgrade/details");

	FBuildingUpgradeCostRequestDto requestDto = FBuildingUpgradeCostRequestDto();
	requestDto.SetCityId(cityId);
	requestDto.SetBuildingId(buildingId);

	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));

	ProcessRequest(request, callBack);
}

void UROVClient::DeconstructBuilding(FString buildingId, FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/building/deconstruct");

	FBuildingDeconstructRequestDto requestDto = FBuildingDeconstructRequestDto();
	requestDto.SetBuildingId(buildingId);
	requestDto.SetCityId(cityId);

	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));

	ProcessRequest(request, callBack);
}

void UROVClient::GetCityUpgradeDetails(FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/city/upgrade/details");
	request = InsertROVHeaders(request);
	FBuildingCityUpgradeDetailsRequestDto requestDto = FBuildingCityUpgradeDetailsRequestDto();
	requestDto.SetCityId(cityId);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));

	ProcessRequest(request, callBack);
}
void UROVClient::StartCityUpgrade(FString cityId, TFunction<void(FString content)> callBack)
{
	auto request = CreateRequest("/city/city/upgrade");
	request = InsertROVHeaders(request);
	FCityUpgradeRequestDto requestDto = FCityUpgradeRequestDto();
	requestDto.SetCityId(cityId);
	request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));

	ProcessRequest(request, callBack);
}

FApiDto *UROVClient::GetResultAsApiDto(FString content, FApiDto *apiDto)
{
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(content);
	TSharedPtr<FJsonObject> JsonObject;
	FString OutputString;
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		auto obj = JsonObject->GetObjectField("payload");
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
		if (FJsonSerializer::Serialize(JsonObject->GetObjectField("payload").ToSharedRef(), JsonWriter))
			JsonWriter->Close();
	}

	UFileManagementUtilities::JsonToStruct(content, apiDto);
	apiDto->SetPayLoad(OutputString);
	return apiDto;
}

FApiDto *UROVClient::GetResultAsApiDtoWithStringResult(FString content, FApiDto *apiDto)
{
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(content);
	TSharedPtr<FJsonObject> JsonObject;
	FString OutputString;
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		OutputString = JsonObject->GetStringField("payload");

	UFileManagementUtilities::JsonToStruct(content, apiDto);
	apiDto->SetPayLoad(OutputString);
	return apiDto;
}
#pragma optimize("", on)
