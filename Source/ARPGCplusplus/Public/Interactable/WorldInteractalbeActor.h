// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "WorldInteractalbeActor.generated.h"

UCLASS()
class ARPGCPLUSPLUS_API AWorldInteractalbeActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldInteractalbeActor();

	UFUNCTION(BlueprintCallable)
	virtual bool Interact(class AActor* InteractingActor) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* InteractableStaticMesh;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract(class AActor* InteractingActor);

};
