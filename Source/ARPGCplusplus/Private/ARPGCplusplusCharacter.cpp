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
#include "DrawDebugHelpers.h" // delete

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
	SetupAbilitiesInputs();
}

void AARPGCplusplusCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if (PS)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);


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

	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if (PS)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);


		//AddInitialCharacterAbilities();
		AddInitialCharacterEffects();
	}
}

UAbilitySystemComponent* AARPGCplusplusCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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
				AbilitySystemComponent->GiveAbility(
					FGameplayAbilitySpec(CurrentAbility, 1, static_cast<int32>(CurrentAbility->AbilityInputId), this));
			}
		}
	}

	bWerecharacterAbilitiesGiven = true;
}

// todo - adding extra end effect as it gets ignored (duplicated extra dodge)
void AARPGCplusplusCharacter::AddInitialCharacterEffects()
{
	if (!IsValid(AbilitySystemComponent) || bWereCharacterEffectsGiven) {
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> CurrentGameplayEffectClass : InitialGameplayEffects)
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
		FGameplayAbilityInputBinds("Confirm", "Cancel", FTopLevelAssetPath("EGT_AbilityInput"), static_cast<int32>(EGT_AbilityInput::Confirm), static_cast<int32>(EGT_AbilityInput::Cancel))
	);

	bInputsBound = true;
}

void AARPGCplusplusCharacter::ActivateAbility(const EGT_AbilityInput AbilityInputId)
{

	UE_LOG(LogTemp, Warning, TEXT("ActivateAbility on character called. Ability id: %d"), AbilityInputId);

	// ability system
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityInputId));
}

bool AARPGCplusplusCharacter::CanMove()
{
	//FGameplayTagContainer* TagContainer = {};
	//AbilitySystemComponent->GetOwnedGameplayTags(*TagContainer);

	FGameplayTagContainer TargetTags;
	AbilitySystemComponent->GetOwnedGameplayTags(TargetTags);

	// get tags where cant move

	// todo jake - has any and create configed container vs adding line for each
	// todo jake - this currently stops the dodge impulse too
	//FGameplayTag dodge = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Character.State.Dodging"));
	FGameplayTag attack = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("Character.State.Attacking"));
	//if (TargetTags.HasTag(dodge) || TargetTags.HasTag(attack)) {
	if (TargetTags.HasTag(attack)) {
		return false;
	}
	return true;
}

//void AARPGCplusplusCharacter::HandleNotifyInitialAbility()
//{
//	UE_LOG(LogTemp, Warning, TEXT("HandleNotifyInitialAbility on character called"));
//
//	USkeletalMeshComponent* mesh = GetMesh();
//	// todo - change to dynamic if different models
//	FVector location = mesh->GetSocketLocation("RightHand");
//	FVector locationL = mesh->GetSocketLocation("LeftHand");
//
//	const TArray<AActor*> actorIgnore{ this };
//
//	TArray<TEnumAsByte<EObjectTypeQuery>> collisionQuery;
//	collisionQuery.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
//
//	TArray<AActor*> outActors;
//
//	bool bHitSomething = UKismetSystemLibrary::SphereOverlapActors
//	(
//		GetWorld(),
//		location,
//		50.0f,
//		collisionQuery,
//		AARPGCplusplusEnemyCharacter::StaticClass(),
//		actorIgnore,
//		outActors
//	);
//	// todo jake - remove after debug or flag passed in
//	DrawDebugSphere(GetWorld(), location, 50.f, 5, FColor::Green, false, 10.f, 2, 3.f);
//
//	if (bHitSomething) {
//		UE_LOG(LogTemp, Warning, TEXT("HandleNotifyInitialAbility - WE HAVE A HIT"));
//
//		//AbilitySystemComponent->tagcontainter
//		for (auto actors : outActors)
//		{
//			ACharacter* actor = Cast<ACharacter>(actors);		
//
//			const FGameplayTag MyTag = FGameplayTag::RequestGameplayTag(FName("Event.InitialAbility.Hit"));
//			FGameplayEventData x;
//			x.Instigator = this;
//			x.Target = actor;
//			x.EventMagnitude = 1.f;
//
//			UGameplayAbility::execSendGameplayEvent();
//			
//			UGameplayAbility::SendGameplayEvent(MyTag, x);
//		}
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("HandleNotifyInitialAbility - WHIFFFFFF"));
//	}
//}
