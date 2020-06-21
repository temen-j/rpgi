#include "include\move.h"
#include "include\actor.h"


Move::Move(){
		id = 0;
		levelObtained = 0;
		priority = -1;
		maxTargets = -1;
		damage = -1;
		healing = -1;
		cost = -1;
		elem = Element::none;
		isPhysical = false;
		isFriendly = false;
		isHostile = false;
		owner = Ownership::general;
}


Move::Move(int id, const char *name, Element elem, int levelObtained, int priority, int maxTargets, int damage, int healing, int cost,
		bool isPhysical, bool isFriendly, bool isHostile, Ownership owner){
		this->id = id;
		this->name = name;
		this->levelObtained = levelObtained;
		this->priority = priority;
		this->maxTargets = maxTargets;
		this->damage = damage;
		this->healing = healing;
		this->cost = cost;
		this->elem = elem;
		this->isPhysical = isPhysical;
		this->isFriendly = isFriendly;
		this->isHostile = isHostile;
		this->owner = owner;
}






/* move::move(const move_serialized &ms){ */
/* 	name = ms.name; */
/* 	id = ms.id; */
/* 	std::cout << "levelObtained: " << bitExtracted(ms.packed0, 3, 0) << std::endl; */
/* 	levelObtained = bitExtracted(ms.packed0, 3, 0); */
/* 	priority = ms.priority; */
/* 	maxTargets = ms.maxTargets; */
/* 	//damage = bitExtracted(ms.packed1, 2, 0) >> 8 + ms.damage; */
/* 	std::cout << damage << std::endl; */
/* 	healing = bitExtracted(ms.packed1, 2, 2) >> 8 + ms.healing; */
/* 	cost = bitExtracted(ms.packed1, 2, 4) >> 8 + ms.cost; */
/* 	owner = (ownership)bitExtracted(ms.packed0, 1, 6); */
/* 	isPhysical = (bool)bitExtracted(ms.packed0, 1, 3); */
/* 	isFriendly = (bool)bitExtracted(ms.packed0, 1, 4); */
/* 	isHostile = (bool)bitExtracted(ms.packed0, 1, 5); */
/* 	elem = (element)ms.elem; */
/* 	use = nullptr; */
/* } */


/* void loadAllMoves(std::vector<move*> &allMoves){ */
/* 	allMoves.resize(127); */
/* 	std::ifstream ifs("moves.mvs", std::ios::in | std::ios::binary); */
/* 	move_serialized am[127]; */
/* 	void *data = am; */

/* 	ifs.read((char*)data, sizeof(am)); */
/* 	ifs.close(); */

/* 	for(int i = 0; i < 127; ++i) */
/* 		allMoves[i] = new move(am[i]); */
/* } */


/* int bitExtracted(const int &num, const int &k, const int &pos){ */
/* 	return (((1 << k) - 1) & (num >> pos)); */
/* } */


/* namespace movefunctions{ */

/* 	bool canAfford(const move *m, actor *caster){ */
/* 		if(m->cost > caster->remMP) */
/* 			return false; */
/* 		return true; */
/* 	} */

/* 	bool canAffordFLAMESWORD(const move *m, actor *caster, actor *target){ */
/* 		bool hasBurning = hasEffect(target, "Burning"); */

/* 		if(hasBurning && (m->cost / 2) > caster->remMP) */
/* 			return false; */
/* 		if(m->cost > caster->remMP) */
/* 			return false; */

/* 		return true; */
/* 	} */

/* 	std::vector<actor*> selectTargets(const move *m, const team &ally, const team &opponent){ */
/* 		std::vector<actor*> out; */

/* 		int count = m->maxTargets; */
/* 		int selection = -1; */
/* 		while(count > 0){ */
/* 			std::cout << "Which would you like to select? " << count << " Remaining..." << std::endl; */

