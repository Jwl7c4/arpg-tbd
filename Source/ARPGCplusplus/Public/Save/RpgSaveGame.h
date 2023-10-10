// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ARPGCplusplus.h"

#include "RpgSaveGame.generated.h"

/**
 *
 */
UCLASS()
class ARPGCPLUSPLUS_API URpgSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	URpgSaveGame();

	bool CreateCharacter(FString CharacterName, TSubclassOf<APawn> CharacterClass);

	// update character data at index with character and state data
	void SaveCharacterData(int CharacterSlotIndex, class AARPGCplusplusCharacter* Character, class APlayerStateBase* PlayerState);

	// get character data from index and update character and state
	void LoadCharacterData(int CharacterSlotIndex, class AARPGCplusplusCharacter* OutCharacter, class APlayerStateBase* OutPlayerState);

protected:

	UPROPERTY(BlueprintReadOnly)
	int MaxCharacters;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UCharacterSaveData*> Characters;
};
