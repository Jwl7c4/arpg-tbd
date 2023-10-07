// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterSaveData.generated.h"

/**
 *
 */
UCLASS()
class ARPGCPLUSPLUS_API UCharacterSaveData : public UObject
{
	GENERATED_BODY()

public:

	UCharacterSaveData();

	void SavePlayerStateData(class APlayerStateBase* PlayerState);

	void SavePlayerCharacterData(class AARPGCplusplusCharacter* Character);

	void LoadPlayerStateData(class APlayerStateBase* OutPlayerState);

	void LoadPlayerCharacterData(class AARPGCplusplusCharacter* OutCharacter);

protected:

	// Player State
	int CurrentLevel;

	float CurrentXp;

	int SaveGameIndex;

	// todo - future abilities enabled saved in state

	// todo - should inventory be in state vs character for player. if so might not need character in rpgsavegame methods and here
	// Player Character
	TArray<class UItem*> Items;
};
