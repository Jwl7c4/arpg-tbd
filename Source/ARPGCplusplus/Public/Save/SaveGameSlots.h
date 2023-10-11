// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameSlots.generated.h"

/**
 *
 */
UCLASS()
class ARPGCPLUSPLUS_API USaveGameSlots : public USaveGame
{
	GENERATED_BODY()

public:

	USaveGameSlots();

	bool DoesSlotExist(FString SlotName);

	bool AddSlotName(FString SlotName);

	bool DeleteSlotName(FString SlotName);

protected:

	UPROPERTY(BlueprintReadOnly)
	int MaxSlots;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> SlotNames;
};
