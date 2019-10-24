// Fill out your copyright notice in the Description page of Project Settings.


#include "CBlueprintFunctionLibrary.h"
#include "Base/types.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CGonetState.h"

int64 UCBlueprintFunctionLibrary::Conv_StringToInt64(const FString& InString)
{
	return FCString::Atoi64(*InString);
}

FString UCBlueprintFunctionLibrary::BuildString_Int64(const FString& AppendTo, const FString& Prefix, int64 InInt64, const FString& Suffix)
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

FString UCBlueprintFunctionLibrary::Conv_Int64ToString(int64 InInt64)
{
    return FString(Base::Int64ToStr(InInt64).c_str());
}

ACGameObjectCharacter* UCBlueprintFunctionLibrary::GetEntity(int64 Id)
{
    auto pGonetState = Cast<ACGonetState>(GWorld->GetGameState());
    auto& EntityMap = pGonetState->EntityMap;
    ACGameObjectCharacter* pEntity = NULL;
    auto itr = EntityMap.find(Id);
    if (itr != EntityMap.end()) {
        return itr->second;
    }
    return NULL;
}

FStats3 UCBlueprintFunctionLibrary::AddStats(FStats3 a, FStats3 b) 
{
	a += b;
	return a;
}

FStats3 UCBlueprintFunctionLibrary::SubStats(FStats3 a, FStats3 b)
{
	a -= b;
	return a;
}

FStats3 UCBlueprintFunctionLibrary::MulStats(FStats3 a, float count)
{
	a *= count;
	return a;
}

FStats3 UCBlueprintFunctionLibrary::AddStatsI(FStats3 a, FStats3 b, float count)
{
	a.Add(b, count);
	return a;
}