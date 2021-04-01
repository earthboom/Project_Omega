// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Omega.h"
#include "Animation/AnimInstance.h"
#include "PO_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_OMEGA_API UPO_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPO_AnimInstance();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
};
