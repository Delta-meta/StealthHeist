// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Weapon/WeaponBase.h"
#include "StealthEnemyCharacter.generated.h"


UCLASS()
class STEALTHHEIST_API AStealthEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStealthEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UBehaviorTree* TreeAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APatrolPath* PatrolPath = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AWeaponBase* EquippedWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
