// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class STEALTHHEIST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	void Fire(AActor* FiringInstigator);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadOnly)
	float WeaponDamage = 10.f;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly)
	float FireRange = 1500.f;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly)
	FName MuzzleSocketName = FName("GunEndPoint");

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
