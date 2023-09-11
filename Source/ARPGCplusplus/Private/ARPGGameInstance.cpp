// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGGameInstance.h"

UARPGGameInstance::UARPGGameInstance()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassOne(TEXT("/Game/Characters/Mannequins/BP_TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassTwo(TEXT("/Game/Characters/Knight/BP_KnightCharacter"));
	AvailablePawns.Add(PlayerPawnBPClassOne.Class);
	AvailablePawns.Add(PlayerPawnBPClassTwo.Class);
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

void UARPGGameInstance::Init()
{
	//SelectedPawnsClass = AvailablePawns[1];
}
