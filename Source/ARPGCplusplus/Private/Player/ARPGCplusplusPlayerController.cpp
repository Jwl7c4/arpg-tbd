// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/ARPGCplusplusPlayerController.h"

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Character/ARPGCplusplusCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/World.h"
#include "ARPGCplusplus.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AARPGCplusplusPlayerController::AARPGCplusplusPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AARPGCplusplusPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	bIsMenuActive = false;

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PossessedPawn = Cast<AARPGCplusplusCharacter>(GetPawn());
}

void AARPGCplusplusPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AARPGCplusplusPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AARPGCplusplusPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AARPGCplusplusPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AARPGCplusplusPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AARPGCplusplusPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AARPGCplusplusPlayerController::OnTouchReleased);

		// pause menu
		EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::HandleMenu);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::HandleInventory);

		// Ability Mappings
		EnhancedInputComponent->BindAction(DodgeInputAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::Dodge);
		EnhancedInputComponent->BindAction(PrimaryAttackInputAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::PrimaryAttack);
		EnhancedInputComponent->BindAction(AbilityOneInputAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::AbilityOne);
		EnhancedInputComponent->BindAction(AbilityTwoInputAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::AbilityTwo);
		EnhancedInputComponent->BindAction(AbilityThreeInputAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::AbilityThree);
		EnhancedInputComponent->BindAction(AbilityFourInputAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::AbilityFour);
	}
}

void AARPGCplusplusPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PossessedPawn = Cast<AARPGCplusplusCharacter>(aPawn);
	HandleCreateHUD(true);
}

void AARPGCplusplusPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	// todo - do we want to unassign 
	PossessedPawn = nullptr;
	HandleCreateHUD(false);
}

void AARPGCplusplusPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AARPGCplusplusPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AARPGCplusplusPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	if (CanPossessedPawnMove())
	{
		FVector WorldDirection = (CachedDestination - PossessedPawn->GetActorLocation()).GetSafeNormal();
		PossessedPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AARPGCplusplusPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold && CanPossessedPawnMove())
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

bool AARPGCplusplusPlayerController::CanPossessedPawnMove()
{
	return PossessedPawn != nullptr && PossessedPawn->CanMove();
}

// Triggered every frame when the input is held down
void AARPGCplusplusPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AARPGCplusplusPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AARPGCplusplusPlayerController::HandleMenu()
{
	if (PauseMenuWidget != nullptr)
	{
		WidgetInstance = CreateWidget(this, PauseMenuWidget, "PauseMenu");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Configure the Pause Menue Widget in Controller"));
	}

	if (WidgetInstance != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("HandleMenu - in widget on controller called"));
		if (bIsMenuActive) {
			UE_LOG(LogTemp, Warning, TEXT("HandleMenu - menu active on controller called"));
			WidgetInstance->RemoveFromParent();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("HandleMenu - menu inactive on controller called"));
			WidgetInstance->AddToViewport(0);
		}
		bIsMenuActive = !bIsMenuActive;
	}
}

void AARPGCplusplusPlayerController::Dodge()
{
	UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusPlayerController::Dodge - called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(EGT_AbilityInput::Dodge));
	}
}

void AARPGCplusplusPlayerController::PrimaryAttack()
{
	UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusPlayerController::PrimaryAttack - called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(EGT_AbilityInput::InitialAbility));
	}
}

void AARPGCplusplusPlayerController::AbilityOne()
{
	UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusPlayerController::AbilityOne - called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(EGT_AbilityInput::AbilityOne));
	}
}

void AARPGCplusplusPlayerController::AbilityTwo()
{
	UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusPlayerController::AbilityTwo - called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(EGT_AbilityInput::AbilityTwo));
	}
}

void AARPGCplusplusPlayerController::AbilityThree()
{
	UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusPlayerController::AbilityThree - called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(EGT_AbilityInput::AbilityThree));
	}
}

void AARPGCplusplusPlayerController::AbilityFour()
{
	UE_LOG(LogTemp, Display, TEXT("AARPGCplusplusPlayerController::AbilityFour - called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(EGT_AbilityInput::AbilityFour));
	}
}
