// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/ARPGCplusplusGameMode.h"

#include "Player/ARPGCplusplusPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerStateBase.h"
#include "Game/ARPGGameInstance.h"
#include "UObject/ConstructorHelpers.h"

AARPGCplusplusGameMode::AARPGCplusplusGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AARPGCplusplusPlayerController::StaticClass();

	GameInstance = Cast<UARPGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DefaultPawnClass = nullptr;

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Characters/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass = APlayerStateBase::StaticClass();
}

UClass* AARPGCplusplusGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	// set default pawn class to our Blueprinted character
	if (GameInstance != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusGameMode::AARPGCplusplusGameMode - Game mode setting pawn class"));
		DefaultPawnClass = GameInstance->getCurrentDesiredPawn();
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AARPGCplusplusGameMode::AARPGCplusplusGameMode - Game mode could not cast"));
		return nullptr;
	}
}
