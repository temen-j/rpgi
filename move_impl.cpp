#include "include\move_impl.h"
#include "include\actor.h"
#include "include\move.h"
#include "include\combat.h"

inline EffectDiff *AllocEDiff(){
	return static_cast<EffectDiff *>(MemPoolAlloc(&CombatData::diffMemPool, sizeof(EffectDiff)));
}

inline EffectDiff *AllocEDiff(size_t size){ //WARNING: Make the assumption that size > 0
	return static_cast<EffectDiff *>(MemPoolAlloc(&CombatData::diffMemPool, size * sizeof(EffectDiff)));
}


void MoveImplementation::IGNITE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
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
	}
	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FIREWALL(Actor &target, CasterMove &cm){
	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);

	if(!UpdateEffectDuration(target, temp)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	cm.caster->remMP -= cm.move->cost;
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
	
	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
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
	}

	MoveEffect temp2(cm.move->id);
	temp2.duration = GetEffectPrimaryDuration(temp2.id);

	if(!UpdateEffectDuration(target, temp2)){
		CombatData::effects[&target].emplace_back(cm.move->id);
		auto &meff = CombatData::effects[&target].back();
		meff.duration = GetEffectPrimaryDuration(meff.id);
	}

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FROMTHEASHES(Actor &target, CasterMove &cm){
	ApplyHeal(target, cm);

	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].id == MoveEffect::Family::burning){
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
	
	cm.caster->remMP -= cm.move->cost;
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
	}

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::WATERWHIP(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::COALESCE(Actor &target, CasterMove &cm){
	bool consumed = false;

	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].id == MoveEffect::Family::wet){
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

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::HAILSTORM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].id == MoveEffect::Family::wet){
			consumed = true;
			CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
			break;
		}
	}
	
	if(consumed){
		MoveEffect temp(cm.move->id);
		temp.duration = GetEffectPrimaryDuration(meff.id);
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

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DEWPOINT(Actor &target, CasterMove &cm){
	//FIXME: Apply % heal?
	
	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].id == MoveEffect::Family::wet){
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
	

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FLASHFREEZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].id == MoveEffect::Family::wet){
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

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
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
	
	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::HELLBROTH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	bool consumed = false;
	for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
		if(CombatData::effects[&target][i].id == MoveEffect::Family::wet){
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

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SEEDSHOT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
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

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SAPPINGSTEMS(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	MoveEffect temp(cm.move->id);
	temp.duration = GetEffectPrimaryDuration(temp.id);
	temp.family = MoveEffect::Family::florid;

	bool consumed = false;
	if(!UpdateEffectDuration(target, temp)){
		for(int i = 0; i < (int)CombatData::effects[&target].size(); ++i){
			if(CombatData::effects[&target][i].id == MoveEffect::Family::florid && ){
				consumed = true;
				CombatData::effects[&target].erase(CombatData::effects[&target].begin() + i);
				break;
			}
		}
	}

	if(consumed){

		if(!UpdateEffectDuration(target, temp)){
			CombatData::effects[&target].emplace_back(cm.move->id);
			auto &meff = CombatData::effects[&target].back();
			meff.duration = GetEffectPrimaryDuration(meff.id);
			meff.family = MoveEffect::Family::florid;
		}
	}


	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::NOURISH(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::LEAFLANCE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FUNGALSPORES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BARBEDHUSK(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::GRASSBLADES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PETALPIKE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::UNDERGROWTH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SYMBIOSIS(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ENSNARINGVINE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::RANCIDROSES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DRYADSCURSE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ZAP(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CHARGE(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DISCHARGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::LIGHTNINGBOLT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DAZZLINGLIGHTS(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ELECTROSTORM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::LIGHTNINGKICK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SPARKINGSKIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SUPERCONDUCT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::STATICSHOCK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::EVANESCENTFIELD(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::HIGHVOLTAGE(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::MJOLNIR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CLOSEDCIRUIT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::IRONSPIKES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CANNONBALL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SHARPEN(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SHATTERSHRAPNEL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BALLANDCHAIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::QUICKSILVER(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::COPPERCUTLASS(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::RAZORWIRE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::MIDASTOUCH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CHROMEPLATED(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::MAGNETIZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BRASSKNUCKLES(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ALLOYASSAULT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PIERCINGPLATINUM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::HURLROCK(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::STONESPEAR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FORTIFY(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::QUICKSAND(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ENTOMB(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CRUSH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::TREMOR(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ROCKSLIDE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ROLLINGBOULDER(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SAPPHIRESTRIKE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::RUBYRUSH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::GARNETGAZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::EMERALDEDGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::OBSIDIANONSLAUGHT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ECTORAY(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::TORMENT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CHAOSCLAW(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PHANTOMWALTS(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::GRAVETENDER(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::MINDINVASION(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BINDINGPAIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PLAGUE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::WICKEDHEX(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PETRIFYINGWAIL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DECAY(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::VIVIDNIGHTMARE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ETHEREALFOG(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::NOXIOUSVOID(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FLASHFRICTION(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SCORCHINGHEAT(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DRAGONBREATH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ICARUSINFERNO(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::REND(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SIRENSTEAR(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CHILLINGBLAST(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::DELUGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::NEEDLE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BLOOM(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::TREECLEAVER(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::VENOMCOATING(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SURGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::OVERLOAD(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::IONSTRIKE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PLASMAPULSE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SCRAPSLUG(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ANNEAL(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::ANODIZE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::GALVANIZEDGLAIVE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::GRAVELSPIN(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SANDBOMB(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::CRYSTALCAGE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::FISSURE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::SHADOWSLASH(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::PILFER(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BLOODCURDLE(Actor &target, CasterMove &cm){

	cm.caster->remMP -= cm.move->cost;
}


void MoveImplementation::BLACKHOLE(Actor &target, CasterMove &cm){
	ApplyDamage(target, cm);

	cm.caster->remMP -= cm.move->cost;
}


void ApplyDamage(Actor &target, CasterMove &cm){
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
			applyBonus = cm.move->elem == Element::fire;
			break;
		case RAINSTORM:
			bonus += (GetEffectPrimaryBuff(it.id) * (cm.move->elem == Element::water)); //Hacky!!!
			applyBonus = cm.move->elem == Element::water;
			break;
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
			MoveEffect meff(1738); //FIXME: magic number! June 20, 2020: effect applied from firewall has no id...
			meff.duration = GetEffectSecondaryDuration(it.id);
			meff.family = MoveEffect::Family::burning;
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


