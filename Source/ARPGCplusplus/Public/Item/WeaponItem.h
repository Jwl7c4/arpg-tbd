// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EquippableItem.h"
#include "GameplayTagContainer.h"

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

	// todo - gameplay ability for specific weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UGameplayAbility> EquipAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UGameplayAbility> UnEquipAbility;
	
	// todo - add stats later
protected:

	virtual void Use(class AARPGCplusplusCharacter* Character) override;
	
	virtual void UnequipItem(class AARPGCplusplusCharacter* Character) override;

private:

	void EquipGameplayAbility(AARPGCplusplusCharacter* Character);

	void UnequipGameplayAbility(AARPGCplusplusCharacter* Character);
};
