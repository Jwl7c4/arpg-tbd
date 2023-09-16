// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCplusplus.h"
#include "AbilitySystemInterface.h"
#include "ARPGCplusplusCharacter.generated.h"

UCLASS(Blueprintable)
class AARPGCplusplusCharacter : public ACharacter, public IAbilitySystemInterface
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

	UPROPERTY(EditAnywhere, BlueprintREadOnly)
	class UInventoryComponent* Inventory;

	// called actions
	void ActivateAbility(const EGT_AbilityInput AbilityInput);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HandleNotifyInitialAbility();

	bool CanMove();

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAbilityAttributeSet* AbilityAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Ability System")
	TArray<TSubclassOf<class UGT_GameplayAbility>> InitialGameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Ability System")
	TArray<TSubclassOf<class UGameplayEffect>> InitialGameplayEffects;

	uint8 bWerecharacterAbilitiesGiven : 1;

	uint8 bWereCharacterEffectsGiven : 1;

	uint8 bInputsBound : 1;

	void AddInitialCharacterAbilities();

	void AddInitialCharacterEffects();

	void SetupAbilitiesInputs();

	// Called on the server to acknowledge possession of this Character.
	virtual void PossessedBy(AController* NewController) override;

	// Called on the client when the Character is assigned it's Player State.
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable)
	void UseItem(class UItem* Item);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

};

