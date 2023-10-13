// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Character/CharacterSelectTableRow.h"

#include "ARPGGameInstance.generated.h"

/**
 *
 */
UCLASS()
class ARPGCPLUSPLUS_API UARPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UARPGGameInstance();

	TSubclassOf<APawn> getCurrentDesiredPawn();

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<APawn>> getAllAvailablePawns();

	UFUNCTION(BlueprintCallable)
	void setSelectedPawn(TSubclassOf<APawn> SelectedPawn);

	UFUNCTION(BlueprintCallable)
	bool AddSaveSlot(FString SlotName);

	bool DeleteSlotName(FString SlotName);

	UFUNCTION(BlueprintCallable)
	void LoadProfile(FString LookUpProfileName);

	UFUNCTION(BlueprintCallable)
	bool CreateCharacter(FString CharacterName, FCharacterSelectTableRow CharacterRow);

	UFUNCTION(BlueprintCallable)
	bool SaveCharacter(class APlayerStateBase* PlayerState, class AARPGCplusplusCharacter* Character);

	UFUNCTION(BlueprintCallable)
	bool LoadCharacters(FString SlotName);

	UFUNCTION(BlueprintCallable)
	bool LoadCharacter(class AARPGCplusplusCharacter* OutCharacter, class APlayerStateBase* OutPlayerState);

	UFUNCTION(BlueprintCallable)
	void SetCharacterIndex(int SelectedIndex);

protected:	

	UFUNCTION()
	void OnAsyncLoadCompleted(bool bWasSuccessful, USaveGame* LoadedSaveGame);

	virtual void Init() override;

	TArray<TSubclassOf<APawn>> AvailablePawns;

	TSubclassOf<APawn> SelectedPawnsClass;

	FString SlotsDataName;

	FString ProfileName;

	UPROPERTY(BlueprintReadOnly)
	class USaveGameSlots* SlotSaveData;

	UPROPERTY(BlueprintReadOnly)
	class URpgSaveGame* CharacterSaveData;

	int CharacterSaveIndex;

};
