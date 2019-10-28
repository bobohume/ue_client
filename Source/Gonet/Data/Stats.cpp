//-----------------------------------------------------------------------------
// PowerEngine
// Copyright (C) FireRain.com, Inc.
//-----------------------------------------------------------------------------

#include "Stats.h"
#include <math.h>

inline int32 mFloor(const F32 val)
{
	return (F32)floor(val);
}


int32 getDodgeRate(int32 val) {
	int q = 1.083, a = 255.0;
	return int32(log(1.0 - (float(val) * (1 - q) / a)) / log(q) * 0.01 * GAMEPLAY_PERCENT_SCALE);
}

int32 getAntiCriticalRate(int32 val) {
	int q = 1.0249, a = 25.0;
	return int32(log(1.0 - (float(val) * (1 - q) / a)) / log(q) * 0.01 * GAMEPLAY_PERCENT_SCALE);
}

int32 getMultipleRate(int32 val) {
	int q = 1.015, a = 450.0;
	return int32(log(1.0 - (float(val) * (1 - q) / a)) / log(q) * 0.01 * GAMEPLAY_PERCENT_SCALE);
}

int32 getCriticalRate(int32 val) {
	int q = 1.0266, a = 25.0;
	return int32(log(1.0 - (float(val) * (1 - q) / a)) / log(q) * 0.01 * GAMEPLAY_PERCENT_SCALE);
}

float getDamageReducePhy(int32 val) {
	int q = 1.04, a = 100.0;
	return float(log(1.0 - (float(val) * (1 - q) / a)) / log(q) * 0.01 * GAMEPLAY_PERCENT_SCALE);
}

float GetDamageReduceSpl(int32 val) {
	int q = 1.05, a = 80.0;
	return float(log(1.0 - (float(val) * (1 - q) / a)) / log(q) * 0.01 * GAMEPLAY_PERCENT_SCALE);
}

FStats3 g_Stats;
FStats3::FStats3()
{
	//Clear();
}

void FStats3::Clear()
{
	dMemset(this, 0, sizeof(FStats));
}

// 做A+=B和A-=B时，注意A::HP和A::HP_Pc没有做运算。所以一般来说A的初始值都为0
FStats3& FStats3::operator+=(const FStats3& _add)
{
	return Add(_add, 1);
}

FStats3& FStats3::operator-=(const FStats3& _add)
{
	HP -= mFloor(_add.HP + _add.HP * _add.HP_Pc / GAMEPLAY_PERCENT_SCALE);
	HP_gPc -= _add.HP_gPc;
	MP -= mFloor(_add.MP + _add.MP * _add.MP_Pc / GAMEPLAY_PERCENT_SCALE);
	MP_gPc -= _add.MP_gPc;

	MaxHP -= mFloor(_add.MaxHP + _add.MaxHP * _add.MaxHP_Pc / GAMEPLAY_PERCENT_SCALE);
	MaxHP_gPc -= _add.MaxHP_gPc;
	MaxMP -= mFloor(_add.MaxMP + _add.MaxMP * _add.MaxMP_Pc / GAMEPLAY_PERCENT_SCALE);
	MaxMP_gPc -= _add.MaxMP_gPc;

	PhyDamage -= mFloor(_add.PhyDamage + _add.PhyDamage * _add.PhyDamage_Pc / GAMEPLAY_PERCENT_SCALE);
	PhyDamage_gPc -= _add.PhyDamage_gPc;

	PhyDefence -= mFloor(_add.PhyDefence + _add.PhyDefence * _add.PhyDefence_Pc / GAMEPLAY_PERCENT_SCALE);
	PhyDefence_gPc -= _add.PhyDefence_gPc;

	SplDamage -= mFloor(_add.SplDamage + _add.SplDamage * _add.SplDamage_Pc / GAMEPLAY_PERCENT_SCALE);
	SplDamage_gPc -= _add.SplDamage_gPc;

	SplDefence -= mFloor(_add.SplDefence + _add.SplDefence * _add.SplDefence_Pc / GAMEPLAY_PERCENT_SCALE);
	SplDefence_gPc -= _add.SplDefence_gPc;

	Heal -= mFloor(_add.Heal + _add.Heal * _add.Heal_Pc / GAMEPLAY_PERCENT_SCALE);
	Heal_gPc -= _add.Heal_gPc;

	CriticalRating -= _add.CriticalRating;
	CriticalTimes -= _add.CriticalTimes;
	Critical_gPc -= _add.Critical_gPc;
	AntiCriticalRating -= _add.AntiCriticalRating;
	AntiCriticalTimes -= _add.AntiCriticalTimes;
	AntiCritical_gPc -= _add.AntiCritical_gPc;
	Velocity_gPc -= _add.Velocity_gPc;
	DodgeRating -= _add.DodgeRating;
	Dodge_gPc -= _add.Dodge_gPc;
	HitRating -= _add.HitRating;
	Hit_gPc -= _add.Hit_gPc;
	return *this;
}

