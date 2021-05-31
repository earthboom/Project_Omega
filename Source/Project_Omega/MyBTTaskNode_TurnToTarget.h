// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Omega.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_OMEGA_API UMyBTTaskNode_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMyBTTaskNode_TurnToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
