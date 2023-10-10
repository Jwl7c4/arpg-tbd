// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ARPGCplusplus.h"

#include "RpgSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	TSubclassOf<APawn> CharacterClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	int CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	float CurrentXp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	int SaveGameIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	TArray<class UItem*> Items;
};

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
	TArray<FCharacterData> Characters;
};
