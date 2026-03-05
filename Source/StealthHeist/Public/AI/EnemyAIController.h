// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHHEIST_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(transient)
	class UBehviorTreeComponenet* BTC;

	UPROPERTY(transient)
	class UBlackboardComponent* BBC;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BluepprintReadWrite, Category = "AI", meta = (AllowPrivateAcess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BluepprintReadOnly, Category = "AI", meta = (AllowPrivateAcess = true))
	TObjectPtr<UBehviorTreeComponenet> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BluepprintReadOnly, Category = "AI", meta = (AllowPrivateAcess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
};
