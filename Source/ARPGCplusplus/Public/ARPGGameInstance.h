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

	void Init();

private:
	TArray<TSubclassOf<APawn>> AvailablePawns;

	TSubclassOf<APawn> SelectedPawnsClass;
};
