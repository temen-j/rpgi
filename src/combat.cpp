/* #include "..\include\combat.h" */
#include "..\include\game.h"
#include "..\include\move_impl.h"

#include "..\include\embed\cassandra_combat_sprite.h"
#include "..\include\embed\gordon_combat_sprite.h"
#include "..\include\embed\lou_combat_sprite.h"
#include "..\include\embed\persy_combat_sprite.h"

#include "..\include\embed\metis_combat_sprite.h"
#include "..\include\embed\callisto_combat_sprite.h"

#include "..\include\sprite.h"

Team *CombatData::playerTeam = nullptr;
Team *CombatData::botTeam = nullptr;

UMap<Actor *, Vec<MoveEffect> > CombatData::effects;
UMap<Actor *, StatusEffects> CombatData::statusEffects;
MemPool CombatData::diffMemPool = CreateMemPool(DIFF_MEM_SIZE);

CombatPortraits CombatData::portraits;
Texture CombatData::halo;
UMap<Actor *, bool> CombatData::hasMoveChosen;

UMap<Actor *, Sprite> CombatData::actorSprites;
bool CombatData::moveAnimPlaying = false;

Vec<Actor *> CombatData::playerAlive;
Vec<Actor *> CombatData::botAlive;
Vec<Actor *> CombatData::potTargets;
Vec<Actor *> CombatData::chosenTargets;

Vec<CasterTargetsPair> CombatData::ctps;
Vec<CasterTargetsPair *> CombatData::ctpsPtrs;

unsigned char CombatData::focus = 0;
unsigned int CombatData::animLockouts = 0;

bool CombatData::executingMoves = false;
bool CombatData::interpStats = false;
unsigned int CombatData::execIndex = 0;
float CombatData::statBarInterpTimer = 0.f;

ListView CombatData::targetAliveList;
ListView CombatData::targetSelectedList;
UMap<Actor *, StatBar[2]> CombatData::statBars;
BoxLabel CombatData::moveAnnouncment;


CasterTargetsPair::CasterTargetsPair(Actor *c, struct Move *m, const Vec<Actor *> &t){
	caster = c;
	move = m;
	targets = t;
}


void StartCombat(Game &game){
	CombatData *cbtData = game.cbtData;

	cbtData->focus = 0;

	CombatData::portraits.toggles.resize(4);
	CombatData::portraits.toggles[0].active = true;
	//FIXME: Use the texture manager instead of loading them with each state change
	CombatData::portraits.toggles[0].texture = LoadTexture("../img/cassandra_dev.png");
	CombatData::portraits.toggles[1].texture = LoadTexture("../img/gordon_dev.png");
	CombatData::portraits.toggles[2].texture = LoadTexture("../img/lou_dev.png");
	CombatData::portraits.toggles[3].texture = LoadTexture("../img/persy_dev.png");
	cbtData->halo = LoadTexture("../img/portrait_halo.png");

	for(size_t i = 0; i < 4; ++i){
		ImageToggle *toggle = &cbtData->portraits.toggles[i];
		toggle->bounds =
			(Rectangle){PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING), PORTRAIT_WIDTH, PORTRAIT_WIDTH};
	}

	CombatData::playerTeam = &game.player.team;

	CombatSpriteSetup(*cbtData);

	CreateGoons(*cbtData);
	TeamsSetup(*cbtData);

	GoonSpriteSetup(*cbtData);

	CombatData::effects.clear();
	for(auto &it : CombatData::playerAlive)
		CombatData::effects.emplace(it, Vec<MoveEffect>());
	for(auto &it : CombatData::botAlive)
		CombatData::effects.emplace(it, Vec<MoveEffect>());

	CombatData::statusEffects.clear();
	for(auto &it : CombatData::playerAlive)
		CombatData::statusEffects.emplace(it, StatusEffects());
	for(auto &it : CombatData::botAlive)
		CombatData::statusEffects.emplace(it, StatusEffects());

	MoveButtonsSetup(*cbtData);

	cbtData->chosenMove = nullptr;
	cbtData->aiMakePairs = true;

	for(auto &it : CombatData::playerAlive)
		CombatData::hasMoveChosen[it] = false;

	cbtData->targetSelectedList.bounds = (Rectangle){256, 64, 192, 192};
	cbtData->targetAliveList.bounds = (Rectangle){256 + 192 + 128, 64, 192, 192};

	//TODO: Also call this when returning to phase 1
	GetAffordableMoves(*CombatData::playerTeam->members[CombatData::focus], cbtData->affordable);

	for(unsigned int i = 0; i < CombatData::playerAlive.size(); ++i){
		Rectangle hpBounds = {PORTRAIT_WIDTH + 2 * PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING + PORTRAIT_PADDING / 2), STATBAR_WIDTH, STATBAR_HEIGHT};
		Rectangle mpBounds = {PORTRAIT_WIDTH + 2 * PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING +  PORTRAIT_PADDING / 2 + STATBAR_HEIGHT * 2), STATBAR_WIDTH, STATBAR_HEIGHT};
		CombatData::statBars[CombatData::playerAlive[i]][0] = StatBar(1.f, hpBounds, CombatData::playerAlive[i]->maxHP, HPGOODCOLOR, HPBADCOLOR);
		CombatData::statBars[CombatData::playerAlive[i]][1] = StatBar(1.f, mpBounds, CombatData::playerAlive[i]->maxMP, MPGOODCOLOR, MPBADCOLOR);
	}

	CombatData::moveAnnouncment.text = "";
	CombatData::moveAnnouncment.bounds = {0,0,0,0};
	CombatData::moveAnnouncment.bgColor = (Color){28, 33,  35, 200};
	CombatData::moveAnnouncment.textColor = (Color){219, 219, 235, 255};
	CombatData::moveAnnouncment.disabled = true;

	game.justEnteredState = true;
}


