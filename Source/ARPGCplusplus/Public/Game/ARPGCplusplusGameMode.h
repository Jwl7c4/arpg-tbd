// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ARPGCplusplusGameMode.generated.h"

UCLASS(minimalapi)
class AARPGCplusplusGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AARPGCplusplusGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

private:
	class UARPGGameInstance* GameInstance;
};
