// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "StealthHeist/StealthHeistCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

AStealthEnemyAIController::AStealthEnemyAIController()
{
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComp");
    
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
    SightConfig->SightRadius = AISightRadius;
    SightConfig->LoseSightRadius = AILoseSightRadius;
    SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
    SightConfig->SetMaxAge(AISightAge);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
    AIPerceptionComponent->ConfigureSense(*SightConfig);
    AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
    AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AStealthEnemyAIController::OnPawnDetected);
    SetPerceptionComponent(*AIPerceptionComponent);
}

void AStealthEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AStealthEnemyCharacter* EnemyCharacter = Cast<AStealthEnemyCharacter>(InPawn);
    if (EnemyCharacter && EnemyCharacter->TreeAsset)
    {
        BlackboardComponent->InitializeBlackboard(*EnemyCharacter->TreeAsset->BlackboardAsset);
        BehaviorTreeComponent->StartTree(*EnemyCharacter->TreeAsset);
    }
}

FRotator AStealthEnemyAIController::GetControlRotation() const
{
    if (!GetPawn()) return FRotator::ZeroRotator;
    return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);

}

APawn* AStealthEnemyAIController::GetSeeingPawn() const
{
    UObject* Target = BlackboardComponent->GetValueAsObject("TargetActor");
    return Cast<APawn>(Target);
}

void AStealthEnemyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
    for (AActor* Actor : DetectedPawns)
    {
        if (!Actor->IsA<AStealthHeistCharacter>()) continue;

        FActorPerceptionBlueprintInfo Info;
        AIPerceptionComponent->GetActorsPerception(Actor, Info);

        for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
        {
            if (Stimulus.Type != UAISense::GetSenseID<UAISense_Sight>()) continue;

            if (Stimulus.WasSuccessfullySensed())
            {
                // Player spotted
                BlackboardComponent->SetValueAsBool("HasLineOfSight", true);
                BlackboardComponent->SetValueAsObject("TargetActor", Actor);
                BlackboardComponent->SetValueAsVector("LastKnown", Actor->GetActorLocation());
            }
            
            else
            {
                // Player Lost
                BlackboardComponent->SetValueAsBool("HasLineOfSight", false);
                BlackboardComponent->SetValueAsObject("TargetActor", nullptr);
                // LastKnownLocation intentionally kept for Investigate state
            }
        }
    }
}