#include "..\include\actor.h"
#include "..\include\move.h"

void AssignStats(Actor *a){
	//Init all stats to 0
	for(int i = 0; i < NUMELEMENTS; ++i)
		a->mAtk[i] = a->mDef[i] = a->pAtk[i] = a->pDef[i] = 0;

	a->hpBonus = 0;
	a->mpBonus = 0;

	for(int i = 0; i < NUMGRIDS; ++i){
		for(int j = 0; j < NUMCELLS; ++j){
			if(i == 0){
				if(a->grids[i][j] > Element::none && a->grids[i][j] <= Element::spectre){
					a->mAtk[a->grids[i][j] - 1]++; //At the elem., incr.
					a->mDef[a->grids[i][j] - 1]++;
				}
			}
			if(i == 1){
				if(a->grids[i][j] > Element::none && a->grids[i][j] <= Element::spectre){
					a->pDef[a->grids[i][j] - 1]++;
					switch(a->grids[i][j]){
					case Element::fire:
						a->hpBonus += HPBONUS_FIRE;
						break;
					case Element::water:
						a->hpBonus += HPBONUS_WATER;
						break;
					case Element::nature:
						a->hpBonus += HPBONUS_NATURE;
						break;
					case Element::lightning:
						a->hpBonus += HPBONUS_LIGHTNING;
						break;
					case Element::metal:
						a->hpBonus += HPBONUS_METAL;
						break;
					case Element::rock:
						a->hpBonus += HPBONUS_ROCK;
						break;
					case Element::spectre:
						a->hpBonus += HPBONUS_SPECTRE;
						break;
					default:
						break;
					}
				}	
			}
			if(i == 2){
				if(a->grids[i][j] > Element::none && a->grids[i][j] <= Element::spectre){
					a->pAtk[a->grids[i][j] - 1]++;
					switch(a->grids[i][j]){
					case Element::fire:
						a->mpBonus += MPBONUS_FIRE;
						break;
					case Element::water:
						a->mpBonus += MPBONUS_WATER;
						break;
					case Element::nature:
						a->mpBonus += MPBONUS_NATURE;
						break;
					case Element::lightning:
						a->mpBonus += MPBONUS_LIGHTNING;
						break;
					case Element::metal:
						a->mpBonus += MPBONUS_METAL;
						break;
					case Element::rock:
						a->mpBonus += MPBONUS_ROCK;
						break;
					case Element::spectre:
						a->mpBonus += MPBONUS_SPECTRE;
						break;
					default:
						break;
					}
				}
			}
			
			int prevMaxHP = a->maxHP;
			int prevMaxMP = a->maxMP;
			a->maxHP = (int)ceil(INITHP * (1.0f + HPMPBONUS_MULT * a->hpBonus));
			a->maxMP = (int)ceil(INITMP * (1.0f + HPMPBONUS_MULT * a->mpBonus));
			/* a->maxMP = INITMP; */

			a->remHP = (int) ceil(((float) a->remHP / prevMaxHP) * a->maxHP);
			a->remMP = (int) ceil(((float) a->remMP / prevMaxMP) * a->maxMP);
		}
	}

	AssignType(*a);
}


void AssignType(Actor &a){
	int counts[NUMELEMENTS] = { 0,0,0,0,0,0,0 };
	
	for(int i = 0; i < NUMGRIDS; ++i){
		for(int j = 0; j < NUMCELLS; ++j){
			if(a.grids[i][j] > Element::none && a.grids[i][j] <= Element::spectre){
				counts[a.grids[i][j] - 1]++;
			}
		}
	}
	
	int max = 0;
	int maxIndex = -1;
	for(int i = 0; i < NUMELEMENTS; ++i){
		if(counts[i] > max){
			max = counts[i];
			maxIndex = i;
		}
	}
	int nextMaxIndex = -1;
	for(int i = 0; i < NUMELEMENTS; ++i){
		if(counts[i] == max && i != maxIndex){
			nextMaxIndex = i;
			break;
		}
	}
	Element found, foundNext;
	if(maxIndex == -1){
		found = Element::none;
		foundNext = Element::none;
	}
	else{
		found = (Element)(maxIndex + 1);
		if(nextMaxIndex != -1)
			foundNext = (Element)(nextMaxIndex + 1);
		else
			foundNext = Element::none;
	}

	a.type[0] = found;
	a.type[1] = foundNext;

	struct Move *moves[NUM_ACTOR_MOVES] = {nullptr};
	int fill = 0;
	for(int i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(a.moves[i]){
			if(a.moves[i]->elem == a.type[0] || a.moves[i]->elem == a.type[1]){
				moves[fill] = a.moves[i];
				fill++;
			}
		}
	}
	for(int i = 0; i < NUM_ACTOR_MOVES; ++i)
		a.moves[i] = moves[i];
}


bool IsDead(const Actor &a){
	if(a.remHP <= 0)
		return true;
	return false;
}


void HealActor(Actor &a, const unsigned int amount){
	unsigned int diff = (unsigned int)(a.maxHP - a.remHP);
	if(diff < amount){
		a.remHP += amount;
	}
	else{
		a.remHP = a.maxHP;
	}
	//TODO: do something about proportions
}


void FullHealActor(Actor &a){
	a.remHP = a.maxHP;
	//TODO: do something about proportions
}


