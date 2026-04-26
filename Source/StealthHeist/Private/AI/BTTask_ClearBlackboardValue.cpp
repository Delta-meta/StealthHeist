// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = "Clear LatKnownLocation";
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	OwnerComp.GetBlackboardComponent()->ClearValue("LastKnownLocation");
	OwnerComp.GetBlackboardComponent()->ClearValue("TargetActor");
	return EBTNodeResult::Succeeded;
}
