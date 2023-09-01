// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCplusplusEnemyPawn.h"

// Sets default values
AARPGCplusplusEnemyPawn::AARPGCplusplusEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AARPGCplusplusEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AARPGCplusplusEnemyPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AARPGCplusplusEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

