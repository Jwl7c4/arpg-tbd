// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCplusplus.h"
#include "ARPGCplusplusCharacter.generated.h"

class UAbilitySystemComponent;
class UCharacterAttributeSet;
class UAbilityAttributeSet;
class UGT_GameplayAbility;
class UGameplayEffect;

UCLASS(Blueprintable)
class AARPGCplusplusCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AARPGCplusplusCharacter();

	// Called every frame.
	//virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// called actions
	void ActivateAbility(const EGT_AbilityInput AbilityInput);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAbilityAttributeSet* AbilityAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Ability System")
	TArray<TSubclassOf<UGT_GameplayAbility>> InitialGameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Ability System")
	TArray<TSubclassOf<UGameplayEffect>> InitialGameplayEffects;

	uint8 bWerecharacterAbilitiesGiven : 1;

	uint8 bWereCharacterEffectsGiven : 1;

	uint8 bInputsBound : 1;

	void AddInitialCharacterAbilities();

	void AddInitialCharacterEffects();

	void SetupAbilitiesInputs();

	virtual void PossessedBy(AController* NewController);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

};

