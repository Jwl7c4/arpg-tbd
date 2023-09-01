// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGGameInstance.h"

UARPGGameInstance::UARPGGameInstance()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassOne(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassTwo(TEXT("/Game/TopDown/Blueprints/BP_KnightCharacter"));
	AvailablePawns.Add(PlayerPawnBPClassOne.Class);
	AvailablePawns.Add(PlayerPawnBPClassTwo.Class);

	//SelectedPawnsClass = AvailablePawns[1];
}

TSubclassOf<APawn> UARPGGameInstance::getCurrentDesiredPawn()
{
	return SelectedPawnsClass;
}

TArray<TSubclassOf<APawn>> UARPGGameInstance::getAllAvailablePawns()
{
	return AvailablePawns;
}

void UARPGGameInstance::setSelectedPawn(TSubclassOf<APawn> SelectedPawn)
{
	SelectedPawnsClass = SelectedPawn;
}
