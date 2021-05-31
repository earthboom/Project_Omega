// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "PO_Monster_AIController.h"
#include "PO_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		UE_LOG(Project_Omega, Warning, TEXT("BTDecorator_IsInAttackRange | nullptr == ControllingPawn | false"));
		return false;
	}

	auto Target = Cast<APO_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(APO_Monster_AIController::TargetKey));
	if (nullptr == Target)
	{
		UE_LOG(Project_Omega, Warning, TEXT("BTDecorator_IsInAttackRange | nullptr == Target | false"));
		return false;
	}

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}
