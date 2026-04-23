// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AStealthEnemyCharacter::AStealthEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(.0f, 600.f, .0f);

}

// Called when the game starts or when spawned
void AStealthEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, SpawnParams);
		if (EquippedWeapon) 
		{
			EquippedWeapon->AttachToComponent(
				GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				FName("WeaponSocket")
			);
		}
	}
}

// Called every frame
void AStealthEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

