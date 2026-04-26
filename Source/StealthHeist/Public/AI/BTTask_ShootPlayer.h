// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShootPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHHEIST_API UBTTask_ShootPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTask_ShootPlayer();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
