#include "include\moveeffect.h"
#include "include\actor.h"
#include "include\combat.h"


MoveEffect::~MoveEffect(){
	for(int i = 0; i < numDiffs; ++i)
		diffs[i].~EffectDiff();

	if(diffs)
		MemPoolFree(&CombatData::diffMemPool, diffs);
}

void MoveEffect::Tick(Actor *actor){
	switch(id){
	case FIREBALL:
		TickDamage(GetEffectDamage(id));
		break;
	case EXPLOSION:
		TickDamage(GetEffectDamage(id));
		break;
	case FIREBEAM:
		TickDamage(GetEffectDamage(id));
		break;
	case FLAMESWORD:
		TickDamage(GetEffectDamage(id));
		break;
	case FLAREKICK:
		TickDamage(GetEffectDamage(id));
		break;
	case FIREWALL:
		TickDamage(GetEffectDamage(id));
		break;
	case MOLTENMETEOR:
		TickDamage(GetEffectDamage(id));
		break;
	case RAZEEARTH:
		TickDamage(GetEffectDamage(id));
		break;
	case SUPERNOVA:
		TickDamage(GetEffectDamage(id));
		break;
	case FLASHFRICTION:
		TickDamage(GetEffectDamage(id));
		break;
	case SCORCHINGHEAT:
		TickDamage(GetEffectDamage(id));
		break;
	case ICARUSINFERNO:
		TickDamage(GetEffectDamage(id));
		break;
	case SAPPINGSTEMS:
		LifeDrain(*this, actor, this->id);
		break;
	case FUNGALSPORES:
		TickDamage(GetEffectDamage(id));
		break;
	case UNDERGROWTH:
		LifeDrain(*this, actor, this->id);
		break;
	case DRYADSCURSE:
		LifeDrain(*this, actor, this->id);
		break;
	case BALLANDCHAIN:
		TickDamage(GetEffectDamage(id));
		break;
	case COPPERCUTLASS:
		TickDamage(GetEffectDamage(id));
		break;
	case RAZORWIRE:
		TickDamage(GetEffectDamage(id));
		break;
	case PIERCINGPLATINUM:
		TickDamage(GetEffectDamage(id));
		break;
	default:
		break;
	}

	duration--;
}


void MoveEffect::TickDamage(int healing){
	affected->remHP += healing;
	
	if(affected->remHP < 0)
		affected->remHP = 0;
}


void MoveEffect::TickHealTarget(int healing){
	affected->remHP += healing;
	
	if(affected->remHP > affected->maxHP)
		affected->remHP = affected->maxHP;
}


void MoveEffect::TickHealCaster(int healing){
	affector->remHP += healing;
	
	if(affector->remHP > affector->maxHP)
		affector->remHP = affector->maxHP;
}


EffectDiff::~EffectDiff(){
	switch(stat){
	case maxHP:
		UndoMaxHPDiff(*this);
		break;
	case maxMP:
		UndoMaxMPDiff(*this);
		break;
	case mAtk0:
	case mAtk1:
	case mAtk2:
	case mAtk3:
	case mAtk4:
	case mAtk5:
	case mAtk6:
		UndoMATKDiff(*this);
		break;
	case mDef0:
	case mDef1:
	case mDef2:
	case mDef3:
	case mDef4:
	case mDef5:
	case mDef6:
		UndoMDEFDiff(*this);
		break;
	case pAtk0:
	case pAtk1:
	case pAtk2:
	case pAtk3:
	case pAtk4:
	case pAtk5:
	case pAtk6:
		UndoPATKDiff(*this);
		break;
	case pDef0:
	case pDef1:
	case pDef2:
	case pDef3:
	case pDef4:
	case pDef5:
	case pDef6:
		UndoPDEFDiff(*this);
		break;
	case immunity0:
	case immunity1:
	case immunity2:
	case immunity3:
	case immunity4:
	case immunity5:
	case immunity6:
		UndoImmunityDiff(*this);
		break;
	case pIncap:
	case mIncap:
		UndoIncapicateDiff(*this);
		break;

	default:
		break;
	}
}


