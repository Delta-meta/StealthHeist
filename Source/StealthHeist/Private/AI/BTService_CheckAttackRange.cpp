// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckAttackRange.h"
#include "AI/StealthEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_CheckAttackRange::UBTService_CheckAttackRange()
{
	NodeName = "Check Attack Range";
	Interval = 0.1f;
}

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AStealthEnemyAIController* AIController = Cast<AStealthEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return;

	APawn* EnemyPawn = AIController->GetPawn();
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

	if (!EnemyPawn || !TargetActor)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsInAttackRange", false);
		return;
	}

	float Distance = EnemyPawn->GetDistanceTo(TargetActor);
	bool bInRange = Distance <= AttackRange;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsInAttackRange", bInRange);
}
