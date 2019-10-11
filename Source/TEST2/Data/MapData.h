#pragma once  

#include "DataRes.h" 
#include "MapData.generated.h"  

USTRUCT(BlueprintType)
struct FMapData
{
	GENERATED_USTRUCT_BODY()

public:

	FMapData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapData)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapData)
	int32 Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapData)
	int32 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapData)
	int32 Height;
};

class MapDataRes : public DataRes<int32, FMapData*>
{
public:
	MapDataRes();

	static MapDataRes* Instance() {
		static MapDataRes s_Instace;
		return &s_Instace;
	}

	virtual ~MapDataRes();
	virtual bool Read();
};

#define MAPDATA MapDataRes::Instance()