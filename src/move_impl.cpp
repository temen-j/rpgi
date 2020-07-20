#include "..\include\move_impl.h"
#include "..\include\actor.h"
#include "..\include\move.h"
#include "..\include\combat.h"

inline EffectDiff *AllocEDiff(){
	return static_cast<EffectDiff *>(MemPoolAlloc(&CombatData::diffMemPool, sizeof(EffectDiff)));
}

inline EffectDiff *AllocEDiff(size_t size){ //WARNING: Make the assumption that size > 0
	return static_cast<EffectDiff *>(MemPoolAlloc(&CombatData::diffMemPool, size * sizeof(EffectDiff)));
}


void MoveImplementation::IGNITE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}

//NOTE: July 5, 2020. This code uses vector<>::emplace_back() b/c when temp goes out of scope
//it will call the destructor and free the shared diffs if it were just pushed_back()

void MoveImplementation::BLAZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::FIREBALL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::EXPLOSION(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::FIREBEAM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::FLAMESWORD(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}
	ApplyCost(cm);
}


void MoveImplementation::FLAREKICK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);
	temp2.family = MoveEffect::Family::taunted;

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::taunted;
	}

	ApplyCost(cm);
}


void MoveImplementation::FIREWALL(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::SEARINGFLESH(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::immunity0;
		int temp = (int)true;
		ApplyImmunityDiff(target, *meff.diffs, temp);
	}
	
	ApplyCost(cm);
}


void MoveImplementation::MOLTENMETEOR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::WILDFIRE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::RAZEEARTH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm); //ApplyDamage before effects?????
	//God im so fuckin tired of this shit, i have no idea

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::FROMTHEASHES(Actor &target, CasterMove &cm){
	ApplyHeal(target, cm);

	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].family == MoveEffect::Family::burning){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}

	if(consumed){
		int fireCount = 0;
		for(size_t i = 0; i < NUMGRIDS; ++i){
			for(size_t j = 0; j < NUMCELLS; ++j){
				if(target.grids[i][j] == Element::fire)
					fireCount++;
				if(cm.caster->grids[i][j] == Element::fire)
					fireCount++;
			}
		}
		
		float percentHealed = 0.1f * (2 * fireCount); //As defined by the design doc
		//FIXME: magic numbers
		int amtHealed = (int) ceil(target.maxHP * percentHealed);
		
		target.remHP += amtHealed;
		if(target.remHP > target.maxHP)
			target.remHP = target.maxHP;
	}
	
	ApplyCost(cm);
}


void MoveImplementation::SUPERNOVA(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::WATERWHIP(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::TORRENT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);
	
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	ApplyCost(cm);
}


void MoveImplementation::TIDALWAVE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	ApplyCost(cm);
}


void MoveImplementation::COALESCE(Actor &target, CasterMove &cm){
	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].family == MoveEffect::Family::wet){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}

	if(consumed){
		float baseHeal = .15f;

		int waterCount = 0;
		for(size_t i = 0; i < NUMGRIDS; ++i){
			for(size_t j = 0; j < NUMGRIDS; ++j){
				if(target.grids[i][j] == Element::water)
					waterCount++;
				if(cm.caster->grids[i][j] == Element::water)
					waterCount++;
			}
		}
		
		float percentHealed = baseHeal + 0.05f * (waterCount); //Explicity this as defined by the design doc
		//FIXME: magic numbers
		int amtHealed = (int) ceil(target.maxHP * percentHealed);
		
		target.remHP += amtHealed;
		if(target.remHP > target.maxHP)
			target.remHP = target.maxHP;
	}

	ApplyCost(cm);
}


void MoveImplementation::WHIRLPOOL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	ApplyCost(cm);
}


void MoveImplementation::HAILSTORM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].family == MoveEffect::Family::wet){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}
	
	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);
		temp.family = MoveEffect::Family::frozen;

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
			meff.family = MoveEffect::Family::frozen;

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::disabled;
			int temp = (int)true;
			ApplyDisableDiff(target, *meff.diffs, temp); 
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::AQUAPRISON(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectSecondaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectSecondaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::pIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::RAINSTORM(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::DEWPOINT(Actor &target, CasterMove &cm){
	//FIXME: Apply % heal?
	
	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].family == MoveEffect::Family::wet){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
		}
	}
	

	ApplyCost(cm);
}


