#pragma once  

#include "Engine/DataTable.h"  
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "GameFramework/Character.h"
#include "GameObject/CGameObjectCharacter.h"
#include "Stats.h"
#include "BuffData.generated.h"  

USTRUCT(BlueprintType)
struct FBuffData : public FStats3
{
	GENERATED_USTRUCT_BODY()

public:

	FBuffData()
	{}

	/** buff lv */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FBuffData)
	int32 Lv;

	/** buff name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FBuffData)
	FString Name;

	/** buff icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FBuffData)
	FString Icon;
	//TSoftObjectPtr<UTexture2D> Icon;

	/** buff desc */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FBuffData)
	FString Desc;
};