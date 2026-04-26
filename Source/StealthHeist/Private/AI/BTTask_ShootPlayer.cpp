// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ShootPlayer.h"
#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "Weapon/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_ShootPlayer::UBTTask_ShootPlayer()
{
	NodeName = "Shoot Player";
}

EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	AStealthEnemyAIController* AIController = Cast<AStealthEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return EBTNodeResult::Failed;

	AStealthEnemyCharacter* EnemyCharacter = Cast<AStealthEnemyCharacter>(AIController->GetPawn());
	if (!EnemyCharacter)
		return EBTNodeResult::Failed;

	if (!EnemyCharacter->EquippedWeapon)
		return EBTNodeResult::Failed;

	// Rotate to face target before shooting
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if (TargetActor)
	{
		// After firing
		AIController->SetFocus(TargetActor);
		EnemyCharacter->bUseControllerRotationYaw = true;
		EnemyCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	
	EnemyCharacter->EquippedWeapon->Fire(EnemyCharacter);

	return EBTNodeResult::Succeeded;
}