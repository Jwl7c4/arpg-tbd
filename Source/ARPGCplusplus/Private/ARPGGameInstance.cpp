// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGGameInstance.h"

#include "Save/SaveGameSlots.h"
#include "Kismet/GameplayStatics.h"

UARPGGameInstance::UARPGGameInstance()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassOne(TEXT("/Game/Characters/Mannequins/BP_TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassTwo(TEXT("/Game/Characters/Knight/BP_KnightCharacter"));
	AvailablePawns.Add(PlayerPawnBPClassOne.Class);
	AvailablePawns.Add(PlayerPawnBPClassTwo.Class);

	CharacterSaveSlotName = "";
	SlotsDataName = "Slots";
}

void UARPGGameInstance::Init()
{
	Super::Init();

	SelectedPawnsClass = AvailablePawns[1];

	bool bSaveExists = UGameplayStatics::DoesSaveGameExist(SlotsDataName, 0);
	if (bSaveExists)
	{
		// todo - async load for performance
		//FAsyncLoadGameFromSlotDelegate LoadGameDelegate;
		//LoadGameDelegate.BindUFunction(this, FName("OnAsyncLoadCompleted"));
		//UGameplayStatics::AsyncLoadGameFromSlot(SlotsDataName, 0, LoadGameDelegate);

		SlotSaveData = Cast<USaveGameSlots>(UGameplayStatics::LoadGameFromSlot(SlotsDataName, 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UARPGGameInstance::Init - no SlotSaveData exists yet"));
		SlotSaveData = Cast<USaveGameSlots>(UGameplayStatics::CreateSaveGameObject(USaveGameSlots::StaticClass()));
	}
}

TSubclassOf<APawn> UARPGGameInstance::getCurrentDesiredPawn()
{
	if (!SelectedPawnsClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UARPGGameInstance::Init - No pawn selected when requested. defaulting"));
		Init();
	}
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

bool UARPGGameInstance::AddSaveSlot(FString SlotName)
{
	if (!SlotSaveData)
	{
		return false;
	}

	if (SlotSaveData->AddSlotName(SlotName))
	{
		return UGameplayStatics::SaveGameToSlot(SlotSaveData, SlotsDataName, 0);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::AddSaveSlot - could not add slot name: %s"), *SlotName);
		return false;
	}
}

bool UARPGGameInstance::DeleteSlotName(FString SlotName)
{
	if (!SlotSaveData)
	{
		return false;
	}

	if (SlotSaveData->DeleteSlotName(SlotName))
	{
		return UGameplayStatics::SaveGameToSlot(SlotSaveData, SlotsDataName, 0);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::AddSaveSlot - could not delete slot name: %s"), *SlotName);
		return false;
	}
}

// todo - not used until async load
void UARPGGameInstance::OnAsyncLoadCompleted(bool bWasSuccessful, USaveGame* LoadedSaveGame)
{
	if (bWasSuccessful && LoadedSaveGame)
	{
		SlotSaveData = Cast<USaveGameSlots>(LoadedSaveGame);
		if (SlotSaveData)
		{
			// Handle the loaded save game slots object here.
			// not sure if will need anything here. just log else
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::OnAsyncLoadCompleted - could not cast to USaveGameSlots"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UARPGGameInstance::OnAsyncLoadCompleted - not successful or no saved slots found"));
	}
}
