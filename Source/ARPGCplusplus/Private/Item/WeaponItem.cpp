// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "InventoryComponent.h"
#include "GameplayTagsModule.h"
#include "AbilitySystemComponent.h"
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

	UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();
	if (ASC)
	{
		// Create an ability spec
		FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
		SpecDef.Ability = EquipAbility;
		FGameplayAbilitySpec Spec(SpecDef, 1); // Set level to 1 or the desired level

		// todo - should this just be permanent?
		ASC->GiveAbilityAndActivateOnce(Spec);

		// Remove the ability after activation (if needed)
		//ASC->RemoveAbility(Spec.Handle);
		ASC->ClearAbility(Spec.Handle);
	}
}
