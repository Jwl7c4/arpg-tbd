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

	//PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	//PlatformMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	//PlatformMesh->SetStaticMesh(SphereMeshAsset.Object);

	//LootRadiusSphere = CreateDefaultSubobject<USphereComponent>(TEXT("LootSphereRadius"));
	//LootRadiusSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ADroppedLoot::BeginPlay()
{
	Super::BeginPlay();
	InventoryItem = NewObject<UItem>(this, ItemClass);
	LootStaticMesh->SetStaticMesh(InventoryItem->PickupMesh);
}

bool ADroppedLoot::Interact(AActor* InteractingActor)
{
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

