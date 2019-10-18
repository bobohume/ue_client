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
// ͨ������
USTRUCT(BlueprintType)
struct FStats3
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HP;					// ����						==> ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HP_Pc;				// �����ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HP_gPc;				// ����ȫ�ְٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MP;					// ����						==> ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MP_Pc;				// �����ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MP_gPc;				// ����ȫ�ְٷֱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxHP;				// �������					==> ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxHP_Pc;			// ��������ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxHP_gPc;			// �������ȫ�ְٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxMP;				// �������					==> ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxMP_Pc;			// ��������ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			MaxMP_gPc;			// �������ȫ�ְٷֱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDamage;			// �����˺�					==> ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDamage_Pc;		// �����˺��ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDamage_gPc;		// �����˺�ȫ�ְٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDefence;			// �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDefence_Pc;		// ��������ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			PhyDefence_gPc;		// �������ȫ�ְٷֱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDamage;			// �����˺�					==> ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDamage_Pc;		// �����˺��ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDamage_gPc;		// �����˺�ȫ�ְٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDefence;			// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDefence_Pc;		// ���������ٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			SplDefence_gPc;		// ��������ȫ�ְٷֱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Heal;				// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Heal_Pc;			// ���ưٷֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Heal_gPc;			// ����ȫ�ְٷֱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Velocity_gPc;		// �ƶ��ٶ�ȫ�ְٷֱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			CriticalRating;		// �ػ��ȼ� Ӱ���ػ�����	==> �����ȼ� Ӱ�챩������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			CriticalTimes;		// �ػ�ȫ�ְٷֱ��˺�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Critical_gPc;		// �ػ�ȫ�ְٷֱȼ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			AntiCriticalRating;	// ���ػ��ȼ� Ӱ���ػ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			AntiCriticalTimes;	// ���ػ�ȫ�ְٷֱ��˺�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			AntiCritical_gPc;	// ���ػ�ȫ�ְٷֱȼ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			DodgeRating;		// �������ܵȼ� Ӱ�����ܼ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Dodge_gPc;			// ��������ȫ�ְٷֱȼ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			HitRating;			// �������еȼ� Ӱ�����м���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats3)
	int32			Hit_gPc;			// ��������ȫ�ְٷֱȼ���

	FStats3();
	void Clear();

	FStats3& operator+=(const FStats3&);
	FStats3& operator-=(const FStats3&);
	FStats3& operator*=(const F32);

	// ���ռ���
	void Calc(const FStats3& _add);
	// ����������Դ�����ԣ���Щֵ���裨���ܣ�����
	void PlusSrc(const FStats3& _orig, S32 ratePhy,  S32 rateSpl);
	// ���Ե��ӣ���+=��������˵�����
	FStats3& Add(const FStats3& _add, S32 _count = 1);
};

extern FStats3 g_Stats;