void MoveImplementation::FLASHFREEZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].family == MoveEffect::Family::wet){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);
		temp.family = MoveEffect::Family::frozen;

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
			meff.family = MoveEffect::Family::frozen;
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::RIPTIDE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	ApplyCost(cm);
}


void MoveImplementation::VAPORVORTEX(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::mIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}
	
	ApplyCost(cm);
}


void MoveImplementation::HELLBROTH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].family == MoveEffect::Family::wet){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}
	if(consumed){
		//Loop through and count water minoes from 1st and 2nd grid
		int waterCount[2] = {0, 0};
		for(size_t j = 0; j < NUMCELLS; ++j){
			if(target.grids[0][j] == Element::water)
				waterCount[0]++;
			if(target.grids[2][j] == Element::water)
				waterCount[1]++;
		}
		
		int waterDiff[2] = {waterCount[0] * -1, waterCount[1] * -1};

		//Apply negative effect to victim
		MoveEffect temp(cm.move->id); //victim
		temp.duration = GetEffectPrimaryDuration(temp.id);

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);

			meff.diffs = AllocEDiff(4);
			meff.diffs[0].stat = EffectDiff::Stat::mAtk1;
			meff.diffs[1].stat = EffectDiff::Stat::mDef1;
			meff.diffs[2].stat = EffectDiff::Stat::pAtk1;
			meff.diffs[3].stat = EffectDiff::Stat::mpBonus;

			ApplyMATKDiff(target, meff.diffs[0], waterDiff[0]);
			ApplyMDEFDiff(target, meff.diffs[1], waterDiff[0]);
			ApplyPATKDiff(target, meff.diffs[2], waterDiff[1]);
			ApplyMPBonusDiff(target, meff.diffs[3], waterDiff[1] *= MPBONUS_WATER);
		}
		
		//Apply positive effect to thief
		MoveEffect temp2(cm.move->id); //thief
		temp2.duration = GetEffectPrimaryDuration(temp2.id);

		if(!UpdateEffectDuration(*cm.caster, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);

			meff.diffs = AllocEDiff(4);
			meff.diffs[0].stat = EffectDiff::Stat::mAtk1;
			meff.diffs[1].stat = EffectDiff::Stat::mDef1;
			meff.diffs[2].stat = EffectDiff::Stat::pAtk1;
			meff.diffs[3].stat = EffectDiff::Stat::mpBonus;

			ApplyMATKDiff(*cm.caster, meff.diffs[0], waterCount[0]);
			ApplyMDEFDiff(*cm.caster, meff.diffs[1], waterCount[0]);
			ApplyPATKDiff(*cm.caster, meff.diffs[2], waterCount[1]);
			ApplyMPBonusDiff(*cm.caster, meff.diffs[3], waterCount[1] *= MPBONUS_WATER);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::TSUNAMI(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);
	
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::wet;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::wet;
	}

	ApplyCost(cm);
}


void MoveImplementation::SEEDSHOT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::ACORNASSAULT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::florid;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::florid;
	}

	ApplyCost(cm);
}


void MoveImplementation::SAPPINGSTEMS(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::lifeDrain;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::lifeDrain;
		meff.affector = cm.caster;
		meff.affected = &target;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		bool consumed = false;
		for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
			if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::florid){
				consumed = true;
				CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
				break;
			}
		}
		if(consumed){
			CombatData::effects[cm.caster].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[cm.caster].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::NOURISH(Actor &target, CasterMove &cm){
	ApplyHeal(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::florid;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::florid;
	}

	ApplyCost(cm);
}


void MoveImplementation::LEAFLANCE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::florid){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);
		temp.family = MoveEffect::Family::lifeDrain;

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
			meff.family = MoveEffect::Family::lifeDrain;
			meff.affector = cm.caster;
			meff.affected = &target;
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::FUNGALSPORES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::poisoned;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::poisoned;
	}

	ApplyCost(cm);
}


