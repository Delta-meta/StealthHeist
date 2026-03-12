// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_PatrolToLocation.h"
#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "AI/PatrolPath.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

UBTTask_PatrolToLocation::UBTTask_PatrolToLocation() {
	bCreateNodeInstance = true;
	NodeName = "PatrolToLocation";
}

EBTNodeResult::Type UBTTask_PatrolToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	// Get and cast AIController
	AStealthEnemyAIController* MyController = Cast<AStealthEnemyAIController>(OwnerComp.GetAIOwner());
	if (!MyController)
		return EBTNodeResult::Failed;

	// Get the character the controller is possessing
	AStealthEnemyCharacter* MyCharacter = Cast<AStealthEnemyCharacter>(MyController->GetPawn());
	if (!MyCharacter)
		return EBTNodeResult::Failed;

	// Check if PatrolPath refrence is valid and locations are populated
	APatrolPath* PathRef = Cast<APatrolPath>(MyCharacter->PatrolPath);
	if (!PathRef || PathRef->Locations.Num() < 1)
		return EBTNodeResult::Succeeded;
	
	// Set Blackbaord MoveToLocation key
	MyBlackboard->SetValue<UBlackboardKeyType_Vector>("MoveToLoaction", PathRef->Locations[Index]);

	// Set the MoveToLocation Blackboard key to be the spline point
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>("MoveToLocation", PathRef->Locations[Index]);
	if (Index < PathRef->Locations.Num() - 1)
	{
		Index++;
	}
	else
	{
		Index = 0; 
	}

	return EBTNodeResult::Succeeded;
}