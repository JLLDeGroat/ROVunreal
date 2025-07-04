// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseROVClient.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

void UBaseROVClient::ProcessRequest(FHttpRequestRef request, TFunction<void(FString content)> callBack)
{
    request->OnProcessRequestComplete().BindLambda(
        [callBack](
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable
        {
            if (connectedSuccessfully)
            {
                callBack(pResponse->GetContentAsString());
            }
            else
            {
                UDebugMessages::LogError(UBaseROVClient::StaticClass(), "api Error");

                if (pRequest->GetStatus() == EHttpRequestStatus::Failed && pRequest->GetFailureReason() == EHttpFailureReason::ConnectionError)
                {
                    auto failedString = "{\"error\":\"failed to connect to api\", \"success\": \"false\" }";
                    callBack(failedString);
                }
            }
        });
    request->ProcessRequest();
}
#pragma optimize("", off)
void UBaseROVClient::ProcessRequest(FHttpRequestRef request, TFunction<void(FGenericApiResponse responseDto)> callBack)
{
    request->OnProcessRequestComplete().BindLambda(
        [callBack](
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable
        {
            if (connectedSuccessfully)
            {
                TSharedPtr<FJsonObject> RootObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(pResponse->GetContentAsString());
                if (FJsonSerializer::Deserialize(Reader, RootObject) && RootObject.IsValid())
                {
                    FGenericApiResponse dto;
                    dto.SetSuccess(RootObject->GetBoolField(TEXT("success")));
                    dto.SetError(RootObject->GetStringField(TEXT("error")));

                    TSharedPtr<FJsonObject> PayloadObj = RootObject->GetObjectField(TEXT("payload"));
                    FString PayloadStr;
                    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&PayloadStr);
                    FJsonSerializer::Serialize(PayloadObj.ToSharedRef(), Writer);

                    dto.SetPayload(PayloadStr);
                    callBack(dto);
                }
            }
            else
            {
                UDebugMessages::LogError(UBaseROVClient::StaticClass(), "api Error");

                if (pRequest->GetStatus() == EHttpRequestStatus::Failed && pRequest->GetFailureReason() == EHttpFailureReason::ConnectionError)
                {
                    FGenericApiResponse responseDto;
                    responseDto.SetError("failed to connect to api");
                    responseDto.SetPayload("");
                    responseDto.SetSuccess(false);
                    callBack(responseDto);
                }
            }
        });
    request->ProcessRequest();
}
#pragma optimize("", on)
FHttpRequestRef UBaseROVClient::CreateRequest(FString url, FString method)
{
    auto request = FHttpModule::Get().CreateRequest();
    request->SetURL(_baseUrl + url);
    request->SetVerb(method);
    request->SetHeader("Content-Type", "application/json");
    request->SetTimeout(70);
    return request;
}

FHttpRequestRef UBaseROVClient::InsertROVHeaders(FHttpRequestRef request)
{
    request->SetHeader(_apiKeyHeaderName, _apiKey);
    request->SetHeader(_tokenHeaderName, _token);
    return request;
}