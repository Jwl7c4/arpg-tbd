// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FloatingHealthBarWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/CharacterAttributeSet.h"
#include <Player/PlayerStateBase.h>

//bool UFloatingHealthBarWidget::InitializeAbilitySystemWidget(UAbilitySystemComponent* AbilitySystemComponent)
//{
//	// Reset the Attribute change Delegate Handles in case they are already bound.
//	CurrentHealthChangeDelegate.Reset();
//	MaximumHealthChangeDelegate.Reset();
//	//HealthRegenerationChangeDelegate.Reset();
//	//CurrentStaminaChangeDelegate.Reset();
//	//MaximumStaminaChangeDelegate.Reset();
//	//StaminaRegenerationChangeDelegate.Reset();
//
//	// Reset the Ability System Component pointer if its already set.
//	AbilitySystem = Cast<UAbilitySystemComponent>(AbilitySystemComponent);
//
//	if (!AbilitySystem.Get())
//	{
//		// Check that the Player State Base class is reachable.
//		if (const APlayerStateBase* PlayerStateBase = Cast<APlayerStateBase>(GetOwningPlayerState()))
//		{
//			// Set the Ability System Component reference.
//			AbilitySystem = PlayerStateBase->AbilitySystemComponent;
//		}
//
//		// If the Ability System Component is not valid try using the Owning Player Pawn.
//		// For the case where this Widget is on an Actor who does not have a Player State or the previous method failed.
//		if (!AbilitySystem.Get())
//		{
//			if (const APawn* Pawn = GetOwningPlayerPawn())
//			{
//				// Try setting the pointer again.
//				AbilitySystem = Cast<UAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Pawn));
//			}
//		}
//
//		// Return false if the Ability System Component pointer is still null.
//		if (!AbilitySystem.Get())
//		{
//			return false;
//		}
//	}
//
//	// Bind the Attribute Change Delegates.
//	BindAbilitySystemDelegates();
//
//	return true;
//}
//
//void UFloatingHealthBarWidget::BindAbilitySystemDelegates()
//{
//	{
//		// Bind Health Attribute delegates if the Attribute set is owned by the Ability System Component.
//		if (AbilitySystem->HasAttributeSetForAttribute(UCharacterAttributeSet::GetMaxHealthAttribute()))
//		{
//			MaximumHealthChangeDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UFloatingHealthBarWidget::MaximumHealthChanged);
//			CurrentHealthChangeDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &UFloatingHealthBarWidget::CurrentHealthChanged);
//			//HealthRegenerationChangeDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetHealthRegenerationAttribute()).AddUObject(this, &UAbilitySystemWidget::HealthRegenerationChanged);
//
//			const float MaxHealth = AbilitySystem->GetNumericAttribute(UCharacterAttributeSet::GetMaxHealthAttribute());
//			const float CurrentHealth = AbilitySystem->GetNumericAttribute(UCharacterAttributeSet::GetHealthAttribute());
//
//			// Call the Blueprint Events to initialize the values.
//			On_MaximumHealthChanged(MaxHealth, 0.0f, CurrentHealth / MaxHealth);
//			On_CurrentHealthChanged(CurrentHealth, 0.0f, CurrentHealth / MaxHealth);
//			//On_HealthRegenerationChanged(AbilitySystem->GetNumericAttribute(UHealthAttributeSet::GetHealthRegenerationAttribute()), 0.0f);
//		}
//
//		// Bind Stamina Attribute delegates if the Attribute set is owned by the Ability System Component.
//		//if (AbilitySystem->HasAttributeSetForAttribute(UStaminaAttributeSet::GetMaximumStaminaAttribute()))
//		//{
//		//	MaximumStaminaChangeDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(UStaminaAttributeSet::GetMaximumStaminaAttribute()).AddUObject(this, &UAbilitySystemWidget::MaximumStaminaChanged);
//		//	CurrentStaminaChangeDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(UStaminaAttributeSet::GetCurrentStaminaAttribute()).AddUObject(this, &UAbilitySystemWidget::CurrentStaminaChanged);
//		//	StaminaRegenerationChangeDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(UStaminaAttributeSet::GetStaminaRegenerationAttribute()).AddUObject(this, &UAbilitySystemWidget::StaminaRegenerationChanged);
//
//		//	const float MaxStamina = AbilitySystem->GetNumericAttribute(UStaminaAttributeSet::GetMaximumStaminaAttribute());
//		//	const float CurrentStamina = AbilitySystem->GetNumericAttribute(UStaminaAttributeSet::GetCurrentStaminaAttribute());
//
//		//	// Call the Blueprint Events to initialize the values.
//		//	On_MaximumStaminaChanged(MaxStamina, 0.0f, CurrentStamina / MaxStamina);
//		//	On_CurrentStaminaChanged(CurrentStamina, 0.0f, CurrentStamina / MaxStamina);
//		//	On_StaminaRegenerationChanged(AbilitySystem->GetNumericAttribute(UStaminaAttributeSet::GetStaminaRegenerationAttribute()), 0.0f);
//		//}
//	}
//}
//
//void UFloatingHealthBarWidget::MaximumHealthChanged(const FOnAttributeChangeData& Data)
//{
//	const float CurrentHealth = AbilitySystem->GetNumericAttribute(UCharacterAttributeSet::GetHealthAttribute());
//
//	On_MaximumHealthChanged(Data.NewValue, Data.OldValue, CurrentHealth / Data.NewValue);
//}
//
//void UFloatingHealthBarWidget::CurrentHealthChanged(const FOnAttributeChangeData& Data)
//{
//	const float MaxHealth = AbilitySystem->GetNumericAttribute(UCharacterAttributeSet::GetMaxHealthAttribute());
//
//	On_CurrentHealthChanged(Data.NewValue, Data.OldValue, Data.NewValue / MaxHealth);
//}
