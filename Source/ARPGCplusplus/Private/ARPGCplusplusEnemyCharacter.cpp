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

void AARPGCplusplusEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(AbilitySystemComponent) && IsValid(AbilityAttributeSet))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddInitialCharacterAbilities();
		AddInitialCharacterEffects();
	}

	//TSubclas
	//AbilitySystemComponent->GetAttributeSet(CharacterAttributeSet.);

	TArray<FGameplayAttribute> OutAttributes;
	AbilitySystemComponent->GetAllAttributes(OutAttributes);
	for (FGameplayAttribute att : OutAttributes) {
		
		FString x = att.GetName();
		//const UAttributeSet* InternalAttributeSet = AbilitySystemComponent->GetAttributeSubobject(att.GetAttributeSetClass());
		//AbilitySystemComponent
		//float y = att.GetNumericValue(CharacterAttributeSet);
		UE_LOG(LogTemp, Warning, TEXT("Attribute name: %s. Value: %d"), *FString(x), 000);
	}
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

	//FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitialGameplayEffects, 1, EffectContextHandle);

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
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*CurrentEffectHandle.Data.Get());
				UE_LOG(LogTemp, Warning, TEXT("Effect name: %s"), *CurrentGameplayEffectClass.GetDefaultObject()->GetName());
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

