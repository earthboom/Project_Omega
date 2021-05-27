// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "PO_Monster_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;

	ConstructorHelpers::FObjectFinder<UBlueprint> BP_Load(TEXT("Blueprint'/Game/Blueprint/Character/BP_Omega_Character.BP_Omega_Character'"));
	if (BP_Load.Object != nullptr)
		PO_Player = (UClass*)BP_Load.Object->GeneratedClass;
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
	float DetectRadius = 600.0f;

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
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(APO_Monster_AIController::TargetKey, nullptr);
		}
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