void LifeDrain(MoveEffect &meff, Actor *actor, int healing){
	if(actor == meff.affected)
		meff.TickDamage(GetEffectDamage(meff.id));
	else
		meff.TickHealCaster(GetEffectDamage(meff.id));
}


bool HasEffect(Actor &target, MoveEffect &meff, MoveEffect *match){
	for(auto &it : CombatData::effects[&target]){
		if(it.id == meff.id || it.family == meff.family){
			match = &it;
			return true;
		}
	}

	return false;
}


bool UpdateEffectDuration(Actor &target, MoveEffect &meff){
	//Increase duration if same type of effect or just apply it
	MoveEffect *match = nullptr;
	
	if(HasEffect(target, meff, match)){
		if(meff.duration > match->duration)
			match->duration = meff.duration;
		return true;
	}
	return false;
}


int GetEffectPrimaryDuration(int id){
	int ret = 0;
	switch(id){
	case BLAZE:
		ret = 2;
		break;
	case FIREBALL:
		ret = 3;
		break;
	case EXPLOSION:
		ret = 3;
		break;
	case FIREBEAM:
		ret = 4;
		break;
	case FLAREKICK:
		ret = 3; //For burning
		break;
	case FIREWALL:
		ret = 2; //For burning
		break;
	case SEARINGFLESH:
		ret = 3;
		break;
	case MOLTENMETEOR:
		ret = 3;
		break;
	case WILDFIRE:
		ret = 5;
		break;
	case RAZEEARTH:
		ret = 4;
		break;
	case SUPERNOVA:
		ret = 3;
		break;
	case FLASHFRICTION:
		ret = 3;
		break;
	case SCORCHINGHEAT:
		ret = 3;
		break;
	case DRAGONBREATH:
		ret = 2;
		break;
	case ICARUSINFERNO:
		ret = 5;
		break;
	case TORRENT:
		ret = 2;
		break;
	case TIDALWAVE:
		ret = 3;
		break;
	case WHIRLPOOL:
		ret = 4;
		break;
	case HAILSTORM:
		ret = 2;
		break;
	case AQUAPRISON:
		ret = 3;
		break;
	case RAINSTORM:
		ret = 5;
		break;
	case DEWPOINT:
		ret = 3;
		break;
	case FLASHFREEZE:
		ret = 2;
		break;
	case RIPTIDE:
		ret = 4;
		break;
	case VAPORVORTEX:
		ret = 3;
		break;
	case HELLBROTH:
		ret = 3;
		break;
	case TSUNAMI:
		ret = 5;
		break;
	case SIRENSTEAR:
		ret = 3;
		break;
	case CHILLINGBLAST:
		ret = 2;
		break;
	case ACORNASSAULT:
		ret = 2;
		break;
	case SAPPINGSTEMS:
		ret = 3; //For both on-consume and life drain
		break;
	case NOURISH:
		ret = 3;
		break;
	case LEAFLANCE:
		ret = 2;
		break;
	case FUNGALSPORES:
		ret = 3;
		break;
	case BARBEDHUSK:
		ret = 4;
		break;
	case PETALPIKE:
		ret = 2;
		break;
	case UNDERGROWTH:
		ret = 3; //For not on-consume
		break;
	case SYMBIOSIS:
		ret = 4;
		break;
	case ENSNARINGVINE:
		ret = 3;
		break;
	case RANCIDROSES:
		ret = 3;
		break;
	case DRYADSCURSE:
		ret = 4;
		break;
	case CHARGE:
		ret = 2;
		break;
	case DAZZLINGLIGHTS:
		ret = 1;
		break;
	case LIGHTNINGKICK:
		ret = 2;
		break;
	case SPARKINGSKIN:
		ret = 3;
		break;
	case SUPERCONDUCT:
		ret = 2;
		break;
	case STATICSHOCK:
		ret = 3;
		break;
	case EVANESCENTFIELD:
		ret = 3;
		break;
	case HIGHVOLTAGE:
		ret = 3;
		break;
	case MJOLNIR:
		ret = 3;
		break;
	case CLOSEDCIRUIT:
		ret = 4;
		break;
	case SHARPEN:
		ret = 3;
		break;
	case BALLANDCHAIN:
		ret = 3;
		break;
	case QUICKSILVER:
		ret = 2;
		break;
	case COPPERCUTLASS:
		ret = 2;
		break;
	case RAZORWIRE:
		ret = 2;
		break;
	case MIDASTOUCH:
		ret = 2;
		break;
	case CHROMEPLATED:
		ret = 4;
		break;
	case MAGNETIZE:
		ret = 3;
		break;
	case BRASSKNUCKLES:
		ret = 3;
		break;
	case ALLOYASSAULT:
		ret = 2;
		break;
	case PIERCINGPLATINUM:
		ret = 4;
		break;
	case FORTIFY:
		ret = 3;
		break;
	case QUICKSAND:
		ret = 2;
		break;
	case ENTOMB:
		ret = 3;
		break;
	case OBSIDIANONSLAUGHT:
		ret = 5;
		break;
	case TORMENT:
		ret = 2;
		break;
	case CHAOSCLAW:
		ret = 3;
		break;
	case PHANTOMWALTS:
		ret = 3;
		break;
	case MINDINVASION:
		ret = 3;
		break;
	case BINDINGPAIN:
		ret = 4;
		break;
	case PLAGUE:
		ret = 3;
		break;
	case WICKEDHEX:
		ret = 3;
		break;
	case PETRIFYINGWAIL:
		ret = 3;
		break;
	case DECAY:
		ret = 3;
		break;
	case VIVIDNIGHTMARE:
		ret = 3;
		break;
	case ETHEREALFOG:
		ret = 4;
		break;
	case NOXIOUSVOID:
		ret = 5;
		break;
	case SHADOWSLASH:
		ret = 2;
		break;
	default:
		break;
	}

	return ret;
}


