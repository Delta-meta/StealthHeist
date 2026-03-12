// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AStealthEnemyAIController::AStealthEnemyAIController()
{
    BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
    BBComp = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
}

void AStealthEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AStealthEnemyCharacter* StealthEnemyCharacter = Cast<AStealthEnemyCharacter>(InPawn);
    if (StealthEnemyCharacter && StealthEnemyCharacter->TreeAsset)
    {
        BBComp->InitializeBlackboard(*StealthEnemyCharacter->TreeAsset->BlackboardAsset);
        BTComp->StartTree(*StealthEnemyCharacter->TreeAsset);
    }
}