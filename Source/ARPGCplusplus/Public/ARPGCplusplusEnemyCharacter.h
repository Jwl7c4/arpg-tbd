// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"

#include "ARPGCplusplusEnemyCharacter.generated.h"

UCLASS()
class ARPGCPLUSPLUS_API AARPGCplusplusEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGCplusplusEnemyCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GrantedXp;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HealthBarWidgetComponent;

	// todo - how to get this being set??
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	class UFloatingHealthBarWidget* FloatingHealthBarWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Loot Drops")
	class ULootComponent* LootDropComponent;

	// Called when the game starts or when spawned
	void BeginPlay();

	// Called every frame
	void Tick(float DeltaTime) override;

	void OnDeath() override;

	UPROPERTY(BlueprintReadOnly)
	int Level;

};
