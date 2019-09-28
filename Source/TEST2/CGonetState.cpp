// Fill out your copyright notice in the Description page of Project Settings.
#include "CGonetState.h"
#include "WinTcp/ClientSocket.h"
#include "WinTcp/Account.h"
#include "Entity.h"
#include "Player/Player.h"

ACGonetState::ACGonetState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WinTcp::CLIENT_TCP->Initial(0);
	WinTcp::ACCOUNT;
	ENTITYMGR;
	PLAYER;
}

// Called when the game starts or when spawned
void ACGonetState::BeginPlay()
{
	Super::BeginPlay();
	WinTcp::DisconnectServer();
	WinTcp::ConnectServer("127.0.0.1", 31700);
	EntityMap.clear();
}

// Called every frame
void ACGonetState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WinTcp::CLIENT_TCP->update(0);
}

