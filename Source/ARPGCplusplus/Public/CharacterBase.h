// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "CharacterBase.generated.h"

UCLASS()
class ARPGCPLUSPLUS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called automatically by the Health Attribute Set when "Current Health" reaches zero.
	void OnDeath();

	// Event called when the the Current Health attribute reaches zero.
	// Note: This will only be called with Authority.
	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

};
