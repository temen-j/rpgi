#include "..\include\combat.h"
#include "..\include\game.h"

CasterTargetsPair::CasterTargetsPair(Actor *c, struct Move *m, const Vec<Actor *> &t){
	caster = c;
	move = m;
	targets = t;
}


void StartCombat(Game &game){
	//TODO: set pos and bounding boxes of the target selection
	CombatData *cbtData = game.cbtData;

	cbtData->focus = 0;

	cbtData->portraits.toggles[0].active = true;
	cbtData->portraits.toggles[0].texture = LoadTexture("../img/cassandra_dev.png");
	cbtData->portraits.toggles[1].texture = LoadTexture("../img/gordon_dev.png");
	cbtData->portraits.toggles[2].texture = LoadTexture("../img/lou_dev.png");
	cbtData->portraits.toggles[3].texture = LoadTexture("../img/persy_dev.png");
	cbtData->halo = LoadTexture("../img/portrait_halo.png");

	for(size_t i = 0; i < 4; ++i){
		ImageToggle *toggle = &cbtData->portraits.toggles[i];
		toggle->bounds =
			(Rectangle){PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING), PORTRAIT_WIDTH, PORTRAIT_WIDTH};
	}

	cbtData->playerTeam = &game.player.team;

	CreateGoons(*cbtData);
	TeamsSetup(*cbtData);
	MoveButtonsSetup(*cbtData);

	cbtData->chosenMove = nullptr;
	cbtData->aiMakePairs = true;

	cbtData->hasMoveChosen.resize(cbtData->playerAlive.size());
	for(unsigned int i = 0; i < cbtData->hasMoveChosen.size(); ++i)
		cbtData->hasMoveChosen[i] = false;

	cbtData->targetSelectedList.bounds = (Rectangle){256, 64, 192, 192};
	cbtData->targetAliveList.bounds = (Rectangle){256 + 192 + 128, 64, 192, 192};

	GetAffordableMoves(*cbtData->playerTeam->members[game.cbtData->focus], cbtData->affordable);

	game.justEnteredState = true;
}


void AIMakeCTPs(CombatData &cbtD){
	for(unsigned int i = 0; i < cbtD.botAlive.size(); ++i){ //FIXME: turn into for-range
		struct Move *move = cbtD.botAlive[i]->moves[0];
		//TODO: add check for maxTargets = whole field and self 
		if(move->isFriendly){
			Vec<Actor *> targets;
			for(int j = 0; j < move->maxTargets; ++j)
				targets.push_back(cbtD.botAlive[j]);
			cbtD.ctps.push_back(CasterTargetsPair(cbtD.botAlive[i], move, targets));
		}
		else if(move->isHostile){
			Vec<Actor *> targets;
			for(int j = 0; j < move->maxTargets; ++j)
				targets.push_back(cbtD.playerAlive[j]);
			cbtD.ctps.push_back(CasterTargetsPair(cbtD.botAlive[i], move, targets));
		}
	}
	cbtD.aiMakePairs = false;
}


void SelectMoves(CombatData &cbtD){
	/* Actor *actor = cbtD.playerAlive[cbtD.focus]; //FIXME: won't work if a character dies! */
	Actor *actor = cbtD.playerTeam->members[cbtD.focus];

	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		Update(cbtD.moveButtons[i]);
		if(cbtD.moveButtons[i].state == GuiControlState::GUI_STATE_PRESSED && cbtD.affordable){
			bool found = false;
			for(size_t j = 0; j < NUM_ACTOR_MOVES; ++j){
				if(actor->moves[i] == cbtD.affordable[j]){ //If the selection is in the affordable move list
					found = true;
					break;
				}
			}
			if(found){
				cbtD.chosenMove = actor->moves[i];
				cbtD.canAssign = true;
			}
			break;
		}
	}
}


void GetAffordableMoves(Actor &actor, struct Move **affordable){
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i)
		affordable[i] = nullptr;

	unsigned int fill = 0;
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(actor.moves[i]){
			if(actor.moves[i]->cost <= actor.remMP){
				affordable[fill] = actor.moves[i];
				fill++;
			}
		}
	}
}


