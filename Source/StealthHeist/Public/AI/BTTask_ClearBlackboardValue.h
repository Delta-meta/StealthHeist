// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHHEIST_API UBTTask_ClearBlackboardValue : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTask_ClearBlackboardValue();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory) override;
};
