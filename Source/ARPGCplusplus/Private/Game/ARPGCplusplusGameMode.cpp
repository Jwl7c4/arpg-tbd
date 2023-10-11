// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/ARPGCplusplusGameMode.h"

#include "Player/ARPGCplusplusPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/ARPGCplusplusCharacter.h"
#include "Player/PlayerStateBase.h"
#include "Game/ARPGGameInstance.h"
#include "UObject/ConstructorHelpers.h"

AARPGCplusplusGameMode::AARPGCplusplusGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Game mode constructor"));
	// use our custom PlayerController class
	PlayerControllerClass = AARPGCplusplusPlayerController::StaticClass();

	GameInstance = Cast<UARPGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// set default pawn class to our Blueprinted character
	if (GameInstance != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusGameMode::AARPGCplusplusGameMode - Game mode setting pawn class"));
		DefaultPawnClass = GameInstance->getCurrentDesiredPawn();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AARPGCplusplusGameMode::AARPGCplusplusGameMode - Game mode could not cast"));
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Characters/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass = APlayerStateBase::StaticClass();
}

void AARPGCplusplusGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{

	// set default pawn class to our Blueprinted character
	if (GameInstance != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusGameMode::AARPGCplusplusGameMode - Game mode setting pawn class"));
		DefaultPawnClass = GameInstance->getCurrentDesiredPawn();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AARPGCplusplusGameMode::AARPGCplusplusGameMode - Game mode could not cast"));
	}
	Super::InitGame(MapName, Options, ErrorMessage);
}
