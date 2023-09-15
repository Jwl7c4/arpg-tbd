// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "InventoryComponent.h"

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

		UE_LOG(LogTemp, Warning, TEXT("UWeaponItem::Use - swapping %d for %d"), CurrentWeapons->WeaponType, this->WeaponType);

		EquipItem(Character, this);
		OwnerInventory->RemoveItem(this);
		OwnerInventory->AddItem(CurrentWeapons);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWeaponItem::Use - empty slot scenario"));
		EquipItem(Character, this);
		OwnerInventory->RemoveItem(this);
	}
}

void UWeaponItem::EquipItem(AARPGCplusplusCharacter* Character, UItem* Item)
{
	UE_LOG(LogTemp, Warning, TEXT("UWeaponItem::EquipItem - equip it!"));
	OwnerInventory->EquippedItems.Add(EEquippableItemType::Weapon, this);
}
