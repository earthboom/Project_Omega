// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project_OmegaGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AProject_OmegaGameModeBase::AProject_OmegaGameModeBase()
{
	//static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Load(TEXT("Blueprint '/Blueprint/Character/BP_Omega_Character.BP_Omega_Character"));
	//TSubclassOf<class UBlueprint> BPClassObj = nullptr;
	//if (BP_Load.Object != nullptr)
	//	BPClassObj = (UClass*)BP_Load.Object->GeneratedClass;

	ConstructorHelpers::FObjectFinder<UBlueprint> BP_Load(TEXT("Blueprint'/Game/Blueprint/Character/BP_Omega_Character.BP_Omega_Character'"));
	if (BP_Load.Object != nullptr)
		DefaultPawnClass = (UClass*)BP_Load.Object->GeneratedClass;
}