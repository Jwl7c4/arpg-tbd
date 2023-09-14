// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PotionItem.h"
#include "InventoryComponent.h"
#include "ARPGCplusplusCharacter.h"

void UPotionItem::Use(AARPGCplusplusCharacter* Character)
{
	// bp Use adds gameplay effect to character. we remove it here
	OwnerInventory->RemoveItem(this);
}
