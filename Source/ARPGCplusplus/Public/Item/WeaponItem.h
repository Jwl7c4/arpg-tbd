// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EquippableItem.h"

#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class ARPGCPLUSPLUS_API UWeaponItem : public UEquippableItem
{
	GENERATED_BODY()

public:

	UWeaponItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EWeaponType WeaponType;
	
	// todo - add stats later
protected:

	virtual void Use(class AARPGCplusplusCharacter* Character) override;

	virtual void EquipItem(class AARPGCplusplusCharacter* Character, class UItem* Item) override;
};
