#pragma once
#ifndef MEFFECT_H
#define MEFFECT_H

#include <vector>

#include "moveconst.h"

struct Actor;

const float CHARGED_BUFF_BONUS = .15f;
const float EFFICIENT_BUFF_BONUS = .2f;
const float SHARPENED_BUFF_BONUS = .15f;
const float BRITTLE_DEBUFF_BONUS = .15f;
const float CURSED_DEBUFF_BONUS = .15f;
const float MANABURN_DEBUFF_BONUS = .125f;

struct MoveEffect{
	enum Family : int{
		noFam,
		burning,
		wet,
		florid,
		lifeDrain,
		poisoned,
		charged,
		efficient,
		feared,
		taunted,
		frozen,
		sharpened,
		corroding,
		brittle,
		supernatural,
		cursed,
		decaying,
		manaburn
	};

	int id; //Id of the move that was used to produce this effect
	int duration; //Based off ID
	int numDiffs = 0;
	struct EffectDiff *diffs = nullptr;

	Family family = noFam;
	Actor *affector = nullptr;
	Actor *affected = nullptr;

	void TickDamage(int damage);
	void TickHealCaster(int damage);
	void TickHealTarget(int damage);
	void Tick(Actor *);

	MoveEffect(int id){
		this->id = id;
	}
	~MoveEffect();
};


//val - damage or healing
void LifeDrain(MoveEffect &, Actor *, int val);

struct EffectDiff{
	enum Stat : int{
		maxHP,
		maxMP,
		mAtk0,
		mAtk1,
		mAtk2,
		mAtk3,
		mAtk4,
		mAtk5,
		mAtk6,
		mDef0,
		mDef1,
		mDef2,
		mDef3,
		mDef4,
		mDef5,
		mDef6,
		pAtk0,
		pAtk1,
		pAtk2,
		pAtk3,
		pAtk4,
		pAtk5,
		pAtk6,
		pDef0,
		pDef1,
		pDef2,
		pDef3,
		pDef4,
		pDef5,
		pDef6,
		hpBonus,
		mpBonus,
		immunity0,
		immunity1,
		immunity2,
		immunity3,
		immunity4,
		immunity5,
		immunity6,
		pIncap,
		mIncap,
		disabled,
		type0,
		type1,
		immunityP,
		immunityM,
		noStat
	};

	Stat stat;

	int prev; //The prev value of the stat
	int curr; //The curr value of the stat
	int diff; //curr - prev

	Actor *affected;

	EffectDiff(){
		stat = noStat;
		prev = curr = diff = 0;
		affected = nullptr;
	}
	~EffectDiff();
};

//Returns whether the effect is already applied to an actor, 3rd param is the matching effect
bool HasEffect(Actor &target, MoveEffect &, MoveEffect *);

//Returns whether the effect's duration is potentially updated
bool UpdateEffectDuration(Actor &, MoveEffect &);

//Returns how long the effect will last for... 1 is after current turn
int GetEffectPrimaryDuration(int id);

//Returns how long the effect will last for... 1 is after current turn
int GetEffectSecondaryDuration(int id);

//Returns damage that the move effect causes, could be none
int GetEffectDamage(int id);

//Returns the healing % that an actor is healed from an effect, could be none
float GetEffectHeal(int id);

//Returns the primary buff of that move effect
float GetEffectPrimaryBuff(int id);

//Returns the secondary buff of that move effect, could be none
float GetEffectSecondaryBuff(int id);

//Returns the primary debuff of that move effect
float GetEffectPrimaryDebuff(int id);

//Returns the secondary debuff of that move effect, could be none
float GetEffectSecondaryDebuff(int id);

//-
void ApplyEffectDiff(Actor &, MoveEffect &);

//-
void ApplyMaxHPDiff(Actor &, EffectDiff &, int &);

//-
void ApplyMaxMPDiff(Actor &, EffectDiff &, int &);

//-
void ApplyMATKDiff(Actor &, EffectDiff &, int &);

//-
void ApplyMDEFDiff(Actor &, EffectDiff &, int &);

//-
void ApplyPATKDiff(Actor &, EffectDiff &, int &);

//-
void ApplyPDEFDiff(Actor &, EffectDiff &, int &);

//-
void ApplyImmunityDiff(Actor &, EffectDiff &, int &);

//-
void ApplyIncapicateDiff(Actor &, EffectDiff &, int &);

//-
void ApplyDisableDiff(Actor &, EffectDiff &, int &);

//-
void ApplyTypeDiff(Actor &, EffectDiff &, int &);

//-
void ApplyHPBonusDiff(Actor &, EffectDiff &, int &);

//-
void ApplyMPBonusDiff(Actor &, EffectDiff &, int &);

//-
void UndoEffectDiff(MoveEffect &);

//-
void UndoMaxHPDiff(EffectDiff &);

//-
void UndoMaxMPDiff(EffectDiff &);

//-
void UndoMATKDiff(EffectDiff &);

//-
void UndoMDEFDiff(EffectDiff &);

//-
void UndoPATKDiff(EffectDiff &);

//-
void UndoPDEFDiff(EffectDiff &);

//-
void UndoImmunityDiff(EffectDiff &);

//-
void UndoIncapicateDiff(EffectDiff &);

//-
void UndoDisableDiff(EffectDiff &);

//-
void UndoTypeDiff(EffectDiff &);

#endif
