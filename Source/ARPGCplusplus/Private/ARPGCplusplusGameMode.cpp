// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARPGCplusplusGameMode.h"

#include "ARPGCplusplusPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ARPGCplusplusCharacter.h"
#include "ARPGGameInstance.h"
#include "UObject/ConstructorHelpers.h"

AARPGCplusplusGameMode::AARPGCplusplusGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AARPGCplusplusPlayerController::StaticClass();

	GameInstance = Cast<UARPGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// set default pawn class to our Blueprinted character
	if (GameInstance != nullptr)
	{
		DefaultPawnClass = GameInstance->getCurrentDesiredPawn();
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Characters/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}