// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot/LootComponent.h"

// Sets default values for this component's properties
ULootComponent::ULootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

TArray<class UItem*> ULootComponent::DroppedItems()
{
	// get items
	//NewObject<UBaseMovementAdjustmentComponent>(this, AdjMovementComponent);
	
	
	// add to array
	
	// return array
	return TArray<class UItem*>();
}


// Called when the game starts
void ULootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

