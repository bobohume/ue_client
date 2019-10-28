#pragma once  

#include "Engine/DataTable.h"  
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "GameFramework/Character.h"
#include "GameObject/GameObjectCharacter.h"
#include "NpcData.generated.h"  

USTRUCT(BlueprintType)
struct FNpcData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FNpcData()
	{}

	/** npc name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FNpcData)
	FString Name;

	/** npc icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FNpcData)
	TSoftObjectPtr<UTexture2D> Icon;

	/** npc Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FNpcData)
	TSoftObjectPtr<USkeletalMesh> Mesh;

	/** npc Animal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FNpcData)
	TSoftClassPtr<UAnimInstance> Anim;
};