int GetEffectSecondaryDuration(int id){
	int ret = 0;
	switch(id){
	case FLAREKICK:
		ret = 2; //For taunting
		break;
	case FIREWALL:
		ret = 3; //For uptime
		break;
	case UNDERGROWTH:
		ret = 4; //For on-consume
		break;
	case ENSNARINGVINE:
		ret = 2;
		break;
	case RANCIDROSES:
		ret = 2;
		break;
	case DAZZLINGLIGHTS:
		ret = 1;
		break;
	case EVANESCENTFIELD:
		ret = 2;
		break;
	case HIGHVOLTAGE:
		ret = 3;
		break;
	case CLOSEDCIRUIT:
		ret = 2;
		break;
	case QUICKSILVER:
		ret = 3;
		break;
	case MINDINVASION:
		ret = 2; //For incap
		break;
	case PETRIFYINGWAIL:
		ret = 2; //For incap
		break;
	case DECAY:
		ret = 3; //For decay
		break;
	case VIVIDNIGHTMARE:
		ret = 2; //For incap
		break;
	case ETHEREALFOG:
		ret = 4;
		break;
	default:
		break;
	}

	return ret;
}


int GetEffectDamage(int id){
	int ret = 0;
	switch(id){
	case FIREBALL:
		ret = 10;
		break;
	case EXPLOSION:
		ret = 10;
		break;
	case FIREBEAM:
		ret = 10;
		break;
	case FLAMESWORD:
		ret = 10;
		break;
	case FLAREKICK:
		ret = 10;
		break;
	case FIREWALL:
		ret = 10;
		break;
	case MOLTENMETEOR:
		ret = 10;
		break;
	case WILDFIRE:
		ret = 20;
		break;
	case RAZEEARTH:
		ret = 10;
		break;
	case SUPERNOVA:
		ret = 10;
		break;
	case FLASHFRICTION:
		ret = 10;
		break;
	case SCORCHINGHEAT:
		ret = 10;
		break;
	case ICARUSINFERNO:
		ret = 10;
		break;
	case SAPPINGSTEMS:
		ret = 15;
		break;
	case FUNGALSPORES:
		ret = 10;
		break;
	case DRYADSCURSE:
		ret = 15;
		break;
	case BALLANDCHAIN:
		ret = 10;
		break;
	case COPPERCUTLASS:
		ret = 10;
		break;
	case RAZORWIRE:
		ret = 10;
		break;
	case PIERCINGPLATINUM:
		ret = 10;
		break;
	default:
		break;
	}

	return ret;
}


float GetEffectHeal(int id){
	float ret = 0;
	switch(id){
	default:
		break;
	}

	return ret;
}


