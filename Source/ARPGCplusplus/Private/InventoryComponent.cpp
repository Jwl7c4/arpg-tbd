// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Item/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 20;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

// todo - all items stack to max stack then create new. need to have objects that only have 1 stack
bool UInventoryComponent::AddItem(UItem* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddItem - max capacity. can't add more items"));
		return false;
	}

	Item->OwnerInventory = this;
	Item->World = GetWorld();

	bool bItemFound = false;
	for (auto& CurrentItem : Items)
	{
		if (Item->ItemDisplayName.ToString() == CurrentItem->ItemDisplayName.ToString())
		{
			if (CurrentItem->CurrentStackCount < CurrentItem->MaxStackCount)
			{
				// add stack if less than max. else ignore and will add new stack in inventory
				CurrentItem->CurrentStackCount += 1;
				bItemFound = true;
				break;
			}
		}
	}

	if (!bItemFound) {
		Item->CurrentStackCount = 1;
		Items.Add(Item);
	}

	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(UItem* Item)
{
	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::RemoveItem - remove item"));
	if (Item)
	{
		bool bItemFound = false;
		for (auto& CurrentItem : Items)
		{
			if (Item->ItemDisplayName.ToString() == CurrentItem->ItemDisplayName.ToString())
			{
				if (CurrentItem->CurrentStackCount > 1)
				{
					// add stack if less than max. else ignore and will add new stack in inventory
					CurrentItem->CurrentStackCount -= 1;
					bItemFound = true;
					break;
				}
			}

		}

		if (!bItemFound) {
			Item->OwnerInventory = nullptr;
			Item->World = nullptr;
			Items.RemoveSingle(Item);
		}

		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

