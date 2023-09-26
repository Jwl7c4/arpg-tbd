// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARPGCplusplusCharacter.h"

#include "AbilitySystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameplayTagsManager.h"
#include "Engine/World.h"
#include "Player/PlayerStateBase.h"
#include "ARPGCplusplusEnemyCharacter.h"
#include "AbilityAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "Components/WidgetComponent.h"
#include "Abilities/CharacterAttributeSet.h"
#include "Abilities/GT_GameplayAbility.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Item/Item.h"
#include "Item/EquippableItem.h"
#include "InventoryComponent.h"

AARPGCplusplusCharacter::AARPGCplusplusCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Inventory
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	// Non Ability attributes
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Ability Systems
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AbilityAttributeSet = CreateDefaultSubobject<UAbilityAttributeSet>(TEXT("AbilityAttributeSet"));
	bWerecharacterAbilitiesGiven = false;
	bWereCharacterEffectsGiven = false;
	bInputsBound = false;
}

void AARPGCplusplusCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerStateBase* PlayerStateBase = GetPlayerState<APlayerStateBase>())
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PlayerStateBase->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PlayerStateBase->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerStateBase, this);

		CharacterAttributeSet = PlayerStateBase->CharacterAttributeSet;

		AddInitialCharacterAbilities();
		AddInitialCharacterEffects();
	}
}

void AARPGCplusplusCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("OnRep_PlayerState - ASC null"));
	}


	if (APlayerStateBase* PlayerStateBase = GetPlayerState<APlayerStateBase>())
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = PlayerStateBase->GetAbilitySystemComponent();

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PlayerStateBase->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerStateBase, this);

		CharacterAttributeSet = PlayerStateBase->CharacterAttributeSet;

		SetupAbilitiesInputs();
	}
}

void AARPGCplusplusCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); // blue print callable
	}
}

void AARPGCplusplusCharacter::UnequipItem(UEquippableItem* Item)
{
	if (Item)
	{
		Item->UnequipItem(this);
		Item->OnUnequipItem(this);
	}
}

void AARPGCplusplusCharacter::SetupAbilitiesInputs()
{
	if (!IsValid(AbilitySystemComponent) || !IsValid(InputComponent) || bInputsBound) {
		return;
	}

	AbilitySystemComponent->BindAbilityActivationToInputComponent(
		InputComponent,
		FGameplayAbilityInputBinds("Confirm", "Cancel", FTopLevelAssetPath("EGT_AbilityInput"), static_cast<int32>(EGT_AbilityInput::Confirm), static_cast<int32>(EGT_AbilityInput::Cancel))
	);

	bInputsBound = true;
}

bool AARPGCplusplusCharacter::CanMove()
{

	FGameplayTagContainer TargetTags;
	AbilitySystemComponent->GetOwnedGameplayTags(TargetTags);

	// get tags where cant move

	// todo - has any and create configed container vs adding line for each
	// todo - this currently stops the dodge impulse too
	//FGameplayTag dodge = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Character.State.Dodging"));
	FGameplayTag attack = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Character.State.Attacking"));
	//if (TargetTags.HasTag(dodge) || TargetTags.HasTag(attack)) {
	if (TargetTags.HasTag(attack)) {
		return false;
	}
	return true;
}
