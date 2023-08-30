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
	Dodge
};
