// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ARPGCplusplus.h"

#include "CharacterSelectTableRow.generated.h"

USTRUCT(BlueprintType)
struct ARPGCPLUSPLUS_API FCharacterSelectTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Select")
    EClassType ClassType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Select")
    TSubclassOf<class AARPGCplusplusCharacter> BlueprintType;

    // todo figure out how to show. picture or render or camera somehow?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Select")
    UAnimSequence* AnimationSequence;
};
