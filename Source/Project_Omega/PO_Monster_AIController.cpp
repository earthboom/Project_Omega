// Fill out your copyright notice in the Description page of Project Settings.


#include "PO_Monster_AIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName APO_Monster_AIController::HomePosKey(TEXT("HomePos"));
const FName APO_Monster_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName APO_Monster_AIController::TargetKey(TEXT("Target"));

APO_Monster_AIController::APO_Monster_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Blueprint/Character/Monster/BB_Monster.BB_Monster"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Blueprint/Character/Monster/BT_Monster.BT_Monster"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;

	RepeatInterval = 3.0f;
}

void APO_Monster_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &APO_Monster_AIController::OnRepeatTimer, RepeatInterval, true);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(Project_Omega, Warning, TEXT("PO_Monster_AIController | AIController couldn't run behavior tree!"))
		}
	}
}

void APO_Monster_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void APO_Monster_AIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	if (nullptr != CurrentPawn)
	{
		UE_LOG(Project_Omega, Warning, TEXT("PO_Monster_AIController | CurrentPawn != nullptr"));
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
		return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		UE_LOG(Project_Omega, Warning, TEXT("PO_Monster_AIController | Next Location : %s"), *NextLocation.Location.ToString());
	}
}
