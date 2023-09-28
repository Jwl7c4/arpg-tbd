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
	// Load a row from the DataTable
	//FItemMasterTableRow* ItemDataRow = LootDropTable->FindRow<FItemMasterTableRow>(RowName, ContextString);

	//if (ItemDataRow)
	//{
	//	// Access the Blueprint class reference
	//	TSubclassOf<UItem> ItemBlueprintClass = ItemDataRow->ItemBlueprintClass;

	//	if (ItemBlueprintClass)
	//	{
	//		// Create an instance of the Blueprint class
	//		UItem* ItemInstance = NewObject<UItem>(this, ItemBlueprintClass);

	//		if (ItemInstance)
	//		{
	//			// You can now work with the Blueprint-derived item instance as needed
	//		}
	//	}
	//}


	TArray<FName> ItemNames; // Store the names of all items

	// rows to loop over
	TArray<FName> RowNames = LootDropTable->GetRowNames();

	float TotalDropChance = 0.0f;
	for (const auto& RowName : RowNames)
	{
		FDropTableRow* ItemData = LootDropTable->FindRow<FDropTableRow>(RowName, "Looking up item calculating drop chance");//Item.Value;

		if (ItemData)
		{
			TotalDropChance += ItemData->DropChance;
			ItemNames.Add(RowName);
		}
	}

	float RandomValue = FMath::FRandRange(0.0f, TotalDropChance);

	FDropTableRow* ChosenItemData = nullptr;
	for (const FName& ItemName : ItemNames)
	{
		FDropTableRow* ItemData = LootDropTable->FindRow<FDropTableRow>(ItemName, "Looking up item name in loop");

		if (ItemData)
		{
			if (RandomValue <= ItemData->DropChance)
			{
				ChosenItemData = ItemData;
				break;
			}
			else
			{
				RandomValue -= ItemData->DropChance;
			}
		}
	}

	if (ChosenItemData)
	{
		FItemMasterTableRow* ItemData = LootDropTable->FindRow<FItemMasterTableRow>(ChosenItemData->ItemRowName, "Looking up master item name");

		// get items
		UItem* DroppedItem = NewObject<UItem>(this, ItemData->ItemDefinition);

		// add to array
		TArray<UItem*> DroppedItems = { DroppedItems };

		// return array
		return DroppedItems;
	} else
	{
		return TArray<UItem*>();
	}
}


// Called when the game starts
void ULootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

