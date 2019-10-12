// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CGameObjectCharacter.generated.h"

UCLASS()
class ACGameObjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACGameObjectCharacter();

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
    
    // Entity TargetId
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(DisplayName="TargetId"), Category = "Entity")
    int64 TargetId;

	// Entity move
	//UFUNCTION(BlueprintImplementableEvent, Category = "Entity")
	//void MoveTo(FVector pos);
};
