// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
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

	//UFUNCTION(BlueprintImplementableEvent, Category = "C++ | Entity")
	//APawn* SpawnPlayer();
};
