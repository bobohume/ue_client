#pragma once  

#include "CoreMinimal.h"
#include "NpcData.h"

//C++ªÒ»°¿∂Õºdata
class DataMgr {
public:
	DataMgr() {
	}

	static DataMgr* Instance() {
		static DataMgr s_Instace;
		return &s_Instace;
	}

	FNpcData* GetNpcData(FString Id);
};

#define DATAMGR DataMgr::Instance()