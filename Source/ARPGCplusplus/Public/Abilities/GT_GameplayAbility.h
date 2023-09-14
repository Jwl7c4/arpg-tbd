// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include <ARPGCplusplus.h>
#include "GT_GameplayAbility.generated.h"

/**
 * todo - rename this better
 */
UCLASS()
class ARPGCPLUSPLUS_API UGT_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UGT_GameplayAbility();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Id")
	EGT_AbilityInput AbilityInputId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Id")
	EGT_AbilityInput AbilityId;
};
