// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FindEnemyQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "AI/StealthEnemyAIController.h"

UFindEnemyQueryContext::UFindEnemyQueryContext() 
{
	


}

void UFindEnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	AStealthEnemyAIController* AIController = Cast<AStealthEnemyAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AIController && AIController->GetSeeingPawn())
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AIController->GetSeeingPawn());
}