void AssignTargets(CombatData &cbtD){
	//Make a macro-loop
	//TODO: Make this into a function, (AssignTargetsSetup())
	if(!cbtD.begunAssigning){
		//TODO: Add checks for maxTargets == all enemies
		//TODO: Add checks for maxTargets == all actors
		ResetSelectAvailList(cbtD);

		//Get potential targets
		if(cbtD.chosenMove->isFriendly){
			for(auto it : cbtD.playerAlive)
				cbtD.potTargets.push_back(it);
		}
		if(cbtD.chosenMove->isHostile){
			for(auto it : cbtD.botAlive)
				cbtD.potTargets.push_back(it);
		}
		
		for(auto &it : cbtD.potTargets) //TODO: Make this into a function, (GetAliveList())
			cbtD.targetAliveList.text.push_back(it->name);

		SetupListView(cbtD.targetAliveList);
		SetupListView(cbtD.targetSelectedList);

		cbtD.begunAssigning = true;
	}
	if((int)cbtD.chosenTargets.size() < cbtD.chosenMove->maxTargets){
		int prevActiveAlive = cbtD.targetAliveList.active;
		int prevActiveSelect = cbtD.targetSelectedList.active;
		Update(cbtD.targetAliveList);
		Update(cbtD.targetSelectedList);

		if(prevActiveAlive != -1 && cbtD.targetAliveList.active != prevActiveAlive)
			AddFromAliveList(cbtD, prevActiveAlive);
		if(prevActiveSelect != -1 && cbtD.targetSelectedList.active != prevActiveSelect)
			RemoveFromSelectedList(cbtD, prevActiveSelect);
	}
	else{
		cbtD.canMakePair = true;
		cbtD.canAssign = false;
	}
}


void MakeCTP(CombatData &cbtD){
	Actor *&actor = cbtD.playerTeam->members[cbtD.focus];
	cbtD.ctps.emplace( cbtD.ctps.begin(), CasterTargetsPair(actor, cbtD.chosenMove, cbtD.chosenTargets));
	cbtD.dispTargetLists = false;
	cbtD.begunAssigning = false;
	cbtD.hasMoveChosen[cbtD.focus] = true;

	cbtD.canMakePair = false;

}

//TODO: make me more elegant?
void AddFromAliveList(CombatData &cbtD, int &prevActive){
	cbtD.chosenTargets.push_back(cbtD.potTargets[prevActive]);
	cbtD.targetSelectedList.text.push_back(cbtD.targetAliveList.text[prevActive]);
	SetupListView(cbtD.targetSelectedList);
}


void RemoveFromSelectedList(CombatData &cbtD, int &prevActive){
	cbtD.chosenTargets.erase(cbtD.chosenTargets.begin() + prevActive);
	cbtD.targetSelectedList.text.erase(cbtD.targetSelectedList.text.begin() + prevActive);
	SetupListView(cbtD.targetSelectedList);
}


void HandleInventoryPortraits(CombatData &cbtD){
	InventoryPortraits *invP = &cbtD.portraits;
	bool isToggled[4]; //Keep track of previous activation
	for(size_t i = 0; i < 4; ++i)
		isToggled[i] = invP->toggles[i].active;

	for(size_t i = 0; i < 4; ++i){
		bool update = Update(invP->toggles[i]);
		if(isToggled[i] && cbtD.hasMoveChosen[i]){
			for(size_t j = 0; j < 4 && cbtD.hasMoveChosen[i]; ++j){ //Cycle through characters who have yet to select moves
				i = (i + 1) % 4; //FIXME: magic numbers!
				invP->toggles[i].active = true;
				cbtD.focus = i;
			}
			for(size_t j = 0; j < 4; ++j){
				if(j != i) //Turn the others in the toggle group off
					invP->toggles[j].active = false;
			}
			break;
		}
		if(update != isToggled[i] && !update && isToggled[i])
			invP->toggles[i].active = true;
		if(update != isToggled[i] && update){
			cbtD.focus = i;
			for(size_t j = 0; j < 4; ++j){
				if(j != i) //Turn the others in the toggle group off
					invP->toggles[j].active = false;
			}
			break;
		}

	}

}


void MoveButtonsSetup(CombatData &cbtD){
	Vector2 pos = {96, 448};
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		cbtD.moveButtons[i].bounds = (Rectangle){pos.x + (176 * (i % 4)), pos.y + (80 * (i / 4)), 160, 64};
	}

	MoveButtonsTextSetup(cbtD);
}


void MoveButtonsTextSetup(CombatData &cbtD){
	Actor *actor = cbtD.playerTeam->members[cbtD.focus];
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(actor->moves[i])
			cbtD.moveButtons[i].text = actor->moves[i]->name;
		else
			break; //early exit b/c moves should always be valid until nullptrs at the end
	}
}


void TeamsSetup(CombatData &cbtD){
	for(unsigned int i = 0; i < cbtD.playerTeam->members.size(); ++i){
		Actor *actor = cbtD.playerTeam->members[i];
		if(!IsDead(*actor))
			cbtD.playerAlive.push_back(actor);
	}
	for(unsigned int i = 0; i < cbtD.botTeam->members.size(); ++i){
		Actor *actor = cbtD.botTeam->members[i];
		if(!IsDead(*actor))
			cbtD.botAlive.push_back(actor);
	}
}


