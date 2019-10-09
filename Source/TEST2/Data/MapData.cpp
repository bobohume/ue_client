#pragma once  

#include "MapData.h"
#include "DataFile.h"
#include "Paths.h"

#define MAP_DATA_NAME  "Content/data/Map.dat"

MapDataRes::MapDataRes() 
{

}

MapDataRes::~MapDataRes()
{

}

bool MapDataRes::Read()
{
	FString str = FPaths::GameDir() + MAP_DATA_NAME;
	CDataFile file;
	RData lineData;
	if (!file.ReadDataFile(TCHAR_TO_UTF8(*str))) {
		UE_LOG(LogClass, Log, TEXT("read %s error"), MAP_DATA_NAME);
		return false;
	}

	for(int i = 0; i < file.RecordNum; i++){
		FMapData* pData = new FMapData{};
		file.GetData(lineData);
		pData->Id = lineData.Int(MAP_DATA_NAME, "Id");

		file.GetData(lineData);
		pData->Type = lineData.Enum(MAP_DATA_NAME, "Type");

		file.GetData(lineData);//AIID

		file.GetData(lineData);
		pData->Width = lineData.Int(MAP_DATA_NAME, "Width");

		file.GetData(lineData);
		pData->Height = lineData.Int(MAP_DATA_NAME, "Height");

		file.GetData(lineData);//NavPath

		AddData(pData->Id, pData);
	}

	UE_LOG(LogClass, Log, TEXT("Map read finish"));

	return true;
}