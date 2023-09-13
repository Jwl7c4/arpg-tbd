// Copyright 2021 Joseph "Narxim" Thigpen.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PlayerStateBase.generated.h"

class UCustomAbilitySystemComponent;

// This version of Player State has an Ability System Component and should be the base of any Player State sub-class when using GAS.
UCLASS()
class  APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	APlayerStateBase();

	// The Ability System Component for this PlayerState. 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ability System")
	UAbilitySystemComponent* AbilitySystemComponent;

	// Implement the IAbilitySystemInterface. (This is used to find the Ability System Component)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	class UCharacterAttributeSet* CharacterAttributeSet;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetHealthRegenRate() const;
};