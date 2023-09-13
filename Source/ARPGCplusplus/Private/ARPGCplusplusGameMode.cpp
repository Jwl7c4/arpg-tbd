// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARPGCplusplusGameMode.h"

#include "ARPGCplusplusPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ARPGCplusplusCharacter.h"
#include "Player/PlayerStateBase.h"
#include "ARPGGameInstance.h"
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
		UE_LOG(LogTemp, Warning, TEXT("Game mode setting pawn class"));
		DefaultPawnClass = GameInstance->getCurrentDesiredPawn();
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Characters/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass = APlayerStateBase::StaticClass();
}