FStats3& FStats3::operator*=(const F32 scale)
{
	MaxHP *= scale;
	MaxHP_gPc *= scale;
	MaxMP *= scale;
	MaxMP_gPc *= scale;
	PhyDamage *= scale;
	PhyDefence *= scale;
	SplDamage *= scale;
	SplDefence *= scale;
	Heal *= scale;

	CriticalRating *= scale;
	CriticalTimes *= scale;
	Critical_gPc *= scale;
	AntiCriticalRating *= scale;
	AntiCriticalTimes *= scale;
	AntiCritical_gPc *= scale;
	Velocity_gPc *= scale;
	DodgeRating *= scale;
	Dodge_gPc *= scale;
	HitRating *= scale;
	Hit_gPc *= scale;
	return *this;
}

void FStats3::Calc(const FStats3& _add)
{
	Clear();

	HP = _add.HP + _add.HP * _add.HP_gPc / GAMEPLAY_PERCENT_SCALE;
	MP = _add.MP + _add.MP * _add.MP_gPc / GAMEPLAY_PERCENT_SCALE;

	MaxHP = getMax((MaxHP + _add.MaxHP) * (1.0f + _add.MaxHP_gPc / GAMEPLAY_PERCENT_SCALE), 1.0f);
	MaxMP = getMax((MaxMP + _add.MaxMP) * (1.0f + _add.MaxMP_gPc / GAMEPLAY_PERCENT_SCALE), 1.0f);

	PhyDamage = getMax((PhyDamage + _add.PhyDamage) * (1.0f + _add.PhyDamage_gPc / GAMEPLAY_PERCENT_SCALE), 0.0f);
	PhyDefence = getMax(PhyDefence + _add.PhyDefence * (1.0f + _add.PhyDefence_gPc / GAMEPLAY_PERCENT_SCALE), 0.0f);
	SplDamage = getMax((SplDamage + _add.SplDamage) * (1.0f + _add.SplDamage_gPc / GAMEPLAY_PERCENT_SCALE), 0.0f);
	SplDefence = getMax(SplDefence + _add.SplDefence * (1.0f + _add.SplDefence_gPc / GAMEPLAY_PERCENT_SCALE), 0.0f);
	Heal = getMax(_add.Heal * (1.0f + _add.Heal_gPc / GAMEPLAY_PERCENT_SCALE), 0.0f);

	CriticalRating = _add.CriticalRating;
	CriticalTimes = mClamp(_add.CriticalTimes, GAMEPLAY_PERCENT_SCALE, 100000);
	Critical_gPc = _add.Critical_gPc + getCriticalRate(CriticalRating);
	AntiCriticalRating = _add.AntiCriticalRating;
	AntiCriticalTimes = mClamp(_add.AntiCriticalTimes, 0, 100000);
	AntiCritical_gPc = _add.AntiCritical_gPc + getAntiCriticalRate(AntiCriticalRating);
	Velocity_gPc = mClampF(_add.Velocity_gPc, 0, GAMEPLAY_PERCENT_SCALE);
	DodgeRating = _add.DodgeRating;
	Dodge_gPc = _add.Dodge_gPc + getDodgeRate(DodgeRating);
	HitRating = _add.HitRating;								
	Hit_gPc = _add.Hit_gPc + getDodgeRate(HitRating);
}

