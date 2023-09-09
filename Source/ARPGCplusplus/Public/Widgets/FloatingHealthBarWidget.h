// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemGlobals.h"
#include "FloatingHealthBarWidget.generated.h"

UCLASS()
class ARPGCPLUSPLUS_API UFloatingHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// todo jake - this should be handled by delegate and not called
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void setHealthPercent(const float Health, const float MaxHealth);

//	// Called to initialize the User Widget and bind to Attribute change delegates
//	// Can be called again to re-initialize the values
//	UFUNCTION(BlueprintCallable, Category = "Ability System")
//	bool InitializeAbilitySystemWidget(UAbilitySystemComponent* AbilitySystemComponent = nullptr);
//
//	// Event called when the Maximum Health attribute value changes.
//	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
//	void On_MaximumHealthChanged(const float NewValue, const float OldValue, const float NewPercentage);
//
//	// Event called when the Current Health attribute value changes.
//	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
//	void On_CurrentHealthChanged(const float NewValue, const float OldValue, const float NewPercentage);
//
//protected:
//	TWeakObjectPtr<class UAbilitySystemComponent> AbilitySystem;
//
//	void BindAbilitySystemDelegates();
//
//	FDelegateHandle MaximumHealthChangeDelegate;
//	FDelegateHandle CurrentHealthChangeDelegate;
//
//	void MaximumHealthChanged(const FOnAttributeChangeData& Data);
//	void CurrentHealthChanged(const FOnAttributeChangeData& Data);
};
