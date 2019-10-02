// Fill out your copyright notice in the Description page of Project Settings.


#include "CBlueprintFunctionLibrary.h"
#include "Base/types.h"

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
