#pragma once  

#include "Engine/DataTable.h"  
#include "Data.generated.h"  

USTRUCT(BlueprintType)
struct FAiData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FAiData()
	{}

	/** The 'Name' column is the same as the XP Level */

	/** XP to get to the given level from the previous level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
		int32 Id;

	/** Extra HitPoints gained at this level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
		int32 Op;

	/** Icon to use for Achivement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
		int32 Type;

	/** Icon to use for Achivement */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
	//	TAssetPtr<UTexture> AchievementIcon;
};