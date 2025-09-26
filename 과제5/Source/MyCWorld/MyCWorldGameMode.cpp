// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCWorldGameMode.h"
#include "MyCWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyCWorldGameMode::AMyCWorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
