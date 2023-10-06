// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/WorldInteractalbeActor.h"

// Sets default values
AWorldInteractalbeActor::AWorldInteractalbeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	SetRootComponent(InteractableStaticMesh);
}

// Called when the game starts or when spawned
void AWorldInteractalbeActor::BeginPlay()
{
	Super::BeginPlay();
}

bool AWorldInteractalbeActor::Interact(AActor* InteractingActor)
{
	OnInteract(InteractingActor);
	return true;
}

