// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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

	protected:
		UPROPERTY(Transient)
		class UBehaviorTreeComponent* BTComp;

		UPROPERTY(Transient)
		class UBlackboardComponent* BBComp;
};
