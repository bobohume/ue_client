// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
//蓝图全局方法
UCLASS()
class TEST2_API UCBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MyFunction|MyClass")
	static void Method1();
};
