// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot/LootComponent.h"

#include "Item/ItemStruct.h"
#include "Loot/DropTableRow.h"

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

	if (!LootDropTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULootComponent::DroppedItems - Drop Loot Table not assigned"));
		return TArray<UItem*>();
	}

	float TotalDropChance = 0.0f;
	TArray<FName> Names = LootDropTable->GetRowNames(); // store all names as we loop twice
	for (const auto& RowName : Names)
	{
		FDropTableRow* CurrentRowForCalculation = LootDropTable->FindRow<FDropTableRow>(RowName, "Looking up item calculating drop chance");//Item.Value;

		if (CurrentRowForCalculation)
		{
			TotalDropChance += CurrentRowForCalculation->DropChance;
		}
	}

	float RandomValue = FMath::FRandRange(0.0f, TotalDropChance);

	FDropTableRow* ChosenItemData = nullptr;
	for (const FName& ItemName : Names)
	{
		FDropTableRow* CurrentRowCheckIfChosenDrop = LootDropTable->FindRow<FDropTableRow>(ItemName, "Looking up item name in loop");

		if (CurrentRowCheckIfChosenDrop)
		{
			if (RandomValue <= CurrentRowCheckIfChosenDrop->DropChance)
			{
				ChosenItemData = CurrentRowCheckIfChosenDrop;
				break;
			}
			else
			{
				RandomValue -= CurrentRowCheckIfChosenDrop->DropChance;
			}
		}
	}

	// todo - only 1 item ever into array
	if (ChosenItemData)
	{
		// get item details from master item table
		FItemMasterTableRow* MasterItemData = ChosenItemData->MasterItemTable->FindRow<FItemMasterTableRow>(ChosenItemData->ItemRowName, "Looking up master item name");

		// create item
		UItem* DroppedItem = NewObject<UItem>(this, MasterItemData->ItemDefinition);

		// add to array
		TArray<UItem*> DroppedItems;
		DroppedItems.Add(DroppedItem);

		// return array
		return DroppedItems;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ULootComponent::DroppedItems - No drop selected"));
		return TArray<UItem*>();
	}
}