void AIMakeCTPs(CombatData &cbtD){
	for(unsigned int i = 0; i < CombatData::botAlive.size(); ++i){ //FIXME: turn into for-range
		Vec<Actor *> targets;
		struct Move *move = CombatData::botAlive[i]->moves[0];

		if(move->maxTargets == TARGET_ALL_ACTORS){
			targets.reserve(CombatData::playerAlive.size() + CombatData::botAlive.size());

			for(auto &it : CombatData::playerAlive)
				targets.push_back(it);
			for(auto &it : CombatData::botAlive)
				targets.push_back(it);
		}
		else if(move->maxTargets == TARGET_SELF){
			targets.push_back(CombatData::botAlive[i]);
		}
		else if(move->isFriendly){
			for(int j = 0; j < move->maxTargets; ++j) //Take the first actors it can
				targets.push_back(CombatData::botAlive[j]);
		}
		else if(move->isHostile){
			for(int j = 0; j < move->maxTargets; ++j) //Take the first actors it can
				targets.push_back(CombatData::playerAlive[j]);
		}

		CombatData::ctps.push_back(CasterTargetsPair(CombatData::botAlive[i], move, targets));
	}
	cbtD.aiMakePairs = false;
}


void SelectMoves(CombatData &cbtD){
	auto &actor = CombatData::playerTeam->members[CombatData::focus];

	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		Update(cbtD.moveButtons[i]);
		if(cbtD.moveButtons[i].state == GuiControlState::GUI_STATE_PRESSED && cbtD.affordable){
			bool found = false;
			for(size_t j = 0; j < NUM_ACTOR_MOVES; ++j){
				if(actor->moves[i] && actor->moves[i] == cbtD.affordable[j]){ //If the selection is in the affordable move list
					/* found = true; */
					cbtD.chosenMove = actor->moves[i];
					cbtD.canAssign = true;
					break;
				}
			}
			/* if(found){ */
			/* 	cbtD.chosenMove = actor->moves[i]; */
			/* 	cbtD.canAssign = true; */
			/* } */
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
	if(!cbtD.begunAssigning){
		AssignTargetsSetup(cbtD);
	}
	if((int)CombatData::chosenTargets.size() < cbtD.chosenMove->maxTargets){
		//Detect changes in selection and add/remove the list
		int prevActiveAlive = CombatData::targetAliveList.active;
		int prevActiveSelect = CombatData::targetSelectedList.active;
		Update(CombatData::targetAliveList);
		Update(CombatData::targetSelectedList);

		if(prevActiveAlive != -1 && CombatData::targetAliveList.active != prevActiveAlive)
			AddFromAliveList(cbtD, prevActiveAlive);
		if(prevActiveSelect != -1 && CombatData::targetSelectedList.active != prevActiveSelect)
			RemoveFromSelectedList(cbtD, prevActiveSelect);
	}
	else{
		cbtD.canMakePair = true;
		cbtD.canAssign = false;
	}
}


void AssignTargetsSetup(CombatData &cbtD){
	//TODO: Add checks for maxTargets == all enemies
	if(cbtD.chosenMove->maxTargets == TARGET_ALL_ACTORS){
		CombatData::chosenTargets.reserve(CombatData::playerAlive.size() + CombatData::botAlive.size());
		for(auto &it : CombatData::playerAlive)
			CombatData::chosenTargets.push_back(it);
		for(auto &it : CombatData::botAlive)
			CombatData::chosenTargets.push_back(it);
		
		cbtD.targetAliveList.text.push_back("ALL");
	}
	ResetSelectAvailList();

	//Get potential targets
	if(cbtD.chosenMove->isFriendly){ //Potential optimization: potTargets.reserve(is... * ...Alive.size())
		for(auto it : CombatData::playerAlive)
			CombatData::potTargets.push_back(it);
	}
	if(cbtD.chosenMove->isHostile){
		for(auto it : CombatData::botAlive)
			CombatData::potTargets.push_back(it);
	}
	
	cbtD.targetAliveList.text.reserve(CombatData::potTargets.size());
	for(auto &it : CombatData::potTargets) //TODO: Make this into a function, (GetAliveList())
		cbtD.targetAliveList.text.push_back(it->name);

	//Populate list views with
	SetupListView(cbtD.targetAliveList);
	SetupListView(cbtD.targetSelectedList);

	cbtD.begunAssigning = true;
}


void MakeCTP(CombatData &cbtD){
	auto &actor = CombatData::playerTeam->members[cbtD.focus];
	CombatData::ctps.emplace(CombatData::ctps.begin(), CasterTargetsPair(actor, cbtD.chosenMove, CombatData::chosenTargets));
	cbtD.dispTargetLists = false;
	cbtD.begunAssigning = false;

	CombatData::hasMoveChosen[actor] = true;

	cbtD.chosenMove = nullptr;
	CombatData::chosenTargets.clear();

	cbtD.canMakePair = false;
}


void AddFromAliveList(CombatData &cbtD, int &prevActive){
	CombatData::chosenTargets.push_back(CombatData::potTargets[prevActive]);
	cbtD.targetSelectedList.text.push_back(cbtD.targetAliveList.text[prevActive]);
	SetupListView(cbtD.targetSelectedList);
}


void RemoveFromSelectedList(CombatData &cbtD, int &prevActive){
	CombatData::chosenTargets.erase(CombatData::chosenTargets.begin() + prevActive);
	cbtD.targetSelectedList.text.erase(cbtD.targetSelectedList.text.begin() + prevActive);
	SetupListView(cbtD.targetSelectedList);
}


void HandleInventoryPortraits(CombatData &cbtD){ //TODO: rename HandleCombatPortraits()
	bool *isToggled = new bool[CombatData::playerTeam->members.size()]; //Keep track of previous activation

	for(size_t i = 0; i < CombatData::playerTeam->members.size(); ++i)
		isToggled[i] = CombatData::portraits.toggles[i].active;

	for(size_t i = 0; i < CombatData::playerTeam->members.size(); ++i){
		bool update = Update(CombatData::portraits.toggles[i]); //a group toggling

		auto actor = CombatData::playerTeam->members[i];
		if(isToggled[i] && CombatData::hasMoveChosen[actor]){

			for(size_t j = 0; j < CombatData::playerTeam->members.size() && CombatData::hasMoveChosen[actor]; ++j){ //Cycle through characters who have yet to select moves
				i = (i + 1) % CombatData::playerTeam->members.size();
				actor = CombatData::playerTeam->members[i];
				CombatData::portraits.toggles[i].active = true;
				CombatData::focus = i;
			}

			for(size_t j = 0; j < CombatData::playerAlive.size(); ++j){
				if(j != i) //Turn the others in the toggle group off
					CombatData::portraits.toggles[j].active = false;
			}
			break;
		}

		if(update != isToggled[i]){
			if(update){
				CombatData::focus = i;
				for(size_t j = 0; j < 4; ++j){
					if(j != i) //Turn the others in the toggle group off
						CombatData::portraits.toggles[j].active = false;
				}
				break;
			}
			else
				CombatData::portraits.toggles[i].active = true;
		}
	}
	delete[] isToggled;
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
		cbtD.moveButtons[i].text = "";
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
			CombatData::playerAlive.push_back(actor);
	}
	for(unsigned int i = 0; i < cbtD.botTeam->members.size(); ++i){
		Actor *actor = cbtD.botTeam->members[i];
		if(!IsDead(*actor))
			CombatData::botAlive.push_back(actor);
	}
}


