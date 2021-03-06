// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Omega.h"
#include "GameFramework/Character.h"
#include "BTTask_Attack.h"
#include "PO_Character.generated.h"

UCLASS()
class PROJECT_OMEGA_API APO_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APO_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Char_Attack")
		void Attack();
	
	UFUNCTION(BlueprintCallable, Category = "Char_Attack")
		void AttackEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsAttacking;

	UBTTask_Attack* m_pBT_Attack;
//private:
//	UPROPERTY(VisibleIntanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
};
