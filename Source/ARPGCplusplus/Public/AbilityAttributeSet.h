// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilityAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ARPGCPLUSPLUS_API UAbilityAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UAbilityAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Ability", ReplicatedUsing = OnRep_DodgeDistance)
	FGameplayAttributeData DodgeDistance;
	ATTRIBUTE_ACCESSORS(UAbilityAttributeSet, DodgeDistance);


	UPROPERTY(BlueprintReadOnly, Category = "Ability", ReplicatedUsing = OnRep_MaxDodgeDistance)
	FGameplayAttributeData MaxDodgeDistance;
	ATTRIBUTE_ACCESSORS(UAbilityAttributeSet, MaxDodgeDistance);

	UFUNCTION()
	void OnRep_DodgeDistance(const FGameplayAttributeData& OldDodgeDistance);

	UFUNCTION()
	void OnRep_MaxDodgeDistance(const FGameplayAttributeData& OldMaxDodgeDistance);
};