void CombatSpriteSetup(CombatData &cbtD){
	CombatData::actorSprites[cbtD.playerTeam->members[0]] = LoadSprite(cassandra_combat_anim); 
	
	//FIXME: kind of hacky, need to store looping in the anim file and embedded file
	for(size_t i = 0; i < cbtD.playerTeam->members.size(); ++i){
		switch(i){
		case 0:
			CombatData::actorSprites[cbtD.playerTeam->members[i]] = LoadSprite(cassandra_combat_anim); break;
		case 1:
			CombatData::actorSprites[cbtD.playerTeam->members[i]] = LoadSprite(gordon_combat_anim); break;
		case 2:
			CombatData::actorSprites[cbtD.playerTeam->members[i]] = LoadSprite(lou_combat_anim); break;
		case 3:
			CombatData::actorSprites[cbtD.playerTeam->members[i]] = LoadSprite(persy_combat_anim); break;
		default:
			break;
		}
	}

	for(size_t i = 0; i < cbtD.playerTeam->members.size(); ++i){
		auto &spr = CombatData::actorSprites[cbtD.playerTeam->members[i]];
		spr.pos = {440 + i * 64, 360}; //FIXME: magic numbers!
		spr.anims["Combat Idle"].looping = true;
		spr.playAnimation("Combat Idle");
	}

	for(size_t i = 0; i < cbtD.playerTeam->members.size(); ++i){
		auto &spr = CombatData::actorSprites[cbtD.playerTeam->members[i]];
		switch(i){
		case 0:
			spr.texture = LoadTexture("../img/cassandra_combat.png");
			break;
		case 1:
			spr.texture = LoadTexture("../img/gordon_combat.png");
			break;
		case 2:
			spr.texture = LoadTexture("../img/lou_combat.png");
			break;
		case 3:
			spr.texture = LoadTexture("../img/persy_combat.png");
			break;
		default:
			break;
		}
	}
}


