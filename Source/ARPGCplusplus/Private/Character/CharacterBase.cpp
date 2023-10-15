// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Abilities/GT_GameplayAbility.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::AddInitialCharacterAbilities()
{
	if (!IsValid(AbilitySystemComponent) || bWerecharacterAbilitiesGiven) {
		return;
	}

	for (TSubclassOf<UGT_GameplayAbility> CurrentGameplayAbilityClass : InitialGameplayAbility)
	{
		if (IsValid(CurrentGameplayAbilityClass))
		{
			UGT_GameplayAbility* CurrentAbility = CurrentGameplayAbilityClass->GetDefaultObject<UGT_GameplayAbility>();
			if (IsValid(CurrentAbility))
			{
				FGameplayAbilitySpec AbilitySpec(CurrentAbility, 1, static_cast<int32>(CurrentAbility->AbilityInputId), this);
				AbilitySystemComponent->GiveAbility(
					FGameplayAbilitySpec(CurrentAbility, 1, static_cast<int32>(CurrentAbility->AbilityInputId), this));
			}
		}
	}

	bWerecharacterAbilitiesGiven = true;
}


// todo - adding extra end effect as it gets ignored (duplicated extra dodge)
void ACharacterBase::AddInitialCharacterEffects()
{
	if (!IsValid(AbilitySystemComponent) || bWereCharacterEffectsGiven) {
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> CurrentGameplayEffectClass : InitialGameplayEffects)
	{
		if (IsValid(CurrentGameplayEffectClass))
		{
			FGameplayEffectSpecHandle CurrentEffectHandle = AbilitySystemComponent->MakeOutgoingSpec(CurrentGameplayEffectClass, 1, EffectContextHandle);
			if (CurrentEffectHandle.IsValid())
			{
				// able to use to remove certain effects based on state
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*CurrentEffectHandle.Data.Get(), AbilitySystemComponent);
			}
		}
	}

	bWereCharacterEffectsGiven = true;
}

void ACharacterBase::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::OnDeath - Calling BP"));
	// call bp on death method
	On_Death();
}

