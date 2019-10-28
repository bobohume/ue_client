// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <unordered_map>
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GonetCharacter.h"
#include "GonetState.generated.h"

/**
 * 
 */
UCLASS()
class AGonetState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AGonetState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//UFUNCTION(BlueprintCallable, Category = "C++ | NetWork")
	//void UpdateTick();
	//��ͼ��������ʵ��
	UFUNCTION(BlueprintImplementableEvent, Category = "Gonet|Entity")
	APawn* SpawnPlayer(FVector pos, FRotator rotation);

	std::unordered_map<int64, AGameObjectCharacter*> EntityMap;
};
//���Ա������Ż���
//#pragma optimize("",off) 
//#pragma optimize("",on) 