void MoveImplementation::BARBEDHUSK(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::GRASSBLADES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::PETALPIKE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::florid;

	if(!UpdateEffectDuration(*cm.caster, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::florid;
	}

	ApplyCost(cm);
}


void MoveImplementation::UNDERGROWTH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::florid){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(!consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);
		temp.family = MoveEffect::Family::lifeDrain;

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
			meff.family = MoveEffect::Family::lifeDrain;
			meff.affector = cm.caster;
			meff.affected = &target;
		}
	}
	else{
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectSecondaryDuration(temp.id);
		temp.family = MoveEffect::Family::lifeDrain;

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);
			meff.family = MoveEffect::Family::lifeDrain;
			meff.affector = cm.caster;
			meff.affected = &target;
		}
	}


	ApplyCost(cm);
}


void MoveImplementation::SYMBIOSIS(Actor &target, CasterMove &cm){
	ApplyHeal(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::florid;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::florid;
	}

	ApplyCost(cm);
}


void MoveImplementation::ENSNARINGVINE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	//FIXME: Dont't really like taunted, maybe slow?
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::taunted;

	if(!UpdateEffectDuration(*cm.caster, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::taunted;
	}
	
	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::florid){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp2(cm.move->id);
		temp2.duration = GetEffectSecondaryDuration(temp2.id);

		if(!UpdateEffectDuration(target, temp2)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::pIncap;
			int temp = (int)true;
			ApplyIncapicateDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::RANCIDROSES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::feared;

	if(!UpdateEffectDuration(*cm.caster, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::feared;
	}
	
	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::florid){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp2(cm.move->id);
		temp2.duration = GetEffectSecondaryDuration(temp2.id);

		if(!UpdateEffectDuration(target, temp2)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::mIncap;
			int temp = (int)true;
			ApplyIncapicateDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::DRYADSCURSE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::lifeDrain;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::lifeDrain;
		meff.affector = cm.caster;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::ZAP(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::CHARGE(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::charged;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::charged;
	}

	ApplyCost(cm);
}


void MoveImplementation::DISCHARGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::LIGHTNINGBOLT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::DAZZLINGLIGHTS(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::taunted;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::taunted;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::pIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::ELECTROSTORM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::LIGHTNINGKICK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::charged){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectSecondaryDuration(temp.id);

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::disabled;
			int temp = (int)true;
			ApplyDisableDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::SPARKINGSKIN(Actor &target, CasterMove &cm){
	//It doesn't make much sense to hurt and heal the actor in the same move
	/* ApplyDamage(target, cm); */
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::SUPERCONDUCT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::charged){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::disabled;
			int temp = (int)true;
			ApplyDisableDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::STATICSHOCK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::pIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::EVANESCENTFIELD(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::charged;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::charged;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectSecondaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectSecondaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::immunity3;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::HIGHVOLTAGE(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::charged;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::charged;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectSecondaryDuration(temp2.id);
	temp2.family = MoveEffect::Family::efficient;

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectSecondaryDuration(meff.id);
		meff.family = MoveEffect::Family::efficient;
	}

	ApplyCost(cm);
}


void MoveImplementation::MJOLNIR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::charged){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(temp.id);

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::disabled;
			int temp = (int)true;
			ApplyDisableDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::CLOSEDCIRUIT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::pIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::charged){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp2(cm.move->id);
		temp2.duration = GetEffectPrimaryDuration(temp2.id);

		if(!UpdateEffectDuration(target, temp2)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::disabled;
			int temp = (int)true;
			ApplyDisableDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::IRONSPIKES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::CANNONBALL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SHARPEN(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::sharpened;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::sharpened;
	}

	ApplyCost(cm);
}


void MoveImplementation::SHATTERSHRAPNEL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::BALLANDCHAIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::sharpened;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::sharpened;
	}

	ApplyCost(cm);
}


void MoveImplementation::QUICKSILVER(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::sharpened;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::sharpened;
	}

	MoveEffect temp2(cm.move->id); //TODO: Implement priority decrease
	temp2.duration = GetEffectSecondaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectSecondaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::COPPERCUTLASS(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::corroding;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::corroding;
	}

	ApplyCost(cm);
}


void MoveImplementation::RAZORWIRE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::corroding;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::corroding;
	}

	ApplyCost(cm);
}


void MoveImplementation::MIDASTOUCH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::mIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::CHROMEPLATED(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::MAGNETIZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);
	
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(*cm.caster, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::BRASSKNUCKLES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::ALLOYASSAULT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	//Loop through and count metal minoes from 1st and 2nd grid
	int metalCount[2] = {0, 0};
	for(size_t j = 0; j < NUMCELLS; ++j){
		if(target.grids[0][j] == Element::metal)
			metalCount[0]++;
		if(target.grids[1][j] == Element::metal)
			metalCount[1]++;
	}
	
	int metalDiff[2] = {metalCount[0] * -1, metalCount[1] * -1};

	//Apply negative effect to victim
	MoveEffect temp(cm.move->id); //victim
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff(4);
		meff.diffs[0].stat = EffectDiff::Stat::mAtk5;
		meff.diffs[1].stat = EffectDiff::Stat::mDef5;
		meff.diffs[2].stat = EffectDiff::Stat::pDef5;
		meff.diffs[3].stat = EffectDiff::Stat::hpBonus;

		ApplyMATKDiff(target, meff.diffs[0], metalDiff[0]);
		ApplyMDEFDiff(target, meff.diffs[1], metalDiff[0]);
		ApplyPDEFDiff(target, meff.diffs[2], metalDiff[1]);
		ApplyHPBonusDiff(target, meff.diffs[3], metalDiff[1] *= HPBONUS_METAL);
	}
	
	//Apply positive effect to thief
	MoveEffect temp2(cm.move->id); //thief
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(*cm.caster, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff(4);
		meff.diffs[0].stat = EffectDiff::Stat::mAtk5;
		meff.diffs[1].stat = EffectDiff::Stat::mDef5;
		meff.diffs[2].stat = EffectDiff::Stat::pDef5;
		meff.diffs[3].stat = EffectDiff::Stat::hpBonus;

		ApplyMATKDiff(*cm.caster, meff.diffs[0], metalCount[0]);
		ApplyMDEFDiff(*cm.caster, meff.diffs[1], metalCount[0]);
		ApplyPDEFDiff(*cm.caster, meff.diffs[2], metalCount[1]);
		ApplyHPBonusDiff(*cm.caster, meff.diffs[3], metalCount[1] *= HPBONUS_METAL);
	}

	ApplyCost(cm);
}


