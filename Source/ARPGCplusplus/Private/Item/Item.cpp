// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Character/ARPGCplusplusCharacter.h"

UItem::UItem()
{
	UseActionText = FText::FromString("Description for on use action");
	ItemDisplayName = FText::FromString("Item's Display Name");
	ItemDescription = FText::FromString("Item description");
	MaxStackCount = 1;
	CurrentStackCount = 0;
}

FItemData UItem::CreateItemSaveObject()
{
	FItemData ItemData;
	ItemData.ItemClass = this->StaticClass();
	ItemData.UseActionText = UseActionText;
	ItemData.PickupMesh = PickupMesh;
	ItemData.Thumbnail = Thumbnail;
	ItemData.ItemDisplayName = ItemDisplayName;
	ItemData.ItemDescription = ItemDescription;
	ItemData.MaxStackCount = MaxStackCount;
	ItemData.CurrentStackCount = CurrentStackCount;
	ItemData.ItemType = EEquippableItemType::None;

	return ItemData;
}

void UItem::ConstructItem(AARPGCplusplusCharacter* OutCharacter, FItemData ItemData)
{
	World = GetWorld();
	UseActionText = ItemData.UseActionText;
	PickupMesh = ItemData.PickupMesh;
	Thumbnail = ItemData.Thumbnail;
	ItemDisplayName = ItemData.ItemDisplayName;
	ItemDescription = ItemData.ItemDescription;
	MaxStackCount = ItemData.MaxStackCount;
	CurrentStackCount = ItemData.CurrentStackCount;
	OwnerInventory = OutCharacter->Inventory;
}
