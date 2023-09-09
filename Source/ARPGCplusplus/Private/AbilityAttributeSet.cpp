// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAttributeSet.h"
#include "GamePlayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAbilityAttributeSet::UAbilityAttributeSet()
{
	DodgeDistance = 3000.0f;
	MaxDodgeDistance = DodgeDistance;
}

void UAbilityAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UAbilityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDodgeDistanceAttribute()) {
		SetDodgeDistance(GetDodgeDistance());
	}
}

void UAbilityAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION_NOTIFY(UAbilityAttributeSet, DodgeDistance, COND_None, REPNOTIFY_Always);
}

void UAbilityAttributeSet::OnRep_DodgeDistance(const FGameplayAttributeData& OldDodgeDistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAbilityAttributeSet, DodgeDistance, OldDodgeDistance);
}

void UAbilityAttributeSet::OnRep_MaxDodgeDistance(const FGameplayAttributeData& OldMaxDodgeDistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAbilityAttributeSet, MaxDodgeDistance, OldMaxDodgeDistance);
}
