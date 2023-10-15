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
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> PotionGameplayEffectClass;

	FItemData CreateItemSaveObject() override;

	void ConstructItem(AARPGCplusplusCharacter* OutCharacter, FItemData ItemData) override;

	virtual void Use(class AARPGCplusplusCharacter* Character) override;
};
