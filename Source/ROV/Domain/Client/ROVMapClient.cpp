// Fill out your copyright notice in the Description page of Project Settings.

#include "ROVMapClient.h"
#include "VgCore/Domain/Debug/DebugMessages.h"
#include "VgFlMngmnt/Domain/FileManagementUtilities.h"
#include "ROVData/Dtos/FGatewayClientDtos.h"
#include "ROVData/Dtos/FBuildingDtos.h"
#include "ROVData/Dtos/FResourceDtos.h"
#include "ROVData/Dtos/FCityUpgradeDtos.h"
#include "ROVData/Dtos/FWorldDtos.h"

void UROVMapClient::GetInitialMapLocation(FString cityId, int radius, TFunction<void(FGenericApiResponse responseDto)> callBack)
{
    auto request = CreateRequest("/world/from/city");
    request = InsertROVHeaders(request);

    FMapLocationAroundCityRequestDto requestDto = FMapLocationAroundCityRequestDto();
    requestDto.SetRadius(radius);
    requestDto.SetCityId(cityId);
    request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
    ProcessRequest(request, callBack);
}

void UROVMapClient::GetLocationsAroundLocation(int x, int y, int radius, TFunction<void(FGenericApiResponse responseDto)> callBack)
{
    auto request = CreateRequest("/world/from/location");
    request = InsertROVHeaders(request);

    FMapLocationAroundLocationRequestDto requestDto = FMapLocationAroundLocationRequestDto();
    requestDto.SetRadius(radius);
    requestDto.SetX(x);
    requestDto.SetY(y);
    request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
    ProcessRequest(request, callBack);
}
#pragma optimize("", off)
void UROVMapClient::GetLocationDetails(int x, int y, FString cityId, EOccupiedType occupationType, TFunction<void(FGenericApiResponse responseDto)> callBack)
{
    auto request = CreateRequest("/world/location/occupation/overview");

    request = InsertROVHeaders(request);

    FMapLocationOccupationDetailsRequestDto requestDto = FMapLocationOccupationDetailsRequestDto();
    requestDto.SetX(x);
    requestDto.SetY(y);
    requestDto.SetCityId(cityId);
    requestDto.SetOccupiedType(occupationType);

    request->SetContentAsString(UFileManagementUtilities::StructToJson(requestDto));
    ProcessRequest(request, callBack);
}
#pragma optimize("", on)