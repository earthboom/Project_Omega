// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "PO_Monster_AIController.h"
#include "PO_Character.h"

UBTTask_Attack::UBTTask_Attack()
	: IsAttacking(false)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto PO_Char = Cast<APO_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == PO_Char)
	{
		UE_LOG(Project_Omega, Warning, TEXT("BTTask_Attack | nullptr == APO_Character | Failed"));
		return EBTNodeResult::Failed;
	}

	PO_Char->Attack();
	IsAttacking = true;
	PO_Char->OnAttackEnd.AddLambda([this]()->void 
		{
			IsAttacking = false; 
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecond)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecond);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
