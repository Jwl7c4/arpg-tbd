// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/CharacterSaveData.h"

#include "Player/PlayerStateBase.h"
#include "ARPGCplusplusCharacter.h"
#include "InventoryComponent.h"

UCharacterSaveData::UCharacterSaveData()
{
	CurrentLevel = 0;
	CurrentXp = 0;
	SaveGameIndex = -1;
}

void UCharacterSaveData::SavePlayerStateData(APlayerStateBase* PlayerState)
{
	CurrentLevel = PlayerState->CurrentLevel;
	CurrentXp = PlayerState->CurrentXp;
	SaveGameIndex = PlayerState->SaveGameIndex;
}

void UCharacterSaveData::SavePlayerCharacterData(AARPGCplusplusCharacter* Character)
{
	for (auto& Item : Character->Inventory->Items)
	{
		this->Items.Add(Item);
	}
}

void UCharacterSaveData::LoadPlayerStateData(APlayerStateBase* OutPlayerState)
{
	OutPlayerState->CurrentLevel = CurrentLevel;
	OutPlayerState->CurrentXp = CurrentXp;
	OutPlayerState->SaveGameIndex = SaveGameIndex;
}

void UCharacterSaveData::LoadPlayerCharacterData(AARPGCplusplusCharacter* OutCharacter)
{
	for (auto& Item : Items)
	{
		OutCharacter->Inventory->AddItem(Item);
	}
}
