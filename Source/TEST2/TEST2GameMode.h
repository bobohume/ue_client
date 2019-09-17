// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TEST2GameMode.generated.h"

UCLASS(minimalapi)
class ATEST2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATEST2GameMode();

	virtual void InitGameState();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UFUNCTION(BlueprintCallable, Category = "C++ | NetWork")
	void UpdateTick();

	UFUNCTION(BlueprintImplementableEvent, Category = "C++ | Entity")
	APawn* SpawnPlayer();
};



