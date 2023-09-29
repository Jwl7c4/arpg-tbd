// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot/DroppedLoot.h"

#include "Item/Item.h"
#include "ARPGCplusplusCharacter.h"


#include "Components/SphereComponent.h" 
#include "InventoryComponent.h"

// Sets default values
ADroppedLoot::ADroppedLoot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LootStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	LootStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ADroppedLoot::BeginPlay()
{
	Super::BeginPlay();
	if (InventoryItem)
	{
		Initialize(InventoryItem->PickupMesh, ItemClass);
	}
}

void ADroppedLoot::Initialize(UStaticMesh* DroppedStaticMesh, TSubclassOf<class UItem> InitializeItemClass)
{
	InventoryItem = NewObject<UItem>(this, InitializeItemClass);
	LootStaticMesh->SetStaticMesh(DroppedStaticMesh);
}

bool ADroppedLoot::Interact(AActor* InteractingActor)
{
	// todo - if loot drop item class set but not created object like in begin play
	if (!InventoryItem)
	{
		InventoryItem = NewObject<UItem>(this, ItemClass);
	}

	// interact with player
	if (AARPGCplusplusCharacter* Player = Cast<AARPGCplusplusCharacter>(InteractingActor))
	{
		// todo - use this boolean to either remove actor or play animation
		if (Player->Inventory->AddItem(InventoryItem))
		{
			return true;
		}
	}

	return false;
}

