// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ARPGCplusplusEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Abilities/AbilityAttributeSet.h"
#include "Abilities/CharacterAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "AttributeSet.h"
#include "Abilities/GT_GameplayAbility.h"
#include <Widgets/FloatingHealthBarWidget.h>
#include <Kismet/GameplayStatics.h>
#include "Item/InventoryComponent.h"
#include "Item/Item.h"
#include "Loot/LootComponent.h"

// Sets default values
AARPGCplusplusEnemyCharacter::AARPGCplusplusEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	RootComponent = GetCapsuleComponent();

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	HealthBarWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Inventory
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 5;

	LootDropComponent = CreateDefaultSubobject<ULootComponent>(TEXT("LootDropComponent"));

	// Non Ability attributes
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Ability Systems
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AbilityAttributeSet = CreateDefaultSubobject<UAbilityAttributeSet>(TEXT("AbilityAttributeSet"));
	bWerecharacterAbilitiesGiven = false;
	bWereCharacterEffectsGiven = false;

	// level and xp granted
	Level = 1;
	GrantedXp = 5000.f;
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

void AARPGCplusplusEnemyCharacter::OnDeath()
{
	if (LootDropComponent) {
		TArray<UItem*> ItemsToDrop = LootDropComponent->DroppedItems();

		if (ItemsToDrop.Num() > 0)
		{
			for (auto& Item : ItemsToDrop)
			{
				Inventory->AddItem(Item);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AARPGCplusplusEnemyCharacter::OnDeath - LootComponent not set"));
	}
	
	Super::OnDeath();
}

