// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ARPGCplusplus.h"
#include "Item.h"

#include "EquippableItem.generated.h"

/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class ARPGCPLUSPLUS_API UEquippableItem : public UItem
{
	GENERATED_BODY()

public:

	UEquippableItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EEquippableItemType ItemType;

	virtual void EquipItem(class AARPGCplusplusCharacter* Character, class UItem* Item) PURE_VIRTUAL(UEquippableItem, );

};
