// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGCplusplusEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Components/WidgetComponent.h"
#include "Abilities/GT_GameplayAbility.h"


// Sets default values
AARPGCplusplusEnemyCharacter::AARPGCplusplusEnemyCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	RootComponent = GetCapsuleComponent();

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	if (HealthBarWidgetClass != nullptr) {
		HealthBarWidgetComponent->SetWidgetClass(HealthBarWidgetClass);
	}
	HealthBarWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AARPGCplusplusEnemyCharacter::AddInitialCharacterAbilities()
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
				AbilitySystemComponent->GiveAbility(AbilitySpec);
				UE_LOG(LogTemp, Warning, TEXT("Ability Name : %s"), *CurrentGameplayAbilityClass.GetDefaultObject()->GetName());
			}
		}
	}

	bWerecharacterAbilitiesGiven = true;
}

void AARPGCplusplusEnemyCharacter::AddInitialCharacterEffects()
{
	if (!IsValid(AbilitySystemComponent) || bWereCharacterEffectsGiven) {
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> CurrentGameplayEffectClass : InitialGameplayAbility)
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


// Called when the game starts or when spawned
//void AARPGCplusplusEnemyCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void AARPGCplusplusEnemyCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
//void AARPGCplusplusEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

