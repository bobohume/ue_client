// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TEST2GameMode.h"
#include "TEST2Character.h"
#include "UObject/ConstructorHelpers.h"


ATEST2GameMode::ATEST2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}