void MoveImplementation::PIERCINGPLATINUM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::corroding;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::corroding;
	}

	ApplyCost(cm);
}


void MoveImplementation::HURLROCK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::STONESPEAR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::FORTIFY(Actor &target, CasterMove &cm){
	int total = 0;
	for(size_t j = 0; j < NUMCELLS; ++j){
		if(target.grids[0][j] == Element::rock)
			total++;
		if(target.grids[1][j] == Element::rock)
			total++;
		if(target.grids[2][j] == Element::rock)
			total++;
	}

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);


	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->curr = 2 * total; //As defined in the design doc
	}

	ApplyCost(cm);
}


void MoveImplementation::QUICKSAND(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::ENTOMB(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::pIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::CRUSH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::TREMOR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::ROCKSLIDE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::ROLLINGBOULDER(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SAPPHIRESTRIKE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::RUBYRUSH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::GARNETGAZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	int rockCount[2] = {0, 0};
	for(size_t j = 0; j < NUMCELLS; ++j){
		if(target.grids[0][j] == Element::rock)
			rockCount[1]++;
		if(target.grids[1][j] == Element::rock)
			rockCount[2]++;
	}
	
	int rockDiff[2] = {rockCount[0] * -1, rockCount[1] * -1};

	//Apply negative effect to victim
	MoveEffect temp(cm.move->id); //victim
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff(4);
		meff.diffs[0].stat = EffectDiff::Stat::pDef5;
		meff.diffs[1].stat = EffectDiff::Stat::hpBonus;
		meff.diffs[2].stat = EffectDiff::Stat::pAtk5;
		meff.diffs[3].stat = EffectDiff::Stat::mpBonus;

		ApplyPDEFDiff(target, meff.diffs[0], rockDiff[0]);
		ApplyHPBonusDiff(target, meff.diffs[1], rockDiff[0] *= HPBONUS_METAL);
		ApplyPATKDiff(target, meff.diffs[2], rockDiff[1]);
		ApplyMPBonusDiff(target, meff.diffs[3], rockDiff[1] *= MPBONUS_METAL);
	}
	
	//Apply positive effect to thief
	MoveEffect temp2(cm.move->id); //thief
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(*cm.caster, temp)){
		CombatData::effects[cm.caster].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[cm.caster].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);

		meff.diffs = AllocEDiff(4);
		meff.diffs[0].stat = EffectDiff::Stat::pDef5;
		meff.diffs[1].stat = EffectDiff::Stat::hpBonus;
		meff.diffs[2].stat = EffectDiff::Stat::pAtk5;
		meff.diffs[3].stat = EffectDiff::Stat::mpBonus;

		ApplyPDEFDiff(*cm.caster, meff.diffs[0], rockDiff[0]);
		ApplyHPBonusDiff(*cm.caster, meff.diffs[1], rockDiff[0] *= HPBONUS_METAL);
		ApplyPATKDiff(*cm.caster, meff.diffs[2], rockDiff[1]);
		ApplyMPBonusDiff(*cm.caster, meff.diffs[3], rockDiff[1] *= MPBONUS_METAL);
	}

	ApplyCost(cm);
}


