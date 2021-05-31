// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_TurnToTarget.h"
#include "PO_Monster_AIController.h"
#include "PO_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTaskNode_TurnToTarget::UMyBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UMyBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto PO_Char = Cast<APO_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == PO_Char)
	{
		UE_LOG(Project_Omega, Warning, TEXT("MyBTTaskNode | nullptr == PO_Char | Failed"));
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<APO_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(APO_Monster_AIController::TargetKey));
	if (nullptr == Target)
	{
		UE_LOG(Project_Omega, Warning, TEXT("MyBTTaskNode | nullptr == Target | Failed"));
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - PO_Char->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	PO_Char->SetActorRotation(FMath::RInterpTo(PO_Char->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