void DisableUnusedButtons(CombatData &cbtD){
	Actor *actor = cbtD.playerTeam->members[cbtD.focus];
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(actor->moves[i])
			cbtD.moveButtons[i].state = GuiControlState::GUI_STATE_NORMAL;
		else
			cbtD.moveButtons[i].state = GuiControlState::GUI_STATE_DISABLED;
	}
}


bool CanExecMoves(CombatData &cbtD){
	Vec<Actor *> allInCombat;
	for(auto &it : cbtD.playerAlive)
		allInCombat.push_back(it);
	for(auto &it : cbtD.botAlive)
		allInCombat.push_back(it);

	//O(n^2), 
	//TODO: find a better way of doing this...
	for(auto &it : allInCombat){
		bool found = false;
		for(auto &jt : cbtD.ctps){
			if(it == jt.caster){
				found = true;
				break;
			}
		}
		if(!found)
			return false;
	}

	return true;
}


bool LessThanCTP(CasterTargetsPair *first, CasterTargetsPair *second){
	//TODO: Add priority effect 'slow' in here
	return first->move->priority < second->move->priority;
}


//NOTE: June 9, 2020
//This function will try to execute within one frame, this does not account for animations/sound
//These will be added at a later date, hopefully... So in order to keep the same relative flow control
//Create a macro-loop bounded by ctpsPtrs.size(), and iterate on confirmation that a move has finished
//animating / playing audio, the confirmation will most likely be a boolean with the combat data
void ExecMoves(CombatData &cbtD){
	if(!cbtD.executingMoves){
		cbtD.ctpsPtrs.resize(0);

		for(auto &it : cbtD.ctps)
			cbtD.ctpsPtrs.push_back(&it);

		std::sort(cbtD.ctpsPtrs.begin(), cbtD.ctpsPtrs.end(), LessThanCTP); //sort on priority 

		cbtD.execIndex = 0;
		cbtD.executingMoves = true;
	}

	if(cbtD.executingMove){
		ExecMove(*cbtD.ctpsPtrs[cbtD.execIndex]);
		if(!cbtD.executingMove){
			cbtD.execIndex++;
			cbtD.executingMove = cbtD.execIndex < cbtD.ctpsPtrs.size();
		}
	}
}


void ExecMove(CasterTargetsPair &ctp){
	return;
}

//TODO: Make a tool that creates enemies
void CreateGoons(CombatData &cbtD){
	cbtD.botTeam = new Team(); //ewww dynamic alloc...
	Actor *foo = new Actor(); //TODO: Do arena alloc instead
	Actor *bar = new Actor();

	Element gridNone[NUMCELLS] = {
		Element::none, Element::none, Element::none, Element::none,
		Element::none, Element::none, Element::none, Element::none,
		Element::none, Element::none, Element::none, Element::none,
		Element::none, Element::none, Element::none, Element::none
	};

	foo->name = "Metis";
	for(size_t i = 0; i < NUMCELLS; ++i){
		foo->grids[0][i] = gridNone[i];
		foo->grids[1][i] = gridNone[i];
		foo->grids[2][i] = gridNone[i];
	}
	foo->grids[1][0] = Element::water;

	bar->name = "Callisto";
	for(size_t i = 0; i < NUMCELLS; ++i){
		bar->grids[0][i] = gridNone[i];
		bar->grids[1][i] = gridNone[i];
		bar->grids[2][i] = gridNone[i];
	}
	bar->grids[1][0] = Element::spectre;

	foo->moves[0] = &AllMoves::moves[102]; //Rend
	bar->moves[0] = &AllMoves::moves[122]; //Shadow Slash

	AssignStats(foo);
	AssignStats(bar);

	cbtD.botTeam->members.push_back(foo);
	cbtD.botTeam->members.push_back(bar);
}


void ResetSelectAvailList(CombatData &cbtD){
	cbtD.chosenTargets.resize(0);
	cbtD.potTargets.resize(0);
	cbtD.targetAliveList.text.resize(0);
	cbtD.targetSelectedList.text.resize(0);
}


/* void tickEffects(casterTargetsPairs &ctp){ */
/* 	//In reverse order of moves, tick all effects of every actor */
/* 	for(int i = (int)ctp.size() - 1; i > -1; --i){ */
/* 		if(!isDead(ctp[i].first) && ctp[i].first->currEffects.size() > 0){ */
/* 			for(effect *e : ctp[i].first->currEffects) */
/* 				e->tick(e, ctp[i].first); */
/* 		} */
/* 	} */
/* } */


/* void cleanupDead(team &t){ */
/* 	for(int i = 0; i < (int)t.members.size(); ++i){ */
/* 		if(!isDead(t.members[i])){ */
/* 			t.members.erase(t.members.begin() + i); */
/* 			--i; */
/* 		} */
/* 	} */
/* } */