float GetEffectPrimaryBuff(int id){
	float ret = 1.f;
	switch(id){
	case BLAZE:
		ret = 1.25f;
		break;
	case FIREWALL:
		ret = 2.f;
		break;
	case SEARINGFLESH:
		ret = .5f; //Apply to Fire damage
		break;
	case RAINSTORM:
		ret = .5f;
		break;
	case DEWPOINT:
		ret = .5f;
		break;
	case SAPPINGSTEMS:
		ret = .5f;
		break;
	case NOURISH:
		ret = 1.25f;
		break;
	case CHARGE:
		ret = 1.25f;
		break;
	case SPARKINGSKIN:
		ret = .5f;
		break;
	case HIGHVOLTAGE:
		ret = .75f;
		break;
	case SHARPEN:
		ret = 1.25f;
		break;
	case CHROMEPLATED:
		ret = 1.25f;
		break;
	case MAGNETIZE:
		ret = .25f;
		break;
	case BRASSKNUCKLES:
		ret = .25f;
		break;
	case FORTIFY:
		ret = .01f;
		break;
	case SAPPHIRESTRIKE:
		ret = .5f;
		break;
	case RUBYRUSH:
		ret = .5f;
		break;
	case EMERALDEDGE:
		ret = .5f;
		break;
	case PHANTOMWALTS:
		ret = 1.5f;
		break;
	case BARBEDHUSK:
		ret = 0.15f;
		break;
	case QUICKSILVER:
		ret = 54.f;
		break;
	default:
		break;
	}

	return ret;
}


float GetEffectSecondaryBuff(int id){
	float ret = 1.f;
	switch(id){
	case SEARINGFLESH:
		ret = 0.75f; //Apply to Fire move cost
		break;
	default:
		break;
	}

	return ret;
}


float GetEffectPrimaryDebuff(int id){
	float ret = 1.f;
	switch(id){
	case RAZEEARTH:
		/* ret = 0.85f; */
		ret = 0.15f;
		break;
	case RIPTIDE:
		ret = 0.25f;
		break;
	case DRAGONBREATH:
		ret = 0.15f; //Subtract from mp gained
		break;
	case BRASSKNUCKLES:
		ret = 0.15f; //Subtract from damage out
		break;
	case QUICKSAND:
		ret = 0.15f; //Subtract from defence
		break;
	case OBSIDIANONSLAUGHT:
		ret = 1.1875f;
		break;
	case TORMENT:
		ret = 0.85f;
		break;
	case CHAOSCLAW:
		ret = 0.85f;
		break;
	case MINDINVASION:
		ret = 0.85f;
		break;
	case BINDINGPAIN:
		ret = 0.85f;
		break;
	case WICKEDHEX:
		ret = 0.85f;
		break;
	case DECAY:
		ret = 0.85f;
		break;
	case NOXIOUSVOID:
		ret = 0.85f;
		break;
	default:
		break;
	}

	return ret;
}


float GetEffectSecondaryDebuff(int id){
	float ret = 1.f;
	switch(id){
	default:
		break;
	}

	return ret;
}


void ApplyEffectDiff(Actor &actor, MoveEffect &meff){
	return;
}


void ApplyMaxHPDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //Assign the diff
	ediff.prev = actor.maxHP;
	actor.maxHP += ediff.diff;
	actor.remHP = (int) ceil(((float) actor.remHP / ediff.prev) * actor.maxHP);
	ediff.curr = actor.maxHP;
}


void ApplyMaxMPDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //Assign the diff
	ediff.prev = actor.maxMP;
	actor.maxMP += ediff.diff;
	actor.remMP = (int) ceil(((float) actor.remMP / ediff.prev) * actor.maxMP);
	ediff.curr = actor.maxMP;
}



void ApplyMATKDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff;
	int elem = ediff.stat - EffectDiff::Stat::mAtk0; //Element with fire indexed at 0
	ediff.prev = actor.mAtk[elem];
	actor.mAtk[elem] += ediff.diff; //TODO: test me!
	ediff.curr = actor.mAtk[elem];
}


void ApplyMDEFDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff;
	int elem = ediff.stat - EffectDiff::Stat::mDef0; //Element with fire indexed at 0
	ediff.prev = actor.mDef[elem];
	actor.mDef[elem] += ediff.diff; //TODO: test me!
	ediff.curr = actor.mDef[elem];
}


void ApplyPATKDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff;
	int elem = ediff.stat - EffectDiff::Stat::pAtk0; //Element with fire indexed at 0
	ediff.prev = actor.pAtk[elem];
	actor.pAtk[elem] += ediff.diff; //TODO: test me!
	ediff.curr = actor.pAtk[elem];
}


void ApplyPDEFDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff;
	int elem = ediff.stat - EffectDiff::Stat::pDef0; //Element with fire indexed at 0
	ediff.prev = actor.pDef[elem];
	actor.pDef[elem] += ediff.diff; //TODO: test me!
	ediff.curr = actor.pDef[elem];
}


void ApplyImmunityDiff(Actor &actor, EffectDiff &ediff, int &diff){
	if(ediff.stat == EffectDiff::Stat::immunityP || ediff.stat == EffectDiff::Stat::immunityM){
		ediff.affected = &actor;
		ediff.diff = diff; //diff == 0 == false, diff == 1 == true
		int physOrMeta = ediff.stat - EffectDiff::Stat::immunityP + 7;

		ediff.prev = (int)CombatData::statusEffects[&actor].immune[physOrMeta];
		CombatData::statusEffects[&actor].immune[physOrMeta] = (bool)ediff.diff; //TODO: test me!
		ediff.curr = (int)CombatData::statusEffects[&actor].immune[physOrMeta];
	}
	else{
		ediff.affected = &actor;
		ediff.diff = diff; //diff == 0 == false, diff == 1 == true
		int elem = ediff.stat - EffectDiff::Stat::immunity0; //Element with fire indexed at 0

		ediff.prev = (int)CombatData::statusEffects[&actor].immune[elem];
		CombatData::statusEffects[&actor].immune[elem] = (bool)ediff.diff; //TODO: test me!
		ediff.curr = (int)CombatData::statusEffects[&actor].immune[elem];
	}
}


void ApplyIncapicateDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //diff == 0 == false, diff == 1 == true
	if(ediff.stat == EffectDiff::Stat::pIncap){
		ediff.prev = (int)CombatData::statusEffects[&actor].incaps[0];
		CombatData::statusEffects[&actor].incaps[0] = (bool)ediff.diff; //TODO: test me!
		ediff.curr = (int)CombatData::statusEffects[&actor].incaps[0];
	}
	else{
		ediff.prev = (int)CombatData::statusEffects[&actor].incaps[1];
		CombatData::statusEffects[&actor].incaps[1] = (bool)ediff.diff; //TODO: test me!
		ediff.curr = (int)CombatData::statusEffects[&actor].incaps[1];
	}
}


void ApplyDisableDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //diff == 0 == false, diff == 1 == true
	ediff.prev = (int)CombatData::statusEffects[&actor].disable;
	CombatData::statusEffects[&actor].disable = (bool)ediff.diff; //TODO: test me!
	ediff.curr = (int)CombatData::statusEffects[&actor].disable;
}


void ApplyTypeDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //diff == 0 == false, diff == 1 == true

	int type0 = (ediff.diff >> 16) << 16;
	int type1 = ediff.diff << 16;
	
	int prev = actor.type[0] & (actor.type[1] >> 16);
	ediff.prev = prev;

	actor.type[0] = (Element)type0;
	actor.type[1] = (Element)type1;

	int curr = actor.type[0] & (actor.type[1] >> 16);
	ediff.curr = curr;
}


void ApplyHPBonusDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //Assign the diff
	ediff.prev = actor.hpBonus;

	int prevMaxHP = actor.maxHP;
	actor.hpBonus += ediff.diff;
	actor.maxHP = (int) ceil(INITHP * (1.0f + HPMPBONUS_MULT * actor.hpBonus));
	actor.remHP = (int) ceil(((float) actor.remHP / prevMaxHP) * actor.maxHP);
	
	ediff.curr = actor.hpBonus;
}


