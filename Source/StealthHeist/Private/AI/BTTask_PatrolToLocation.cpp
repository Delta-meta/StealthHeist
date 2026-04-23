// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_PatrolToLocation.h"
#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "AI/PatrolPath.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_PatrolToLocation::UBTTask_PatrolToLocation() {
	bCreateNodeInstance = true;
	NodeName = "PatrolToLocation";
}

EBTNodeResult::Type UBTTask_PatrolToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	// Get and cast AIController
	AStealthEnemyAIController* AIController = Cast<AStealthEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return EBTNodeResult::Failed;

	// Get the character the controller is possessing
	AStealthEnemyCharacter* EnemyCharacter = Cast<AStealthEnemyCharacter>(AIController->GetPawn());
	if (!EnemyCharacter)
		return EBTNodeResult::Failed;

	// Check if PatrolPath refrence is valid and locations are populated
	APatrolPath* PatrolPath = Cast<APatrolPath>(EnemyCharacter->PatrolPath);
	if (!PatrolPath || PatrolPath->Locations.Num() < 1)
		return EBTNodeResult::Succeeded;
	
	AIController->ClearFocus(EAIFocusPriority::Gameplay);
	EnemyCharacter->bUseControllerRotationYaw = false;
	EnemyCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	

	// Set the MoveToLocation Blackboard key to be the spline point
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>("MoveToLocation", PatrolPath->Locations[Index]);
	if (Index < PatrolPath->Locations.Num() - 1)
	{
		Index++;
	}
	else
	{
		Index = 0; 
	}

	return EBTNodeResult::Succeeded;
}