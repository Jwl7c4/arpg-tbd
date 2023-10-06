// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ARPGCplusplus.h"

#include "RpgSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ARPGCPLUSPLUS_API URpgSaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:

	TMap<EClassType, class UCharacterSaveData*> CharacterSaveMap;
};
