// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ARPGCplusplusEnemyCharacter.generated.h"

UCLASS()
class ARPGCPLUSPLUS_API AARPGCplusplusEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGCplusplusEnemyCharacter();

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

	void AddInitialCharacterAbilities();

	void AddInitialCharacterEffects();

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	//TSubclassOf<class UUserWidget> HealthBarWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HealthBarWidgetComponent;

	// todo jake - how to get this being set??
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	class UFloatingHealthBarWidget* FloatingHealthBarWidget;

	// Called when the game starts or when spawned
	void BeginPlay();

	// Called every frame
	void Tick(float DeltaTime) override;


	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};
