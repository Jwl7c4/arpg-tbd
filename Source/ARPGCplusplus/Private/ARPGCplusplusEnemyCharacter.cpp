// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGCplusplusEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "AbilityAttributeSet.h"
#include "Abilities/CharacterAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "AttributeSet.h"
#include "Abilities/GT_GameplayAbility.h"
#include <Widgets/FloatingHealthBarWidget.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AARPGCplusplusEnemyCharacter::AARPGCplusplusEnemyCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	RootComponent = GetCapsuleComponent();

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	HealthBarWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Non Ability attributes
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Ability Systems
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AbilityAttributeSet = CreateDefaultSubobject<UAbilityAttributeSet>(TEXT("AbilityAttributeSet"));
	bWerecharacterAbilitiesGiven = false;
	bWereCharacterEffectsGiven = false;
}

// Called when the game starts or when spawned
void AARPGCplusplusEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddInitialCharacterAbilities();
		AddInitialCharacterEffects();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Ability System not done on enemy"));
	}

	FloatingHealthBarWidget = Cast<UFloatingHealthBarWidget>(HealthBarWidgetComponent->GetWidget());
	FloatingHealthBarWidget->setHealthPercent(CharacterAttributeSet->GetHealth(), CharacterAttributeSet->GetMaxHealth());
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
				UE_LOG(LogTemp, Warning, TEXT("Enemy Ability Name : %s"), *CurrentGameplayAbilityClass.GetDefaultObject()->GetName());
			}
		}
	}

	bWerecharacterAbilitiesGiven = true;
}

// todo - adding extra end effect as it gets ignored (dodge bc dont use on enemy)
void AARPGCplusplusEnemyCharacter::AddInitialCharacterEffects()
{
	if (!IsValid(AbilitySystemComponent) || bWereCharacterEffectsGiven) {
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	UE_LOG(LogTemp, Warning, TEXT("Effects on enemy character being set"));
	for (TSubclassOf<UGameplayEffect> CurrentGameplayEffectClass : InitialGameplayEffects)
	{
		UE_LOG(LogTemp, Warning, TEXT("Effects on enemy character loop"));
		if (IsValid(CurrentGameplayEffectClass))
		{
			UE_LOG(LogTemp, Warning, TEXT("Effects on enemy character valid"));
			FGameplayEffectSpecHandle CurrentEffectHandle = AbilitySystemComponent->MakeOutgoingSpec(CurrentGameplayEffectClass, 1, EffectContextHandle);
			if (CurrentEffectHandle.IsValid())
			{
				// able to use to remove certain effects based on state
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*CurrentEffectHandle.Data.Get(), AbilitySystemComponent);
				UE_LOG(LogTemp, Warning, TEXT("Effect name: %s"), *CurrentGameplayEffectClass.GetDefaultObject()->GetName());
			}
		}
	}
	bWereCharacterEffectsGiven = true;
}

// Called every frame
// todo - delegates for this
void AARPGCplusplusEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FloatingHealthBarWidget->setHealthPercent(CharacterAttributeSet->GetHealth(), CharacterAttributeSet->GetMaxHealth());
}

UAbilitySystemComponent* AARPGCplusplusEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

