#pragma once

#include "CoreMinimal.h"
#include "../Enums/ROVEnums.h"
#include "FBaseDtos.generated.h"


USTRUCT()
struct FBase {
	GENERATED_BODY()
public:
	FBase() {

	}

	static FGuid ToGuid(FString str) {
		FGuid g;
		FGuid::Parse(str, g);
		return g;
	}

	static FString ToString(FGuid guid) {
		return guid.ToString(EGuidFormats::DigitsWithHyphens);
	}

protected:

};

USTRUCT()
struct FResourceDto {
	GENERATED_BODY()
public:
	FResourceDto() {
		Amount = 0;
		ResourceType = EResourceType::INVALID;
	}

	EResourceType GetResourceType() { return ResourceType; }
	int GetAmount() { return Amount; }
protected:

	UPROPERTY() EResourceType ResourceType;
	UPROPERTY() int Amount;

};

USTRUCT()
struct FBuildingResourceDto {
	GENERATED_BODY()
public:
	FBuildingResourceDto() {
		Amount = 0;
		ResourceType = EResourceType::INVALID;
	}

	int GetLevel() { return Level; }
	EResourceType GetResourceType() { return ResourceType; }
	int GetAmount() { return Amount; }
protected:

	UPROPERTY() int Level;
	UPROPERTY() EResourceType ResourceType;
	UPROPERTY() int Amount;

};

USTRUCT()
struct FBuildingCostDto {
	GENERATED_BODY()
public:
	FBuildingCostDto() {
		BuildingType = EBuildingType::INVALID;
	}

	TArray<FBuildingResourceDto> GetResources() { return Resources; }
	EBuildingType GetBuildingType() { return BuildingType; }
protected:

	UPROPERTY() TArray<FBuildingResourceDto> Resources;
	UPROPERTY() EBuildingType BuildingType;

};

