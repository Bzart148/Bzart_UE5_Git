// Copyright Epic Games, Inc. All Rights Reserved.

#include "Homework7GameMode.h"
#include "Homework7Character.h"
#include "UObject/ConstructorHelpers.h"

AHomework7GameMode::AHomework7GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
