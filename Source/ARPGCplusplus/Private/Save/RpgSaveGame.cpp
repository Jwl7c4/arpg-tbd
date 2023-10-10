// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/RpgSaveGame.h"

#include "Save/CharacterSaveData.h"
#include "Player/PlayerStateBase.h"
#include "ARPGCplusplusCharacter.h"

// struct imports
#include "InventoryComponent.h"

URpgSaveGame::URpgSaveGame()
{
	MaxCharacters = 5;
}

bool URpgSaveGame::CreateCharacter(FString CharacterName, TSubclassOf<APawn> CharacterClass)
{
	int InitialCharacterCount = Characters.Num();
	if (Characters.Num() >= MaxCharacters)
	{
		UE_LOG(LogTemp, Warning, TEXT("URpgSaveGame::CreateCharacter - max characters already created"));
		return false;
	}

	FCharacterData StructCharacter;
	StructCharacter.CharacterClass = CharacterClass;
	StructCharacter.CharacterName = CharacterName;
	StructCharacter.CharacterLevel = 1;
	Characters.Add(StructCharacter);
	

	//UCharacterSaveData* CreatedCharacterData = NewObject<UCharacterSaveData>();
	//CreatedCharacterData->CreateInitialCharacterData(CharacterName, CharacterClass);
	//Characters.Add(CreatedCharacterData);

	return Characters.Num() > InitialCharacterCount;
}

void URpgSaveGame::SaveCharacterData(int CharacterSlotIndex, AARPGCplusplusCharacter* Character, APlayerStateBase* PlayerState)
{
	//UCharacterSaveData* CharacterData;
	//if (Characters.Num() == 0)
	//{
	//	CharacterData = NewObject<UCharacterSaveData>(this, UCharacterSaveData::StaticClass());
	//}
	//else {
	//	CharacterData = Characters[CharacterSlotIndex];
	//}

	//CharacterData->SavePlayerCharacterData(Character);
	//CharacterData->SavePlayerStateData(PlayerState);

	FCharacterData StructCharacter;
	if (Characters.Num() > 0)
	{
		StructCharacter = Characters[CharacterSlotIndex];
	}

	// save character data
	for (auto& Item : Character->Inventory->Items)
	{
		StructCharacter.Items.Add(Item);
	}

	// save player state data
	StructCharacter.CharacterName = PlayerState->CharacterName;
	StructCharacter.CharacterLevel = PlayerState->CurrentLevel;
	StructCharacter.CurrentXp = PlayerState->CurrentXp;
	StructCharacter.SaveGameIndex = PlayerState->SaveGameIndex;
}

void URpgSaveGame::LoadCharacterData(int CharacterSlotIndex, AARPGCplusplusCharacter* OutCharacter, APlayerStateBase* OutPlayerState)
{
	if (!Characters.IsValidIndex(CharacterSlotIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("URpgSaveGame::LoadCharacterData - slot index: %d not valid"), CharacterSlotIndex);
	}
	UCharacterSaveData* CharacterData = Characters[CharacterSlotIndex];

	CharacterData->LoadPlayerCharacterData(OutCharacter);
	CharacterData->LoadPlayerStateData(OutPlayerState);
}
