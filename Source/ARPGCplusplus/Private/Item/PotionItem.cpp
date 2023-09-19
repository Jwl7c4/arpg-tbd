// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PotionItem.h"
#include "InventoryComponent.h"
#include "AbilitySystemComponent.h"
#include "ARPGCplusplusCharacter.h"

void UPotionItem::Use(AARPGCplusplusCharacter* Character)
{
	if (PotionGameplayEffectClass)
	{
		UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
		if (AbilitySystemComponent)
		{
			FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();

			// Create an instance of the Gameplay Effect
			UGameplayEffect* GameplayEffect = NewObject<UGameplayEffect>(this, PotionGameplayEffectClass);

			// Apply the Gameplay Effect
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(PotionGameplayEffectClass, 1, ContextHandle);
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UPotionItem::Use - No effect set up on item. Check BP"));
	}

	OwnerInventory->RemoveItem(this);
}
