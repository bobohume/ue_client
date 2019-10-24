#pragma once  

#include "Data.h"

FNpcData* DataMgr::GetNpcData(FString Id)
{
	UDataTable *pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("/Game/data/Npc.Npc"));
	FString ContextString;
	TArray<FName> RowNames;
	RowNames = pDataTable->GetRowNames();
	for (auto& name : RowNames)
	{
		FNpcData* pNpcData = pDataTable->FindRow<FNpcData>(name, ContextString);
		if (pNpcData)
		{
			return pNpcData;
		}
	}
	return NULL;
}