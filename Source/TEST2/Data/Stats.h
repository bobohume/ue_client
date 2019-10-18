//-----------------------------------------------------------------------------
// PowerEngine
// Copyright (C) FireRain.com, Inc.
//-----------------------------------------------------------------------------

#pragma once
#include "CoreMinimal.h"
#include "Base/types.h"
#include "Stats.generated.h"  
// ========================================================================================================================================
//  Stats
// ========================================================================================================================================

using namespace Base;
// 通用属性
USTRUCT(BlueprintType)
struct FStats3
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HP;					// 生命						==> 体力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HP_Pc;				// 生命百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HP_gPc;				// 生命全局百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MP;					// 真气						==> 精力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MP_Pc;				// 真气百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MP_gPc;				// 真气全局百分比

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxHP;				// 最大生命					==> 体力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxHP_Pc;			// 最大生命百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxHP_gPc;			// 最大生命全局百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxMP;				// 最大真气					==> 精力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxMP_Pc;			// 最大真气百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxMP_gPc;			// 最大真气全局百分比

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDamage;			// 物理伤害					==> 物击
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDamage_Pc;		// 物理伤害百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDamage_gPc;		// 物理伤害全局百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDefence;			// 物理防御
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDefence_Pc;		// 物理防御百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDefence_gPc;		// 物理防御全局百分比

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDamage;			// 法攻伤害					==> 法攻
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDamage_Pc;		// 法攻伤害百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDamage_gPc;		// 法攻伤害全局百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDefence;			// 法攻防御
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDefence_Pc;		// 法攻防御百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDefence_gPc;		// 法攻防御全局百分比

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Heal;				// 治疗
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Heal_Pc;			// 治疗百分比
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Heal_gPc;			// 治疗全局百分比

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Velocity_gPc;		// 移动速度全局百分比

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			CriticalRating;		// 重击等级 影响重击几率	==> 暴击等级 影响暴击几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			CriticalTimes;		// 重击全局百分比伤害倍数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Critical_gPc;		// 重击全局百分比几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			AntiCriticalRating;	// 防重击等级 影响重击几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			AntiCriticalTimes;	// 抗重击全局百分比伤害倍数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			AntiCritical_gPc;	// 防重击全局百分比几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			DodgeRating;		// 物理闪避等级 影响闪避几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Dodge_gPc;			// 物理闪避全局百分比几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HitRating;			// 物理命中等级 影响命中几率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Hit_gPc;			// 物理命中全局百分比几率

	FStats3();
	void Clear();

	FStats3& operator+=(const FStats3&);
	FStats3& operator-=(const FStats3&);
	FStats3& operator*=(const F32);

	// 最终计算
	void Calc(const FStats3& _add);
	// 按比例叠加源的属性，有些值无需（不能）叠加
	void PlusSrc(const FStats3& _orig, S32 ratePhy,  S32 rateSpl);
	// 属性叠加，与+=相比增加了叠加数
	FStats3& Add(const FStats3& _add, S32 _count = 1);
};

extern FStats3 g_Stats;

