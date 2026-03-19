// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "StealthEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHHEIST_API AStealthEnemyAIController : public AAIController
{
	GENERATED_BODY()
	public:
		AStealthEnemyAIController();		
		virtual void OnPossess(APawn* InPawn) override;
		virtual FRotator GetControlRotation() const override;

		UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

		virtual void Tick(float DeltaSeconds) override;
		virtual void BeginPlay() override;

	protected:
		UPROPERTY(Transient)
		class UBehaviorTreeComponent* BTComp;

		UPROPERTY(Transient)
		class UBlackboardComponent* BBComp;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AISightRadius = 500.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AISightAge = 5.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AILoseSightRadius = AISightRadius + 50.f;

		UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		float AIFieldOfView = 90.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Sight* SightConfig;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DistanceToPlayer = 0.0f;
};
