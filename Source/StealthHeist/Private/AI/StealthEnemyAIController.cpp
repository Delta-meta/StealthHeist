// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

AStealthEnemyAIController::AStealthEnemyAIController()
{
    BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
    BBComp = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
    PrimaryActorTick.bCanEverTick = true;

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
    SightConfig->SightRadius = AISightRadius;
    SightConfig->LoseSightRadius = AILoseSightRadius;
    SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
    SightConfig->SetMaxAge(AISightAge);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception"));
    GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
    GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AStealthEnemyAIController::OnPawnDetected);
    GetPerceptionComponent()->ConfigureSense(*SightConfig);
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

void AStealthEnemyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
    for (size_t i = 0; i < DetectedPawns.Num();i++)
        if (DetectedPawns[i] == GetWorld()->GetFirstPlayerController()->GetPawn()) 
        {
            DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
            BBComp->SetValue<UBlackboardKeyType_Bool>("HasLineOfSight", true);
            BBComp->SetValue<UBlackboardKeyType_Object>("TargetActor", DetectedPawns[i]);
        }
}

void AStealthEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();
}

FRotator AStealthEnemyAIController::GetControlRotation() const
{
    if (GetPawn() == nullptr)
        return FRotator(.0f, .0f, .0f);
    else
        return FRotator(.0f, GetPawn()->GetActorRotation().Yaw, .0f);

}

void AStealthEnemyAIController::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    if (DistanceToPlayer > AISightRadius)
    {
        BBComp->SetValue<UBlackboardKeyType_Bool>("HasLineOfSight", false);
        BBComp->ClearValue("TargetActor");
    }
}
