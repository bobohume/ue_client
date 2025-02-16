// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameObject/GameObjectCharacter.h"
#include <unordered_map>
#include "Data/Stats.h"
#include "GonetBlueprintFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class EnDataType :uint8
{
	MAP UMETA(DisplayName = "map")
};
/**
 * 
 */
//��ͼȫ�ַ���
UCLASS()
class UGonetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    //---------------------int64 to string------------------//
	/**
	 * Converts a int64->string, creating a new string in the form AppendTo+Prefix+InInt64+Suffix
	 * @param AppendTo - An existing string to use as the start of the conversion string
	 * @param Prefix - A string to use as a prefix, after the AppendTo string
	 * @param InInt64 - The int64 value to convert
	 * @param Suffix - A suffix to append to the end of the conversion string
	 * @return A new string built from the passed parameters
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "BuildString (integer64)"), Category = "Utilities|String")
	static FString BuildString_Int64(const FString& AppendTo, const FString& Prefix, int64 InInt64, const FString& Suffix);

	/** Converts a string to a int64 value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "String To Int64", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")
	static int64 Conv_StringToInt64(const FString& InString);

	/** Converts an integer value to a string */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (integer64)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")
	static FString Conv_Int64ToString(int64 InInt64);
    //---------------------int64 to string------------------//
    
    //----------------------entiy--------------------------//
    /** get enity by id */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetEntity(id)", /*CompactNodeTitle = "->",*/ BlueprintAutocast), Category = "Gonet|Entity")
    static AGameObjectCharacter* GetEntity(int64 Id);

	//-----------------------stats-----------------------//
	UFUNCTION(BlueprintPure, meta = (DisplayName = "+Stats(FStats3 a, FStats3 b)", CompactNodeTitle = "+", BlueprintAutocast), Category = "Gonet|Data")
	static FStats3 AddStats(FStats3 a, FStats3 b);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "-Stats(FStats3 a, FStats3 b)", CompactNodeTitle = "-", BlueprintAutocast), Category = "Gonet|Data")
	static FStats3 SubStats(FStats3 a, FStats3 b);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "*Stats(FStats3 a, float count)", CompactNodeTitle = "*", BlueprintAutocast), Category = "Gonet|Data")
	static FStats3 MulStats(FStats3 a, float count);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "AddStatsI(FStats3 a, FStats3 b, float count)", CompactNodeTitle = "++", BlueprintAutocast), Category = "Gonet|Data")
	static FStats3 AddStatsI(FStats3 a, FStats3 b,  float count);
	//-----------------------stats-----------------------//
};
