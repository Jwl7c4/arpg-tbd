// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ARPGCplusplus.h"
#include "Engine/DataTable.h"
#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct ARPGCPLUSPLUS_API FItemMasterTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EEquippableItemType EquippableItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UItem> ItemDefinition;

	FItemMasterTableRow()
	{
		DisplayName = TEXT("DefaultName");
		ItemType = EItemType::None;
		EquippableItemType = EEquippableItemType::None;
		WeaponType = EWeaponType::None;
		ItemDefinition = nullptr;
	}
};
