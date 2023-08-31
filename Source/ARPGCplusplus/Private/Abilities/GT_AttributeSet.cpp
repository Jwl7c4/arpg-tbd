// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GT_AttributeSet.h"
#include "GamePlayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UGT_AttributeSet::UGT_AttributeSet()
{
	MaxHealth = 100.0f;
	Health = 100.0f;
	DodgeDistance = 3000.0f;
}

void UGT_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UGT_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGT_AttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UGT_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGT_AttributeSet, MaxHealth, OldMaxHealth);
}

void UGT_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGT_AttributeSet, Health, OldHealth);
}

void UGT_AttributeSet::OnRep_DodgeDistance(const FGameplayAttributeData& OldDodgeDistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGT_AttributeSet, DodgeDistance, OldDodgeDistance);
}
