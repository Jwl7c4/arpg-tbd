// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem.h"

UEquippableItem::UEquippableItem()
{
	ItemType = EEquippableItemType::None;
}

FItemData UEquippableItem::CreateItemSaveObject()
{
	FItemData ItemData = Super::CreateItemSaveObject();
	ItemData.ItemType = ItemType;

	return ItemData;
}

void UEquippableItem::ConstructItem(AARPGCplusplusCharacter* OutCharacter, FItemData ItemData)
{
	Super::ConstructItem(OutCharacter, ItemData);
	ItemType = ItemData.ItemType;
}
