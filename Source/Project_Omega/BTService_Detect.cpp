// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "PO_Monster_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "PO_Character.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		UE_LOG(Project_Omega, Warning, TEXT("BTService_Detect | nullptr == ControllingPawn"));
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 2000.0f;

	if (nullptr == World)
	{
		UE_LOG(Project_Omega, Warning, TEXT("BTService_Detect | nullptr == World"));
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, Center, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto const& OLR : OverlapResults)
		{
			APO_Character* POPC = Cast<APO_Character>(OLR.GetActor());

			if (POPC && POPC->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(APO_Monster_AIController::TargetKey, POPC);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, POPC->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				//DrawDebugLine(World, ControllingPawn->GetActorLocation(), POPC->GetActorLocation(), FColor::Blue, false, 0.27f);

				return;
			}
		}
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
