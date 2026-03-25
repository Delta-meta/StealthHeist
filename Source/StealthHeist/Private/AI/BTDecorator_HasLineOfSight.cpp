// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_HasLineOfSight.h"
#include "AI/StealthEnemyCharacter.h"
#include "AI/StealthEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

UBTDecorator_HasLineOfSight::UBTDecorator_HasLineOfSight()
{
	NodeName = "Has Line Of Sight";
	bCreateNodeInstance = true;
}

bool UBTDecorator_HasLineOfSight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Check if AIController or Blackboard exist in the AI Character
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AStealthEnemyAIController* EnemyController = Cast<AStealthEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyController || !Blackboard)
		return false;

	// Check if the pawn of the AI Controller is an instance of AI Character
	AStealthEnemyCharacter* EnemyCharacter = Cast<AStealthEnemyCharacter>(EnemyController->GetPawn());
	if (!EnemyCharacter)
		return false;

	// Get main character detected, push forward for the Engage sequence
	if (Blackboard->GetValueAsBool("HasLineOfSight"))
		return true;
	return false;
}