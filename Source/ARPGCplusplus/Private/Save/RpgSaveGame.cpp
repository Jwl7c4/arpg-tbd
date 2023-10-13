// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/RpgSaveGame.h"

#include "Player/PlayerStateBase.h"
#include "Character/ARPGCplusplusCharacter.h"
#include "Item/InventoryComponent.h"
#include "Item/Item.h"
#include <Item/WeaponItem.h>
#include <Item/PotionItem.h>

URpgSaveGame::URpgSaveGame()
{
	MaxCharacters = 5;
}

bool URpgSaveGame::CreateCharacter(FString CharacterName, TSubclassOf<AARPGCplusplusCharacter> CharacterClass)
{
	int InitialCharacterCount = Characters.Num();
	if (Characters.Num() >= MaxCharacters)
	{
		UE_LOG(LogTemp, Warning, TEXT("URpgSaveGame::CreateCharacter - max characters already created"));
		return false;
	}

	FCharacterData CharacterData;
	CharacterData.CharacterClass = CharacterClass;
	CharacterData.CharacterName = CharacterName;
	CharacterData.CharacterLevel = 1;
	CharacterData.CurrentXp = 0.f;
	CharacterData.SaveGameIndex = -1;
	Characters.Add(CharacterData);

	return Characters.Num() > InitialCharacterCount;
}

void URpgSaveGame::SaveCharacterData(int CharacterSlotIndex, AARPGCplusplusCharacter* Character, APlayerStateBase* PlayerState)
{
	if (Characters.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("URpgSaveGame::SaveCharacterData - character array no indexes"));
		return;
	}

	FCharacterData* CharacterData = &Characters[CharacterSlotIndex];

	// save character data
	// bag items
	//CharacterData->Items = Character->Inventory->Items;
	CharacterData->EquippedItems = Character->Inventory->EquippedItems;

	TArray<FItemData> TempArray;
	for (auto& Item : Character->Inventory->Items)
	{
		FItemData ItemData = Item->CreateItemSaveObject();
		TempArray.Add(ItemData);
	}
	if (TempArray.Num() > 0)
	{
		CharacterData->Items = TempArray;
	}
	//// equipped items
	//for (auto& EquippedItem : Character->Inventory->EquippedItems)
	//{
	//	CharacterData->EquippedItems.Add(EquippedItem.Key, EquippedItem.Value);
	//}

	// save player state data
	CharacterData->CharacterName = PlayerState->CharacterName;
	CharacterData->CharacterLevel = PlayerState->CurrentLevel;
	CharacterData->CurrentXp = PlayerState->CurrentXp;
	CharacterData->SaveGameIndex = PlayerState->SaveGameIndex;
}

void URpgSaveGame::LoadCharacterData(int CharacterSlotIndex, AARPGCplusplusCharacter* OutCharacter, APlayerStateBase* OutPlayerState)
{
	if (!Characters.IsValidIndex(CharacterSlotIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("URpgSaveGame::LoadCharacterData - slot index: %d not valid"), CharacterSlotIndex);
	}
	FCharacterData CharacterData = Characters[CharacterSlotIndex];

	// load character data
	// bag items
	//OutCharacter->Inventory->Items = CharacterData.Items;
	OutCharacter->Inventory->EquippedItems = CharacterData.EquippedItems;

	TArray<UItem*> TempArray;
	for (auto& Item : CharacterData.Items)
	{
		UItem* InvItem = nullptr;
		if (Item.ItemClass == UWeaponItem::StaticClass())
		{
			InvItem = NewObject<UWeaponItem>();
		}
		else if (Item.ItemClass == UPotionItem::StaticClass())
		{
			InvItem = NewObject<UPotionItem>();
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("URpgSaveGame::LoadCharacterData - Not found class of item found. please add type here"));
		}

		InvItem->ConstructItem(OutCharacter, Item);
		TempArray.Add(InvItem);
	}
	OutCharacter->Inventory->Items = TempArray;
	//// equipped items
	//for (auto& EquippedItem : CharacterData.EquippedItems)
	//{
	//	OutCharacter->Inventory->EquippedItems.Add(EquippedItem.Key, EquippedItem.Value);
	//}

	// load player state
	OutPlayerState->CharacterName = CharacterData.CharacterName;
	OutPlayerState->CurrentLevel = CharacterData.CharacterLevel;
	OutPlayerState->CurrentXp = CharacterData.CurrentXp;
	OutPlayerState->SaveGameIndex = CharacterData.SaveGameIndex;
}
