#pragma once  

#include "CoreMinimal.h"
#include "NpcData.h"

//C++��ȡ��ͼdata
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