void FStats3::PlusSrc(const FStats3& _orig, S32 ratePhy,  S32 rateSpl)
{
	// 加成比例
	F32 _ratePhy = mClampF(ratePhy/GAMEPLAY_PERCENT_SCALE, 0.0f, 3.0f);
	F32 _rateSpl = mClampF(rateSpl/GAMEPLAY_PERCENT_SCALE, 0.0f, 3.0f);
	PhyDamage += _orig.PhyDamage * _ratePhy * (getMax(PhyDamage_gPc + GAMEPLAY_PERCENT_SCALE, 0.0f) / GAMEPLAY_PERCENT_SCALE);
	SplDamage += _orig.SplDamage * _ratePhy * (getMax(SplDamage_gPc + GAMEPLAY_PERCENT_SCALE, 0.0f) / GAMEPLAY_PERCENT_SCALE);

	Heal += _orig.Heal * rateSpl * (getMax(Heal_gPc + GAMEPLAY_PERCENT_SCALE, 0.0f) / GAMEPLAY_PERCENT_SCALE);
}

FStats3& FStats3::Add(const FStats3& _add, S32 _count /* = 1 */)
{
	HP += mFloor(_add.HP + _add.HP * _add.HP_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	HP_gPc += _add.HP_gPc * _count;
	MP += mFloor(_add.MP + _add.MP * _add.MP_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	MP_gPc += _add.MP_gPc * _count;

	MaxHP += mFloor(_add.MaxHP + _add.MaxHP * _add.MaxHP_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	MaxHP_gPc += _add.MaxHP_gPc * _count;
	MaxMP += mFloor(_add.MaxMP + _add.MaxMP * _add.MaxMP_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	MaxMP_gPc += _add.MaxMP_gPc * _count;

	PhyDamage += mFloor(_add.PhyDamage + _add.PhyDamage * _add.PhyDamage_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	PhyDamage_gPc += _add.PhyDamage_gPc * _count;

	PhyDefence += mFloor(_add.PhyDefence + _add.PhyDefence * _add.PhyDefence_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	PhyDefence_gPc += _add.PhyDefence_gPc * _count;

	SplDamage += mFloor(_add.SplDamage + _add.SplDamage * _add.SplDamage_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	SplDamage_gPc += _add.SplDamage_gPc * _count;

	SplDefence += mFloor(_add.SplDefence + _add.SplDefence * _add.SplDefence_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	SplDefence_gPc += _add.SplDefence_gPc * _count;

	Heal += mFloor(_add.Heal + _add.Heal * _add.Heal_Pc / GAMEPLAY_PERCENT_SCALE) * _count;
	Heal_gPc += _add.Heal_gPc * _count;

	CriticalRating += _add.CriticalRating * _count;
	CriticalTimes += _add.CriticalTimes * _count;
	Critical_gPc += _add.Critical_gPc * _count;
	AntiCriticalRating += _add.AntiCriticalRating * _count;
	AntiCriticalTimes += _add.AntiCriticalTimes * _count;
	AntiCritical_gPc += _add.AntiCritical_gPc * _count;
	Velocity_gPc += _add.Velocity_gPc * _count;
	DodgeRating += _add.DodgeRating * _count;
	Dodge_gPc += _add.Dodge_gPc * _count;
	HitRating += _add.HitRating * _count;
	Hit_gPc += _add.Hit_gPc * _count;
	return *this;
}