void GoonSpriteSetup(CombatData &cbtD){
	CombatData::actorSprites[cbtD.botTeam->members[0]] = LoadSprite(metis_combat_anim);
	auto &spr0 = CombatData::actorSprites[cbtD.botTeam->members[0]];
	spr0.pos = {248, 232};
	spr0.anims["Combat Idle"].looping = true;

	CombatData::actorSprites[cbtD.botTeam->members[1]] = LoadSprite(callisto_combat_anim);
	auto &spr1 = CombatData::actorSprites[cbtD.botTeam->members[1]];
	spr1.pos = {312, 232};
	spr1.anims["Combat Idle"].looping = true;

	spr0.playAnimation("Combat Idle");
	spr1.playAnimation("Combat Idle");

	spr0.texture = LoadTexture("../img/metis_combat.png");
	spr1.texture = LoadTexture("../img/callisto_combat.png");
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
	allInCombat.reserve(CombatData::playerAlive.size() + CombatData::botAlive.size());

	for(auto &it : CombatData::playerAlive)
		allInCombat.push_back(it);
	for(auto &it : CombatData::botAlive)
		allInCombat.push_back(it);

	//O(n^2) 
	for(auto &it : allInCombat){
		bool found = false;
		for(auto &jt : CombatData::ctps){
			if(it == jt.caster){
				found = true;
				break;
			}
		}
		if(!found)
			return false;
	}

	BeginExecMoves();
	return true;
}


bool LessThanCTP(CasterTargetsPair *first, CasterTargetsPair *second){
	//TODO: DONT FORGET SLOWING
	int priorities[2] = {first->move->priority, second->move->priority};

	for(auto &it : CombatData::effects[first->caster]){
		if(it.id == QUICKSILVER)
			priorities[0] -= (int)GetEffectPrimaryBuff(it.id);
	}
	for(auto &it : CombatData::effects[second->caster]){
		if(it.id == QUICKSILVER)
			priorities[1] -= (int)GetEffectPrimaryBuff(it.id);
	}

	return priorities[0] < priorities[1];
}


