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
