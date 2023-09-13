// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

UItem::UItem()
{
	UseActionText = FText::FromString("Description for on use action");
	ItemDisplayName = FText::FromString("Item's Display Name");
	ItemDescription = FText::FromString("Item description");
	MaxStackCount = 1;
	CurrentStackCount = 0;
}
