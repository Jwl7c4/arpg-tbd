// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "InventoryComponent.h"
#include "GameplayTagsModule.h"
#include "ARPGCplusplusCharacter.h"

UWeaponItem::UWeaponItem()
{
	WeaponType = EWeaponType::None;
}

void UWeaponItem::Use(AARPGCplusplusCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UWeaponItem::Use - used weapon. todo - equip it"));

	UEquippableItem** CurrentWeapon = OwnerInventory->EquippedItems.Find(EEquippableItemType::Weapon);
	if (CurrentWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWeaponItem::Use - swap scenario"));
		// get item from slot
		UWeaponItem* CurrentWeapons = Cast<UWeaponItem>(*CurrentWeapon);
		bool bSwapSuccess = OwnerInventory->EquipItem(this, CurrentWeapons);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWeaponItem::Use - empty slot scenario"));
		bool bEquipSuccess = OwnerInventory->EquipItem(this, nullptr);
	}

	// todo - this not clean. check if set
	Character->Tags.Remove(RemoveOtherWeaponTag.GetTagName());
	Character->Tags.Add(EquippedWeaponTag.GetTagName());
}
