// Fill out your copyright notice in the Description page of Project Settings.
#include "GonetState.h"
#include "WinTcp/ClientSocket.h"
#include "WinTcp/Account.h"
#include "Entity.h"
#include "Player/Player.h"
#include "Data/Data.h"

AGonetState::AGonetState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WinTcp::CLIENT_TCP->Initialize();
	WinTcp::ACCOUNT;
	ENTITYMGR;
	PLAYER;
}

// Called when the game starts or when spawned
void AGonetState::BeginPlay()
{
	Super::BeginPlay();
	WinTcp::CLIENT_TCP->Disconnect();
	WinTcp::CLIENT_TCP->Connect("127.0.0.1", 31700);
	EntityMap.clear();
	DATAMGR->GetNpcData(FString("199999"));
}

// Called every frame
void AGonetState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WinTcp::CLIENT_TCP->update(0);
}

