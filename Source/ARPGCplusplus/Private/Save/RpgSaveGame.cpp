// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/RpgSaveGame.h"

#include "Save/CharacterSaveData.h"
#include "Player/PlayerStateBase.h"
#include "ARPGCplusplusCharacter.h"

URpgSaveGame::URpgSaveGame()
{
	MaxCharacters = 5;
}

void URpgSaveGame::SaveCharacterData(int CharacterSlotIndex, AARPGCplusplusCharacter* Character, APlayerStateBase* PlayerState)
{
	UCharacterSaveData* CharacterData;
	if (Characters.Num() == 0)
	{
		CharacterData = NewObject<UCharacterSaveData>(this, UCharacterSaveData::StaticClass());
	}
	else {
		CharacterData = Characters[CharacterSlotIndex];
	}

	CharacterData->SavePlayerCharacterData(Character);
	CharacterData->SavePlayerStateData(PlayerState);
}

void URpgSaveGame::LoadCharacterData(int CharacterSlotIndex, AARPGCplusplusCharacter* OutCharacter, APlayerStateBase* OutPlayerState)
{
}
