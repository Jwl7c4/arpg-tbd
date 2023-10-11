// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ARPGGameInstance.h"

#include "Save/SaveGameSlots.h"
#include "Save/RpgSaveGame.h"
#include "Character/ARPGCplusplusCharacter.h"
#include "Player/PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"

UARPGGameInstance::UARPGGameInstance()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassOne(TEXT("/Game/Characters/Mannequins/BP_TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassTwo(TEXT("/Game/Characters/Knight/BP_KnightCharacter"));
	AvailablePawns.Add(PlayerPawnBPClassOne.Class);
	AvailablePawns.Add(PlayerPawnBPClassTwo.Class);

	// save data init
	SlotSaveData = nullptr;
	CharacterSaveData = nullptr;
	ProfileName = "";
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
		UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::DeleteSlotName - could not delete slot name: %s"), *SlotName);
		return false;
	}
}

void UARPGGameInstance::LoadProfile(FString LookUpProfileName)
{
	ProfileName = LookUpProfileName;
}

bool UARPGGameInstance::CreateCharacter(FString CharacterName, FCharacterSelectTableRow CharacterRow)
{
	if (!CharacterSaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::CreateCharacter - CharacterSaveData not set"));
		return false;
	}

	bool bWasCharacterAdded = CharacterSaveData->CreateCharacter(CharacterName, CharacterRow.BlueprintType);
	return UGameplayStatics::SaveGameToSlot(CharacterSaveData, ProfileName, 0);
}

// todo save character
bool UARPGGameInstance::SaveCharacter(APlayerStateBase* PlayerState, AARPGCplusplusCharacter* Character)
{
	if (!CharacterSaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::SaveCharacter - CharacterSaveData not set"));
		return false;
	}
	else if (ProfileName == "")
	{
		UE_LOG(LogTemp, Error, TEXT("UARPGGameInstance::SaveCharacter - ProfileName not set"));
		return false;
	}

	// todo - where does index come from?
	CharacterSaveData->SaveCharacterData(0, Character, PlayerState);
	return UGameplayStatics::SaveGameToSlot(CharacterSaveData, ProfileName, 0);
}

// todo - is there a way to decuple this from UI profile click?
bool UARPGGameInstance::LoadCharacters(FString SlotName)
{
	bool bSaveExists = UGameplayStatics::DoesSaveGameExist(SlotName, 0);
	if (bSaveExists)
	{
		CharacterSaveData = Cast<URpgSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UARPGGameInstance::LoadCharacters - no CharacterSaveData exists yet"));
		CharacterSaveData = Cast<URpgSaveGame>(UGameplayStatics::CreateSaveGameObject(URpgSaveGame::StaticClass()));
	}

	return CharacterSaveData != nullptr ? true : false;
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
