// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TEST2GameMode.h"
#include "TEST2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "WinTcp/ClientSocket.h"
#include "WinTcp/Account.h"
#include "Entity.h"

ATEST2GameMode::ATEST2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	WinTcp::CLIENT_TCP->Initial(0);
	WinTcp::ACCOUNT;
	ENTITY;
	WinTcp::ConnectServer("127.0.0.1", 31700);
}

void ATEST2GameMode::InitGameState() {
	Super::InitGameState();
}

void ATEST2GameMode::UpdateTick() {
	//auto pActo = SpawnPlayer();
	WinTcp::CLIENT_TCP->update(0);
}
