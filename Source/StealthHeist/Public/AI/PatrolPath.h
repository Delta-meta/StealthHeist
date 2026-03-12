// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "PatrolPath.generated.h"

UCLASS()
class STEALTHHEIST_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBillboardComponent* Billboard;

	UPROPERTY(EditAnywhere)
	UArrowComponent* FacingDirection;

	UPROPERTY(EditAnywhere)
	USplineComponent* Path;

	UPROPERTY(EditAnywhere)
	TArray<FVector> Locations;
};
