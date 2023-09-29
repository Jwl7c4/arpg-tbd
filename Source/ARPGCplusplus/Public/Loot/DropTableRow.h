// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DropTableRow.generated.h"

USTRUCT(BlueprintType)
struct ARPGCPLUSPLUS_API FDropTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    // Reference to the master item DataTable
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Data")
    TSoftObjectPtr<UDataTable> MasterItemTable;

    // The row name in the master table to reference
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Data")
    FName ItemRowName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Data")
    float DropChance;
};