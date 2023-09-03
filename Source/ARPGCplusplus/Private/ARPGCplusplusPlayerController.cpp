// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARPGCplusplusPlayerController.h"

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "ARPGCplusplusCharacter.h"
#include "Engine/World.h"
#include "ARPGCplusplus.h"
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

		// need to figure out how to set this binding and call gameplay ability
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::Dodge);
		EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Started, this, &AARPGCplusplusPlayerController::BasicAttack);
	}
}

void AARPGCplusplusPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PossessedPawn = Cast<AARPGCplusplusCharacter>(aPawn);
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
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AARPGCplusplusPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
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
	UE_LOG(LogTemp, Warning, TEXT("Dodge on controller called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->ActivateAbility(EGT_AbilityInput::Dodge);
	}
}

void AARPGCplusplusPlayerController::BasicAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("InitialAbility on controller called"));
	if (PossessedPawn != nullptr)
	{
		PossessedPawn->ActivateAbility(EGT_AbilityInput::InitialAbility);
	}
}
