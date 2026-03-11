// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthEnemyCharacter.h"

// Sets default values
AStealthEnemyCharacter::AStealthEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStealthEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStealthEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStealthEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