/* 			if(m->isFriendly && !m->isHostile){ */
/* 				std::cout << ally; */
/* 				selection = getIntegerInput(0, (int)ally.members.size()); */ 
/* 				out.push_back(ally.members[selection-1]); */
/* 			} */	
/* 			if(m->isHostile && !m->isFriendly){ */
/* 				std::cout << opponent; */
/* 				selection = getIntegerInput(0, (int)opponent.members.size()); */
/* 				out.push_back(opponent.members[selection-1]); */
/* 			} */
/* 		} */

/* 		return out; */
/* 	} */

/* 	void resolveDamageHP(std::vector<int> &in, std::vector<actor*> &targets){ */
/* 		for(int i = 0; i < targets.size(); ++i) */
/* 			targets[i]->remHP = targets[i]->remHP - in[i] > 0 ? targets[i]->remHP : 0; */
/* 	} */


/* 	std::vector<int> pDamage(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out; */

/* 		float splitDamage = m->maxTargets > 1 ? (float)m->damage / m->maxTargets : m->damage; */

/* 		for(actor* target : targets){ */
/* 			float effectiveness = elementchart::effectiveness(m->elem, target->type); */
/* 			float floatDamage = splitDamage * (1.0f + FLATBONUS * caster->pAtk[m->elem - 1] + (-1.0f * FLATBONUS * target->pDef[m->elem - 1])); */
/* 			int damage = (int) ceil(effectiveness * floatDamage); */
/* 			out.push_back(damage); */
/* 		} */

/* 		return out; */
/* 	} */

/* 	std::vector<int> mDamage(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out; */

/* 		float splitDamage = m->maxTargets > 1 ? (float)m->damage / m->maxTargets : m->damage; */

/* 		for(actor* target : targets){ */
/* 			float effectiveness = elementchart::effectiveness(m->elem, target->type); */
/* 			float floatDamage = splitDamage * (1.0f + caster->mAtk[m->elem - 1] + (-1.0f * target->mDef[m->elem - 1])); */
/* 			int damage = (int)ceil(effectiveness * floatDamage); */
/* 			out.push_back(damage); */
/* 		} */

/* 		return out; */
/* 	} */

/* 	std::vector<int> pHeal(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out; */

/* 		float splitHeal = m->maxTargets > 1 ? (float)m->healing / m->maxTargets : m->healing; */

/* 		for(actor* target : targets){ */
/* 			float floatHeal = splitHeal * (1.0f + caster->pAtk[m->elem - 1]); */
/* 			int heal = (int)ceil(floatHeal); */
/* 			out.push_back(heal); */
/* 		} */

/* 		return out; */
/* 	} */

/* 	std::vector<int> mHeal(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out; */

/* 		float splitHeal = m->maxTargets > 1 ? (float)m->healing / m->maxTargets : m->healing; */

/* 		for(actor* target : targets){ */
/* 			float floatHeal = splitHeal * (1.0f + caster->mAtk[m->elem - 1]); */
/* 			int heal = (int)ceil(floatHeal); */
/* 			out.push_back(heal); */
/* 		} */

/* 		return out; */
/* 	} */


/* 	void ignite(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = pDamage(m, caster, targets); */
/* 		resolveDamageHP(out, targets); */
/* 	} */

/* 	void  blaze(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		resolveDamageHP(out, targets); */
/* 		effect *burning = new effect("Burning", 1, 15, 0, 0, 0); */
/* 		for(actor *t : targets){ */
/* 			t->currEffects.push_back(burning); */
/* 		} */
/* 		//give actor the effect */
/* 	} */

/* 	void fireball(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void explosion(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = pDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void firebeam(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void flamesword(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = pDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void flarekick(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = pDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */
	
/* 	void firewall(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = pDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void searingflesh(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		//give actor the effect */
/* 		std::vector<int> out; */
/* 	} */

/* 	void moltenmeteor(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void wildfire(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void razeearth(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void fromtheashes(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = pHeal(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void supernova(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void flashfriction(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out= pDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void scorchingheat(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void dragonbreath(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* 	void icarusinferno(move *m, actor *caster, std::vector<actor*>& targets){ */
/* 		std::vector<int> out = mDamage(m, caster, targets); */
/* 		//give actor the effect */
/* 	} */

/* } */