void BeginExecMoves(){
	if(!CombatData::executingMoves){
		ResetSelectAvailList();

		CombatData::ctpsPtrs.resize(0);
		CombatData::ctpsPtrs.reserve(CombatData::ctps.size());
		for(auto &it : CombatData::ctps)
			CombatData::ctpsPtrs.push_back(&it);

		std::sort(CombatData::ctpsPtrs.begin(), CombatData::ctpsPtrs.end(), LessThanCTP); //sort on priority 

		CombatData::execIndex = 0;
		CombatData::executingMoves = true;
	}
}


//NOTE: July 31, 2020
//This function will execute a move and play the corresponding animations and sounds
//TODO: play the corresponding sounds
void ExecMoves(CombatData &cbtD){
	ExecMove(*CombatData::ctpsPtrs[cbtD.execIndex]);

	std::string announcment = "";
	auto &ctp = CombatData::ctpsPtrs[cbtD.execIndex];
	announcment += ctp->caster->name + " uses " + ctp->move->name + " on ";
	for(size_t i = 0; i < ctp->targets.size(); ++i){
		if(i > 1)
			announcment += ", " + ctp->targets[i]->name;
		else
			announcment += ctp->targets[i]->name;
	}
	announcment += ".";
	CombatData::moveAnnouncment.text = announcment;
	int w = GetGuiTextWidth(CombatData::moveAnnouncment.text.c_str());
	Rectangle rect = {(float)(SCREENWIDTH / 2 - w / 2 - 8), (float)(SCREENHEIGHT / 4 - GuiGetStyle(DEFAULT, TEXT_SIZE) - 8), (float)(w + 16), (float)(GuiGetStyle(DEFAULT, TEXT_SIZE) * 2)};
	CombatData::moveAnnouncment.bgBounds = rect;
	CombatData::moveAnnouncment.bounds = rect;
	CombatData::moveAnnouncment.disabled = false;
	CombatData::moveAnnouncment.alignment = GUI_TEXT_ALIGN_CENTER;

	cbtD.execIndex++;
	
	cbtD.executingMoves = cbtD.execIndex < CombatData::ctpsPtrs.size();
	cbtD.aiMakePairs = !cbtD.executingMoves;
}


