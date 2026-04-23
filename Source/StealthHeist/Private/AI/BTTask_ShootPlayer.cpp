// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ShootPlayer.h"
#include "AI/StealthEnemyAIController.h"
#include "AI/StealthEnemyCharacter.h"
#include "Weapon/WeaponBase.h"

UBTTask_ShootPlayer::UBTTask_ShootPlayer()
{
	NodeName = "Shoot Player";
}

EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	AStealthEnemyAIController* AAIController = Cast<AStealthEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AAIController)
		return EBTNodeResult::Failed;

	AStealthEnemyCharacter* EnemyCharacter = Cast<AStealthEnemyCharacter>(AAIController->GetPawn());
	if (!EnemyCharacter)
		return EBTNodeResult::Failed;

	if (!EnemyCharacter->EquippedWeapon)
		return EBTNodeResult::Failed;

	EnemyCharacter->EquippedWeapon->Fire(EnemyCharacter);

	return EBTNodeResult::Succeeded;
}