// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainMenuGameMode.h"

#include "Player/ARPGCplusplusPlayerController.h"
#include "Player/PlayerStateBase.h"
#include "UObject/ConstructorHelpers.h"

AMainMenuGameMode::AMainMenuGameMode()
{

	// use our custom PlayerController class
	PlayerControllerClass = AARPGCplusplusPlayerController::StaticClass();

	DefaultPawnClass = nullptr;

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Characters/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass = APlayerStateBase::StaticClass();
}
