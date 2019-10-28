// Fill out your copyright notice in the Description page of Project Settings.


#include "GonetBlueprintFunctionLibrary.h"
#include "Base/types.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GonetState.h"

int64 UGonetBlueprintFunctionLibrary::Conv_StringToInt64(const FString& InString)
{
	return FCString::Atoi64(*InString);
}

FString UGonetBlueprintFunctionLibrary::BuildString_Int64(const FString& AppendTo, const FString& Prefix, int64 InInt64, const FString& Suffix)
{
	// faster, preallocating method
	FString const IntStr = FString::Printf(TEXT("%d"), InInt64);

	FString StringResult;
	StringResult.Empty(AppendTo.Len() + Prefix.Len() + IntStr.Len() + Suffix.Len() + 1); // adding one for the string terminator
	StringResult += AppendTo;
	StringResult += Prefix;
	StringResult += IntStr;
	StringResult += Suffix;

	return StringResult;
}

FString UGonetBlueprintFunctionLibrary::Conv_Int64ToString(int64 InInt64)
{
    return FString(Base::Int64ToStr(InInt64).c_str());
}

AGameObjectCharacter* UGonetBlueprintFunctionLibrary::GetEntity(int64 Id)
{
    auto pGonetState = Cast<AGonetState>(GWorld->GetGameState());
    auto& EntityMap = pGonetState->EntityMap;
	AGameObjectCharacter* pEntity = NULL;
    auto itr = EntityMap.find(Id);
    if (itr != EntityMap.end()) {
        return itr->second;
    }
    return NULL;
}

FStats3 UGonetBlueprintFunctionLibrary::AddStats(FStats3 a, FStats3 b)
{
	a += b;
	return a;
}

FStats3 UGonetBlueprintFunctionLibrary::SubStats(FStats3 a, FStats3 b)
{
	a -= b;
	return a;
}

FStats3 UGonetBlueprintFunctionLibrary::MulStats(FStats3 a, float count)
{
	a *= count;
	return a;
}

FStats3 UGonetBlueprintFunctionLibrary::AddStatsI(FStats3 a, FStats3 b, float count)
{
	a.Add(b, count);
	return a;
}