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
#include "Engine/World.h"
#include "Abilities/GT_AttributeSet.h"
#include "Abilities/GT_GameplayAbility.h"

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
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Ability Systems
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UGT_AttributeSet>(TEXT("AttributeSet"));
	bWerecharacterAbilitiesGiven = false;
	bWereCharacterEffectsGiven = false;
	bInputsBound = false;
	SetupAbilitiesInputs();
}

void AARPGCplusplusCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AARPGCplusplusCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(AbilitySystemComponent) && IsValid(AttributeSet))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddInitialCharacterAbilities();
		AddInitialCharacterEffects();
	}
}

void AARPGCplusplusCharacter::AddInitialCharacterAbilities()
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

void AARPGCplusplusCharacter::AddInitialCharacterEffects()
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

void AARPGCplusplusCharacter::SetupAbilitiesInputs()
{
	if (!IsValid(AbilitySystemComponent) || !IsValid(InputComponent) || bInputsBound) {
		return;
	}

	AbilitySystemComponent->BindAbilityActivationToInputComponent(
	    InputComponent,
		FGameplayAbilityInputBinds("Confirm", "Cancel", "EGT_AbilityInput", static_cast<int32>(EGT_AbilityInput::Confirm), static_cast<int32>(EGT_AbilityInput::Cancel))
	);

	bInputsBound = true;
}

void AARPGCplusplusCharacter::Dodge()
{
	UE_LOG(LogTemp, Warning, TEXT("Dodge on character called"));
	//GetCharacterMovement()->MaxWalkSpeed = 2000.f;

	FVector fv = GetActorForwardVector();

	// todo jake - set 5000 as variable
	FVector x = fv * 5000;

	GetCharacterMovement()->Velocity = x;
}

void AARPGCplusplusCharacter::BasicAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("BasicAttack on character called"));
	GetCharacterMovement()->StopActiveMovement();
}

