// Fill out your copyright notice in the Description page of Project Settings.
#include "CGamePlayState.h"
#include "WinTcp/ClientSocket.h"
#include "WinTcp/Account.h"
#include "Entity.h"
#include "Player/Player.h"

ACGamePlayState::ACGamePlayState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WinTcp::CLIENT_TCP->Initial(0);
	WinTcp::ACCOUNT;
	ENTITYMGR;
	PLAYER;
}

// Called when the game starts or when spawned
void ACGamePlayState::BeginPlay()
{
	Super::BeginPlay();
	WinTcp::DisconnectServer();
	WinTcp::ConnectServer("127.0.0.1", 31700);
	int  AA = 0;

}

// Called every frame
void ACGamePlayState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WinTcp::CLIENT_TCP->update(0);
}