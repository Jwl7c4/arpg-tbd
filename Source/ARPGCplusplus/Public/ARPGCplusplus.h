// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogARPGCplusplus, Log, All);

UENUM()
enum class EGT_AbilityInput : uint8
{
	None,
	Confirm,
	Cancel,
	Dodge,
	InitialAbility,
	Attack1,
	Attack2,
	Attack3,
	Attack4
};

// todo - move to own class for items?
UENUM()
enum class EItemType : uint8
{
	None,
	Consumable,
	Equippable
};

UENUM()
enum class EEquippableItemType : uint8
{
	None,
	Head,
	Shoulders,
	Chest,
	Wrist,
	Hand,
	Legs,
	Feet,
	Weapon
};

UENUM()
enum class EWeaponType : uint8
{
	None,
	Dagger,
	Sword,
	TwoHandSword,
	Axe,
	GreatAxe,
	Spear,
	Staff
};

UENUM()
enum class EClassType : uint8
{
	None,
	Knight,
	TestManny,
};