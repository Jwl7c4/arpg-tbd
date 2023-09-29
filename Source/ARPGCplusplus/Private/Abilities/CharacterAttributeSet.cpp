// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CharacterAttributeSet.h"
#include "GamePlayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "CharacterBase.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	Health = 0.0f;
	MaxHealth = Health;
	HealthRegenRate = 0.f;
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetMaxHealth(GetMaxHealth());
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		if (GetHealth() <= 0) {
			UE_LOG(LogTemp, Warning, TEXT("UCharacterAttributeSet::PostGameplayEffectExecute - Health less than 0"));

			if (ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
			{
				AvatarCharacter->OnDeath();
			}
		}
	}
}

void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void UCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Health, OldHealth);
}

void UCharacterAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, HealthRegenRate, OldHealthRegenRate);
}
