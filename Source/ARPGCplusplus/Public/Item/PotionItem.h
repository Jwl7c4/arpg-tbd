// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class ARPGCPLUSPLUS_API UPotionItem : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta = (ClampMin = 0.0))
	float HealthToAdd;
	
protected:

	virtual void Use(class AARPGCplusplusCharacter* Character) override;
};
