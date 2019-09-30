// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <unordered_map>
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TEST2Character.h"
#include "CGonetState.generated.h"

/**
 * 
 */
UCLASS()
class TEST2_API ACGonetState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACGonetState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//UFUNCTION(BlueprintCallable, Category = "C++ | NetWork")
	//void UpdateTick();
	//蓝图创建对象实体
	UFUNCTION(BlueprintImplementableEvent, Category = "Gonet | Entity")
	APawn* SpawnPlayer(FVector pos, FRotator rotation);

	std::unordered_map<int64, ACGameObjectCharacter*> EntityMap;
};
//调试变量不优化掉
//#pragma optimize("",off) 
//#pragma optimize("",on) 
