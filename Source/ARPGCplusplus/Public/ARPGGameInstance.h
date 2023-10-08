// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	// todo - save character/state info in CharacterSaveSlotName at index of character

	// todo - set active save slot name somewhere
	FString CharacterSaveSlotName;

protected:

	UFUNCTION()
	void OnAsyncLoadCompleted(bool bWasSuccessful, USaveGame* LoadedSaveGame);

	virtual void Init() override;

	TArray<TSubclassOf<APawn>> AvailablePawns;

	TSubclassOf<APawn> SelectedPawnsClass;

	FString SlotsDataName;

	UPROPERTY(BlueprintReadOnly)
	class USaveGameSlots* SlotSaveData;

	class URpgSaveGame* CharacterSaveData;

};
