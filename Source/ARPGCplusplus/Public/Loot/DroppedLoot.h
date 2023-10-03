// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "DroppedLoot.generated.h"

UCLASS()
class ARPGCPLUSPLUS_API ADroppedLoot : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADroppedLoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Initialize(TSubclassOf<class UItem> InitializeItemClass);

	UFUNCTION(BlueprintCallable)
	virtual bool Interact(class AActor* InteractingActor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* LootStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UItem> ItemClass;

	class UItem* InventoryItem;
};
