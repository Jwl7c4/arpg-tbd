// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PotionItem.h"
#include "InventoryComponent.h"
#include "ARPGCplusplusCharacter.h"

void UPotionItem::Use(AARPGCplusplusCharacter* Character)
{
	// add gameplay effect to character
	UE_LOG(LogTemp, Warning, TEXT("UPotionItem::Use - use potion"));

	OwnerInventory->RemoveItem(this);
}
