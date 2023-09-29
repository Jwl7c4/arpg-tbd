// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"

#include "ARPGCplusplusCharacter.generated.h"

UCLASS(Blueprintable)
class AARPGCplusplusCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AARPGCplusplusCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//class UInventoryComponent* Inventory;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HandleNotifyInitialAbility();

	bool CanMove();

protected:

	uint8 bInputsBound : 1;

	void SetupAbilitiesInputs();

	// Called on the server to acknowledge possession of this Character.
	virtual void PossessedBy(AController* NewController) override;

	// Called on the client when the Character is assigned it's Player State.
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable)
	void UseItem(class UItem* Item);

	UFUNCTION(BlueprintCallable)
	void UnequipItem(class UEquippableItem* Item);

private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

};