void ApplyMPBonusDiff(Actor &actor, EffectDiff &ediff, int &diff){
	ediff.affected = &actor;
	ediff.diff = diff; //Assign the diff
	ediff.prev = actor.mpBonus;

	int prevMaxMP = actor.maxMP;
	actor.mpBonus += ediff.diff;
	actor.maxMP = (int) ceil(INITMP * (1.0f + HPMPBONUS_MULT * actor.mpBonus));
	actor.remMP = (int) ceil(((float) actor.remMP / prevMaxMP) * actor.maxMP);
	
	ediff.curr = actor.mpBonus;
}


void UndoMaxHPDiff(EffectDiff &ediff){
	int prevMaxHP = ediff.affected->maxHP;
	ediff.affected->maxHP -= ediff.diff;
	ediff.affected->remHP = (int) ceil(((float) ediff.affected->remHP / prevMaxHP) * ediff.affected->maxHP);
}


void UndoMaxMPDiff(EffectDiff &ediff){
	int prevMaxMP = ediff.affected->maxMP;
	ediff.affected->maxMP -= ediff.diff;
	ediff.affected->remMP = (int) ceil(((float) ediff.affected->remMP / prevMaxMP) * ediff.affected->maxMP);
}


void UndoMATKDiff(EffectDiff &ediff){
	int elem = ediff.stat - EffectDiff::Stat::mAtk0; //Element with fire indexed at 0
	ediff.affected->mAtk[elem] -= ediff.diff;
}


void UndoMDEFDiff(EffectDiff &ediff){
	int elem = ediff.stat - EffectDiff::Stat::mDef0; //Element with fire indexed at 0
	ediff.affected->mDef[elem] -= ediff.diff;
}


void UndoPATKDiff(EffectDiff &ediff){
	int elem = ediff.stat - EffectDiff::Stat::pAtk0; //Element with fire indexed at 0
	ediff.affected->pAtk[elem] -= ediff.diff;
}


void UndoPDEFDiff(EffectDiff &ediff){
	int elem = ediff.stat - EffectDiff::Stat::pDef0; //Element with fire indexed at 0
	ediff.affected->pDef[elem] -= ediff.diff;
}


void UndoImmunityDiff(EffectDiff &ediff){
	int elem = ediff.stat - EffectDiff::Stat::immunity0; //Element with fire indexed at 0
	/* ediff.affected->immune[elem] = (bool)ediff.prev; */
	CombatData::statusEffects[ediff.affected].immune[elem] = (bool)ediff.prev;
}


void UndoIncapicateDiff(EffectDiff &ediff){
	//TODO: Optimize by just getting a pointer to the incap arr and add the mult of stat == pIncap
	if(ediff.stat == EffectDiff::Stat::pIncap)
		CombatData::statusEffects[ediff.affected].incaps[0] = (bool)ediff.prev;
	else
		CombatData::statusEffects[ediff.affected].incaps[1] = (bool)ediff.prev;
}


void UndoDisableDiff(EffectDiff &ediff){
	CombatData::statusEffects[ediff.affected].disable = (bool)ediff.prev;
}


void UndoTypeDiff(EffectDiff &ediff){
	int type0 = (ediff.prev >> 16) << 16;
	int type1 = ediff.prev << 16;
	ediff.affected->type[0] = (Element)type0;
	ediff.affected->type[1] = (Element)type1;
}


void UndoHPBonusDiff(EffectDiff &ediff){
	int prevMaxHP = ediff.affected->maxHP;
	ediff.affected->hpBonus -= ediff.diff;
	ediff.affected->maxHP = (int) ceil(INITHP * (1.0f + HPMPBONUS_MULT * ediff.affected->hpBonus));
	ediff.affected->remHP = (int) ceil(((float) ediff.affected->remHP / prevMaxHP) * ediff.affected->maxHP);
}


void UndoMPBonusDiff(EffectDiff &ediff){
	int prevMaxMP = ediff.affected->maxMP;
	ediff.affected->mpBonus -= ediff.diff;
	ediff.affected->maxMP = (int) ceil(INITMP * (1.0f + HPMPBONUS_MULT * ediff.affected->mpBonus));
	ediff.affected->remMP = (int) ceil(((float) ediff.affected->remMP / prevMaxMP) * ediff.affected->maxMP);
}

