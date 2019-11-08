// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/Stats.h"
#include "GameObjectCharacter.generated.h"

UCLASS()
class AGameObjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameObjectCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Entity Id
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	int64 Id;

	//  µÃÂ Ù–‘
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	FStats3 Stats;
    
    // Entity TargetId
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(DisplayName="TargetId"), Category = "Entity")
    int64 TargetId;

	// NPC DATA Id
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	int32 DataId;

public:
	//for blueprint
	//entity init
	UFUNCTION(BlueprintImplementableEvent, Category = "Entity")
	void Init();

	//show damage
	UFUNCTION(BlueprintImplementableEvent, Category = "Entity")
	void ShowDamageAmount(int32 damage);
};
