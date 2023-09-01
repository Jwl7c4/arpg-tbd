// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ARPGGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "ARPGCplusplusGameMode.generated.h"

UCLASS(minimalapi)
class AARPGCplusplusGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AARPGCplusplusGameMode();

private:
	UARPGGameInstance* GameInstance;
};
