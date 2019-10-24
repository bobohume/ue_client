#pragma once  

#include "Engine/DataTable.h"  
#include "CoreMinimal.h"
#include "Data.generated.h"  

USTRUCT(BlueprintType)
struct FAiData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FAiData()
	{}

	/** The 'Name' column is the same as the XP Level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
	FString Name;

	/** XP to get to the given level from the previous level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
	TSoftObjectPtr<UTexture2D> Icon;

	/** Extra HitPoints gained at this level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
	TSoftObjectPtr<USkeletalMesh> Mesh;

	/** Icon to use for Achivement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
	TSoftClassPtr<UAnimBlueprintGeneratedClass> Animal;

	/** Icon to use for Achivement */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AiData)
	//TSoftObjectPtr<UTexture> AchievementIcon;
};