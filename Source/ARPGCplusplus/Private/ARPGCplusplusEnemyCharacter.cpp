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

// Called every frame
// todo - delegates for this
void AARPGCplusplusEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FloatingHealthBarWidget->setHealthPercent(CharacterAttributeSet->GetHealth(), CharacterAttributeSet->GetMaxHealth());
}

