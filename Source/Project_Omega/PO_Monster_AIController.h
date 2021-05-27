// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Omega.h"
#include "AIController.h"
#include "PO_Monster_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_OMEGA_API APO_Monster_AIController : public AAIController
{
	GENERATED_BODY()

public:
	APO_Monster_AIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	void OnRepeatTimer();

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
};