void MoveImplementation::EMERALDEDGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::OBSIDIANONSLAUGHT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::brittle;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::brittle;
	}

	ApplyCost(cm);
}


void MoveImplementation::ECTORAY(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::TORMENT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	ApplyCost(cm);
}


void MoveImplementation::CHAOSCLAW(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	ApplyCost(cm);
}


void MoveImplementation::PHANTOMWALTS(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::supernatural;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::supernatural;
	}

	ApplyCost(cm);
}


void MoveImplementation::GRAVETENDER(Actor &target, CasterMove &cm){

	//TODO: implement adding characters to the team
	ApplyCost(cm);
}


void MoveImplementation::MINDINVASION(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectSecondaryDuration(meff.id);

		meff.diffs = AllocEDiff();
		meff.diffs->stat = EffectDiff::Stat::mIncap;
		int temp = (int)true;
		ApplyIncapicateDiff(target, *meff.diffs, temp);
	}

	ApplyCost(cm);
}


void MoveImplementation::BINDINGPAIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	ApplyCost(cm);
}


void MoveImplementation::PLAGUE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	ApplyCost(cm);
}


void MoveImplementation::WICKEDHEX(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	ApplyCost(cm);
}


void MoveImplementation::PETRIFYINGWAIL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::supernatural){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp2(cm.move->id);
		temp2.duration = GetEffectPrimaryDuration(temp2.id);

		if(!UpdateEffectDuration(target, temp2)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::pIncap;
			int temp = (int)true;
			ApplyIncapicateDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::DECAY(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	ApplyCost(cm);
}


void MoveImplementation::VIVIDNIGHTMARE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::supernatural){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp2(cm.move->id);
		temp2.duration = GetEffectPrimaryDuration(temp2.id);

		if(!UpdateEffectDuration(target, temp2)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::mIncap;
			int temp = (int)true;
			ApplyIncapicateDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::ETHEREALFOG(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[cm.caster].size(); ++i){
		if(CombatData::effects[cm.caster][i].family == MoveEffect::Family::supernatural){
			consumed = true;
			CombatData::effects[cm.caster].erase(CombatData::effects[cm.caster].begin() + i);
			break;
		}
	}

	if(consumed){
		MoveEffect temp2(cm.move->id);
		temp2.duration = GetEffectPrimaryDuration(temp2.id);

		if(!UpdateEffectDuration(*cm.caster, temp2)){
			CombatData::effects[cm.caster].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[cm.caster].back();
			meff.duration = GetEffectSecondaryDuration(meff.id);

			meff.diffs = AllocEDiff();
			meff.diffs->stat = EffectDiff::Stat::immunityM;
			int temp = (int)true;
			ApplyImmunityDiff(target, *meff.diffs, temp);
		}
	}

	ApplyCost(cm);
}


void MoveImplementation::NOXIOUSVOID(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::cursed;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::cursed;
	}

	ApplyCost(cm);
}


void MoveImplementation::FLASHFRICTION(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::SCORCHINGHEAT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::DRAGONBREATH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::manaburn;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::manaburn;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::ICARUSINFERNO(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::burning;

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
		meff.family = MoveEffect::Family::burning;
		meff.affected = &target;
	}

	ApplyCost(cm);
}


void MoveImplementation::REND(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SIRENSTEAR(Actor &target, CasterMove &cm){

	ApplyCost(cm);
}


void MoveImplementation::CHILLINGBLAST(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::DELUGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::NEEDLE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::BLOOM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::TREECLEAVER(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::VENOMCOATING(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SURGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::OVERLOAD(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::IONSTRIKE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::PLASMAPULSE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SCRAPSLUG(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::ANNEAL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::ANODIZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::GALVANIZEDGLAIVE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::GRAVELSPIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SANDBOMB(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::CRYSTALCAGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::FISSURE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::SHADOWSLASH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::PILFER(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void MoveImplementation::BLOODCURDLE(Actor &target, CasterMove &cm){

	ApplyCost(cm);
}


void MoveImplementation::BLACKHOLE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	ApplyCost(cm);
}


void ApplyDamage(Actor &target, CasterMove &cm){

	if(CombatData::statusEffects[&target].immune[cm.move->elem-1]) //FIXME: May have to be more verbose
		return;

	if(CombatData::statusEffects[&target].immune[cm.move->isPhysical + 7]) //FIXME: May have to be more verbose
		return;

	int dmg = cm.move->damage;
	float effectiveness = Effectiveness(cm.move->elem, target.type);
	dmg = (int) ceil(dmg * effectiveness);

	//Apply the proportional bonus damage if an effect requires it
	bool applyBonus = false;
	float bonus = 0.0f;
	for(auto &it : CombatData::effects[cm.caster]){ //TODO: turn this into a function
		switch(it.id){
		case SEARINGFLESH:
			bonus += (GetEffectPrimaryBuff(it.id) * (cm.move->elem == Element::fire)); //Hacky!!!
			applyBonus = applyBonus || cm.move->elem == Element::fire;
			break;
		case RAINSTORM:
			bonus += (GetEffectPrimaryBuff(it.id) * (cm.move->elem == Element::water)); //Hacky!!!
			applyBonus = applyBonus || cm.move->elem == Element::water;
			break;
		case SAPPINGSTEMS:
			bonus += (GetEffectPrimaryBuff(it.id) * (cm.move->elem == Element::nature)); //Hacky!!!
			applyBonus = applyBonus || cm.move->elem == Element::nature;
			break;
		case SAPPHIRESTRIKE:
			bonus += (GetEffectPrimaryBuff(it.id) * (target.remHP > (target.maxHP / 2)));
			applyBonus = applyBonus || (target.remHP > (target.maxHP / 2));
			break;
		case RUBYRUSH:
			bonus += (GetEffectPrimaryBuff(it.id) * (target.remHP > (target.maxHP / 2)));
			applyBonus = applyBonus || (target.remHP > (target.maxHP / 2));
			break;
		case EMERALDEDGE:
			bonus += (GetEffectPrimaryBuff(it.id) * (target.remHP > (target.maxHP / 2)));
			applyBonus = applyBonus || (target.remHP > (target.maxHP / 2));
			break;
		default:
			break;
		}
		switch(it.family){
		case MoveEffect::Family::charged:
			bonus += (CHARGED_BUFF_BONUS * (cm.move->elem == Element::lightning)); //Hacky!!!
			applyBonus = applyBonus || cm.move->elem == Element::lightning;
			break;
		case MoveEffect::Family::sharpened:
			bonus += (SHARPENED_BUFF_BONUS * (cm.move->elem == Element::metal)); //Hacky!!!
			applyBonus = applyBonus || cm.move->elem == Element::lightning;
		default:
			break;
		}
	}
	if(applyBonus)
		dmg = (int) ceil(dmg * (1.f + bonus));

	
	float defence = 0.f;
	if(cm.move->isPhysical)
		defence = 1.f - (COMBATBONUS_MULT *  target.pDef[cm.move->elem-1]);
	else
		defence = 1.f - (COMBATBONUS_MULT *  target.mDef[cm.move->elem-1]);
	
	//Apply the propritonal defence if an effect requires it
	applyBonus = false;
	bonus = 0.f;
	for(auto &it : CombatData::effects[&target]){
		switch(it.id){
		case DEWPOINT:
			bonus += GetEffectPrimaryBuff(it.id);
			applyBonus = true;
			break;
		case RAZEEARTH:
			bonus -= GetEffectPrimaryDebuff(it.id);
			applyBonus = true;
			break;
		case RIPTIDE:
			bonus -= GetEffectPrimaryDebuff(it.id);
			applyBonus = true;
			break;
		case SPARKINGSKIN:
			bonus += (GetEffectPrimaryBuff(it.id) * cm.move->isPhysical); //Hacky!!!
			applyBonus = applyBonus || cm.move->isPhysical;
			break;
		case MAGNETIZE:
			bonus += (GetEffectPrimaryBuff(it.id) * cm.move->isPhysical); //Hacky!!!
			applyBonus = applyBonus || cm.move->isPhysical;
			break;
		case FORTIFY:
			bonus += (it.diffs->curr * GetEffectPrimaryBuff(it.id) * cm.move->isPhysical); //Hacky!!!
			applyBonus = applyBonus || cm.move->isPhysical;
			break;
		case BRASSKNUCKLES:
			bonus -= GetEffectPrimaryDebuff(it.id);
			applyBonus = true;
			break;
		case QUICKSAND:
			bonus -= GetEffectPrimaryDebuff(it.id);
			applyBonus = true;
			break;
		default:
			break;
		}
		switch(it.family){
		case MoveEffect::Family::brittle:
			bonus -= BRITTLE_DEBUFF_BONUS;
			applyBonus = true;
			break;
		default:
			break;
		}
	}
	if(applyBonus)
		defence *= (1.f + bonus);

	dmg = (int) ceil(dmg * defence);

	target.remHP -= dmg;
	target.remHP = target.remHP * (target.remHP > 0);

	//Post-damage effect appliance
	for(auto &it : CombatData::effects[&target]){
		if(it.id == FIREWALL){
			CombatData::effects[&target].emplace_back(1738);//FIXME: magic number! June 20, 2020: effect applied from firewall has no id...
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectSecondaryDuration(it.id);
			meff.family = MoveEffect::Family::burning;
			meff.affected = &target;
		}
		else if(it.id == BARBEDHUSK && cm.move->isPhysical){
			int dmgReturned = (int) ceil(dmg * GetEffectPrimaryBuff(it.id));
			cm.caster->remHP -= dmgReturned;
			cm.caster->remHP = cm.caster->remHP * (cm.caster->remHP > 0);
		}
	}
}


void ApplyHeal(Actor &target, CasterMove &cm){
	int heal = cm.move->healing;
	float effectiveness = Effectiveness(cm.move->elem, cm.caster->type);
	heal = (int) ceil(heal * effectiveness);
	
	target.remHP += heal;

	if(target.remHP > target.maxHP)
		target.remHP = target.maxHP;
}


void ApplyCost(CasterMove &cm){
	int cost = cm.move->cost;

	for(auto &it : CombatData::effects[cm.caster]){
		if(it.family == MoveEffect::Family::efficient)
			cost -= (int) floor(EFFICIENT_BUFF_BONUS * cm.move->cost);
	}
	cost = cost * (cost > 0);
	cm.caster->remMP -= cost;
}