void ExecMove(CasterTargetsPair &ctp){
	bool playedCasterAnim = false;
	for(auto &it : ctp.targets){
		switch(ctp.move->id){
		case IGNITE:
			MoveImplementation::IGNITE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BLAZE:
			MoveImplementation::BLAZE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FIREBALL:
			MoveImplementation::FIREBALL(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case EXPLOSION:
			MoveImplementation::EXPLOSION(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FIREBEAM:
			MoveImplementation::FIREBEAM(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FLAMESWORD:
			MoveImplementation::FLAMESWORD(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FLAREKICK:
			MoveImplementation::FLAREKICK(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FIREWALL:
			MoveImplementation::FIREWALL(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SEARINGFLESH:
			MoveImplementation::SEARINGFLESH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case MOLTENMETEOR:
			MoveImplementation::MOLTENMETEOR(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case WILDFIRE:
			MoveImplementation::WILDFIRE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case RAZEEARTH:
			MoveImplementation::RAZEEARTH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FROMTHEASHES:
			MoveImplementation::FROMTHEASHES(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SUPERNOVA:
			MoveImplementation::SUPERNOVA(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case WATERWHIP:
			MoveImplementation::WATERWHIP(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case TORRENT:
			MoveImplementation::TORRENT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case TIDALWAVE:
			MoveImplementation::TIDALWAVE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case COALESCE:
			MoveImplementation::COALESCE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case WHIRLPOOL:
			MoveImplementation::WHIRLPOOL(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case HAILSTORM:
			MoveImplementation::HAILSTORM(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case AQUAPRISON:
			MoveImplementation::AQUAPRISON(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case RAINSTORM:
			MoveImplementation::RAINSTORM(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DEWPOINT:
			MoveImplementation::DEWPOINT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FLASHFREEZE:
			MoveImplementation::FLASHFREEZE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case RIPTIDE:
			MoveImplementation::RIPTIDE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case VAPORVORTEX:
			MoveImplementation::VAPORVORTEX(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case HELLBROTH:
			MoveImplementation::HELLBROTH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case TSUNAMI:
			MoveImplementation::TSUNAMI(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SEEDSHOT:
			MoveImplementation::SEEDSHOT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ACORNASSAULT:
			MoveImplementation::ACORNASSAULT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SAPPINGSTEMS:
			MoveImplementation::SAPPINGSTEMS(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case NOURISH:
			MoveImplementation::NOURISH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case LEAFLANCE:
			MoveImplementation::LEAFLANCE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FUNGALSPORES:
			MoveImplementation::FUNGALSPORES(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BARBEDHUSK:
			MoveImplementation::BARBEDHUSK(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case GRASSBLADES:
			MoveImplementation::GRASSBLADES(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PETALPIKE:
			MoveImplementation::PETALPIKE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case UNDERGROWTH:
			MoveImplementation::UNDERGROWTH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SYMBIOSIS:
			MoveImplementation::SYMBIOSIS(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ENSNARINGVINE:
			MoveImplementation::ENSNARINGVINE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case RANCIDROSES:
			MoveImplementation::RANCIDROSES(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DRYADSCURSE:
			MoveImplementation::DRYADSCURSE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ZAP:
			MoveImplementation::ZAP(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CHARGE:
			MoveImplementation::CHARGE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DISCHARGE:
			MoveImplementation::DISCHARGE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case LIGHTNINGBOLT:
			MoveImplementation::LIGHTNINGBOLT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DAZZLINGLIGHTS:
			MoveImplementation::DAZZLINGLIGHTS(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ELECTROSTORM:
			MoveImplementation::ELECTROSTORM(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case LIGHTNINGKICK:
			MoveImplementation::LIGHTNINGKICK(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SPARKINGSKIN:
			MoveImplementation::SPARKINGSKIN(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SUPERCONDUCT:
			MoveImplementation::SUPERCONDUCT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case STATICSHOCK:
			MoveImplementation::STATICSHOCK(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case EVANESCENTFIELD:
			MoveImplementation::EVANESCENTFIELD(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case HIGHVOLTAGE:
			MoveImplementation::HIGHVOLTAGE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case MJOLNIR:
			MoveImplementation::MJOLNIR(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CLOSEDCIRUIT:
			MoveImplementation::CLOSEDCIRUIT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case IRONSPIKES:
			MoveImplementation::IRONSPIKES(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CANNONBALL:
			MoveImplementation::CANNONBALL(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SHARPEN:
			MoveImplementation::SHARPEN(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SHATTERSHRAPNEL:
			MoveImplementation::SHATTERSHRAPNEL(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BALLANDCHAIN:
			MoveImplementation::BALLANDCHAIN(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case QUICKSILVER:
			MoveImplementation::QUICKSILVER(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case COPPERCUTLASS:
			MoveImplementation::COPPERCUTLASS(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case RAZORWIRE:
			MoveImplementation::RAZORWIRE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case MIDASTOUCH:
			MoveImplementation::MIDASTOUCH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CHROMEPLATED:
			MoveImplementation::CHROMEPLATED(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case MAGNETIZE:
			MoveImplementation::MAGNETIZE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BRASSKNUCKLES:
			MoveImplementation::BRASSKNUCKLES(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ALLOYASSAULT:
			MoveImplementation::ALLOYASSAULT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PIERCINGPLATINUM:
			MoveImplementation::PIERCINGPLATINUM(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case HURLROCK:
			MoveImplementation::HURLROCK(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case STONESPEAR:
			MoveImplementation::STONESPEAR(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FORTIFY:
			MoveImplementation::FORTIFY(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case QUICKSAND:
			MoveImplementation::QUICKSAND(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ENTOMB:
			MoveImplementation::ENTOMB(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CRUSH:
			MoveImplementation::CRUSH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case TREMOR:
			MoveImplementation::TREMOR(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ROCKSLIDE:
			MoveImplementation::ROCKSLIDE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ROLLINGBOULDER:
			MoveImplementation::ROLLINGBOULDER(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SAPPHIRESTRIKE:
			MoveImplementation::SAPPHIRESTRIKE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case RUBYRUSH:
			MoveImplementation::RUBYRUSH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case GARNETGAZE:
			MoveImplementation::GARNETGAZE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case EMERALDEDGE:
			MoveImplementation::EMERALDEDGE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case OBSIDIANONSLAUGHT:
			MoveImplementation::OBSIDIANONSLAUGHT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ECTORAY:
			MoveImplementation::ECTORAY(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case TORMENT:
			MoveImplementation::TORMENT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CHAOSCLAW:
			MoveImplementation::CHAOSCLAW(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PHANTOMWALTS:
			MoveImplementation::PHANTOMWALTS(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case GRAVETENDER:
			MoveImplementation::GRAVETENDER(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case MINDINVASION:
			MoveImplementation::MINDINVASION(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BINDINGPAIN:
			MoveImplementation::BINDINGPAIN(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PLAGUE:
			MoveImplementation::PLAGUE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case WICKEDHEX:
			MoveImplementation::WICKEDHEX(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PETRIFYINGWAIL:
			MoveImplementation::PETRIFYINGWAIL(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DECAY:
			MoveImplementation::DECAY(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case VIVIDNIGHTMARE:
			MoveImplementation::VIVIDNIGHTMARE(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ETHEREALFOG:
			MoveImplementation::ETHEREALFOG(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case NOXIOUSVOID:
			MoveImplementation::NOXIOUSVOID(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FLASHFRICTION:
			MoveImplementation::FLASHFRICTION(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SCORCHINGHEAT:
			MoveImplementation::SCORCHINGHEAT(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DRAGONBREATH:
			MoveImplementation::DRAGONBREATH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ICARUSINFERNO:
			MoveImplementation::ICARUSINFERNO(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case REND:
			MoveImplementation::REND(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SIRENSTEAR:
			/* MoveImplementation::SIRENSTEAR(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CHILLINGBLAST:
			/* MoveImplementation::CHILLINGBLAST(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case DELUGE:
			/* MoveImplementation::DELUGE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case NEEDLE:
			/* MoveImplementation::NEEDLE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BLOOM:
			/* MoveImplementation::BLOOM(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case TREECLEAVER:
			/* MoveImplementation::TREECLEAVER(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case VENOMCOATING:
			/* MoveImplementation::VENOMCOATING(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SURGE:
			/* MoveImplementation::SURGE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case OVERLOAD:
			/* MoveImplementation::OVERLOAD(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case IONSTRIKE:
			/* MoveImplementation::IONSTRIKE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PLASMAPULSE:
			/* MoveImplementation::PLASMAPULSE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SCRAPSLUG:
			/* MoveImplementation::SCRAPSLUG(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ANNEAL:
			/* MoveImplementation::ANNEAL(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case ANODIZE:
			/* MoveImplementation::ANODIZE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case GALVANIZEDGLAIVE:
			/* MoveImplementation::GALVANIZEDGLAIVE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case GRAVELSPIN:
			/* MoveImplementation::GRAVELSPIN(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SANDBOMB:
			/* MoveImplementation::SANDBOMB(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case CRYSTALCAGE:
			/* MoveImplementation::CRYSTALCAGE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case FISSURE:
			/* MoveImplementation::FISSURE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case SHADOWSLASH:
			MoveImplementation::SHADOWSLASH(*it, *static_cast<CasterMove *>(&ctp));
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case PILFER:
			/* MoveImplementation::PILFER(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Physical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BLOODCURDLE:
			/* MoveImplementation::BLOODCURDLE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
			break;
		case BLACKHOLE:
			/* MoveImplementation::BLACKHOLE(*it, *static_cast<CasterMove *>(&ctp)); */
			{
				if(!playedCasterAnim){
					CombatData::actorSprites[ctp.caster].playAnimation("Use Magical", 
						[](){ CombatData::animLockouts--; }
					);
					playedCasterAnim = true;
					CombatData::animLockouts++;
				}
			}
			CombatData::actorSprites[it].playAnimation("Hurt", 8, 
				[](){ CombatData::animLockouts--; }
			);
			CombatData::animLockouts++;
		default:
			break;
		}
	}
	CombatData::moveAnimPlaying = true;
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


void ResetSelectAvailList(){
	CombatData::chosenTargets.resize(0);
	CombatData::potTargets.resize(0);
	CombatData::targetAliveList.text.resize(0);
	CombatData::targetSelectedList.text.resize(0);
}


void ApplyEffect(Actor &target, int id){

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

