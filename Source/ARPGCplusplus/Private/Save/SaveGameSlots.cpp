// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SaveGameSlots.h"

USaveGameSlots::USaveGameSlots()
{
	MaxSlots = 2;
	SlotNames = {};
}

bool USaveGameSlots::DoesSlotExist(FString SlotName)
{
	for (auto Name : SlotNames)
	{
		if (Name == SlotName)
		{
			return true;
		}
	}
	return false;
}

bool USaveGameSlots::AddSlotName(FString SlotName)
{

	if (SlotNames.Num() >= MaxSlots)
	{
		return false;
	}

	for (auto Name : SlotNames)
	{
		if (Name == SlotName)
		{
			return false;
		}
	}

	SlotNames.Add(SlotName);
	return true;
}

bool USaveGameSlots::DeleteSlotName(FString SlotName)
{
	SlotNames.Remove(SlotName);

	for (auto Name : SlotNames)
	{
		if (Name == SlotName)
		{
			return false;
		}
	}
	return true;
}
