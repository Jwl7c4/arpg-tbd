// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGCplusplus.h"

#include "InventoryComponent.generated.h"

// Blueprints will bind to this to update UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquippedItemsUpdated);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARPGCPLUSPLUS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	bool AddItem(class UItem* Item);

	bool RemoveItem(class UItem* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> Items;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnEquippedItemsUpdated OnEquippedUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TMap<EEquippableItemType, class UEquippableItem*> EquippedItems;

	bool EquipItem(class UEquippableItem* ToEquip, class UEquippableItem* CurrentSlot);

	UFUNCTION(BlueprintCallable)
	bool UnEquipItem(class UEquippableItem* EquippableItem);
};
