// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARPGCplusplusGameMode.h"
#include "ARPGCplusplusPlayerController.h"
#include "ARPGCplusplusCharacter.h"
#include "UObject/ConstructorHelpers.h"

AARPGCplusplusGameMode::AARPGCplusplusGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AARPGCplusplusPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_KnightCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}