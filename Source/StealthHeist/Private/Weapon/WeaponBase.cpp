// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	RootComponent = WeaponMesh;

}

void AWeaponBase::Fire(AActor* FiringInstigator)
{
	if (!WeaponMesh) return;

	FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	FVector ForwardVector = WeaponMesh->GetSocketRotation(MuzzleSocketName).Vector();
	FVector TraceEnd = MuzzleLocation + (ForwardVector * FireRange);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(FiringInstigator);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLocation, TraceEnd, ECC_Visibility, Params);

	if (bHit && HitResult.GetActor()) 
	{
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), WeaponDamage, nullptr, this, UDamageType::StaticClass());

		// Debug line to visualize shots - remove later
		DrawDebugLine(GetWorld(), MuzzleLocation, HitResult.Location, FColor::Red, false, 1.f);
	}

	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

