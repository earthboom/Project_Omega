// Fill out your copyright notice in the Description page of Project Settings.


#include "PO_Character.h"

// Sets default values
APO_Character::APO_Character()
	: m_pBT_Attack(nullptr)
	, IsAttacking(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APO_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APO_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APO_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APO_Character::Attack()
{
	UE_LOG(Project_Omega, Warning, TEXT("PO_Character | Attack() "));
	IsAttacking = true;
}

void APO_Character::AttackEnd()
{
	UE_LOG(Project_Omega, Warning, TEXT("PO_Character | AttackEnd() "));
	m_pBT_Attack->IsAttacking = false;
}

