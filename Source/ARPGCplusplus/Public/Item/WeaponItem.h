// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EquippableItem.h"
#include "GameplayTagContainer.h"

#include "WeaponItem.generated.h"

/**
 * todo - add stats later
 */
UCLASS()
class ARPGCPLUSPLUS_API UWeaponItem : public UEquippableItem
{
	GENERATED_BODY()

public:

	UWeaponItem();

	FItemData CreateItemSaveObject() override;

	void ConstructItem(AARPGCplusplusCharacter* OutCharacter, FItemData ItemData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EWeaponType WeaponType;

	// todo - gameplay ability for specific weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UGameplayAbility> EquipAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UGameplayAbility> UnEquipAbility;

	void EquipGameplayAbility(AARPGCplusplusCharacter* Character);

	void UnequipGameplayAbility(AARPGCplusplusCharacter* Character);

protected:

	virtual void Use(class AARPGCplusplusCharacter* Character) override;
	
	virtual void UnequipItem(class AARPGCplusplusCharacter* Character) override;

};
