/* #include "..\include\combat.h" */
#include "..\include\game.h"

#include "..\include\embed\cassandra_combat_sprite.h"
#include "..\include\embed\gordon_combat_sprite.h"
#include "..\include\embed\lou_combat_sprite.h"
#include "..\include\embed\persy_combat_sprite.h"

#include "..\include\embed\metis_combat_sprite.h"
#include "..\include\embed\callisto_combat_sprite.h"

#include "..\include\sprite.h"


CasterTargetsPair::CasterTargetsPair(Actor *c, struct Move *m, const Vec<Actor *> &t){
	caster = c;
	move = m;
	targets = t;
}


void CombatData::StartCombat(Team *playerTeam, Team *botTeam){
	focus = 0;

	portraits.toggles.resize(4);
	portraits.toggles[0].active = true;
	//FIXME: Use the texture manager instead of loading them with each state change
	portraits.toggles[0].texture = LoadTexture("../img/cassandra_dev.png");
	portraits.toggles[1].texture = LoadTexture("../img/gordon_dev.png");
	portraits.toggles[2].texture = LoadTexture("../img/lou_dev.png");
	portraits.toggles[3].texture = LoadTexture("../img/persy_dev.png");
	halo = LoadTexture("../img/portrait_halo.png");

	for(size_t i = 0; i < 4; ++i){
		auto toggle = &portraits.toggles[i];
		toggle->bounds =
			(Rectangle){PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING), PORTRAIT_WIDTH, PORTRAIT_WIDTH};
	}

	CombatData::playerTeam = playerTeam;

	CombatSpriteSetup();

	CreateGoons();
	TeamsSetup();

	GoonSpriteSetup();

	effects.clear();
	for(auto &it : playerAlive)
		effects.emplace(it, Vec<MoveEffect>());
	for(auto &it : botAlive)
		effects.emplace(it, Vec<MoveEffect>());

	statusEffects.clear();
	for(auto &it : playerAlive)
		statusEffects.emplace(it, StatusEffects());
	for(auto &it : botAlive)
		statusEffects.emplace(it, StatusEffects());

	MoveButtonsSetup();

	chosenMove = nullptr;
	aiMakePairs = true;

	for(auto &it : playerAlive)
		hasMoveChosen[it] = false;

	targetSelectedList.bounds = (Rectangle){256, 64, 192, 192};
	targetAliveList.bounds = (Rectangle){256 + 192 + 128, 64, 192, 192};

	//TODO: Also call this when returning to phase 1
	GetAffordableMoves(*CombatData::playerTeam->members[focus], affordable);

	for(unsigned int i = 0; i < playerAlive.size(); ++i){
		Rectangle hpBounds = {PORTRAIT_WIDTH + 2 * PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING + PORTRAIT_PADDING / 2), STATBAR_WIDTH, STATBAR_HEIGHT};
		Rectangle mpBounds = {PORTRAIT_WIDTH + 2 * PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING +  PORTRAIT_PADDING / 2 + STATBAR_HEIGHT * 2), STATBAR_WIDTH, STATBAR_HEIGHT};
		statBars[playerAlive[i]][0] = StatBar(1.f, hpBounds, playerAlive[i]->maxHP, HPGOODCOLOR, HPBADCOLOR);
		statBars[playerAlive[i]][1] = StatBar(1.f, mpBounds, playerAlive[i]->maxMP, MPGOODCOLOR, MPBADCOLOR);
	}

	for(unsigned int i = 0; i < botAlive.size(); ++i){
		Rectangle hpBounds = {960 - PORTRAIT_PADDING - STATBAR_WIDTH / 2, (float)(i * PORTRAIT_PADDING * 2), STATBAR_WIDTH / 2, STATBAR_HEIGHT / 4};
		Rectangle mpBounds = {960 - PORTRAIT_PADDING - STATBAR_WIDTH / 2, (float)(i * PORTRAIT_PADDING  * 2 + PORTRAIT_PADDING), STATBAR_WIDTH / 2, STATBAR_HEIGHT / 4};
		statBars[botAlive[i]][0] = StatBar(1.f, hpBounds, HPGOODCOLOR, HPBADCOLOR);
		statBars[botAlive[i]][1] = StatBar(1.f, mpBounds, MPGOODCOLOR, MPBADCOLOR);
	}

	moveAnnouncement.text = "";
	moveAnnouncement.bounds = {0,0,0,0};
	moveAnnouncement.bgColor = (Color){28, 33,  35, 200};
	moveAnnouncement.textColor = (Color){219, 219, 235, 255};
	moveAnnouncement.disabled = true;

	endExec = false;
}


void CombatData::AIMakeCTPs(){
	for(unsigned int i = 0; i < botAlive.size(); ++i){ //FIXME: turn into for-range
		Vec<Actor *> targets;
		struct Move *move = botAlive[i]->moves[0];

		if(move->maxTargets == TARGET_ALL_ACTORS){
			targets.reserve(playerAlive.size() + botAlive.size());

			for(auto &it : playerAlive)
				targets.push_back(it);
			for(auto &it : botAlive)
				targets.push_back(it);
		}
		else if(move->maxTargets == TARGET_SELF){
			targets.push_back(botAlive[i]);
		}
		else if(move->isFriendly){
			for(int j = 0; j < move->maxTargets; ++j) //Take the first actors it can
				targets.push_back(botAlive[j]);
		}
		else if(move->isHostile){
			for(int j = 0; j < move->maxTargets; ++j) //Take the first actors it can
				targets.push_back(playerAlive[j]);
		}

		ctps.push_back(CasterTargetsPair(botAlive[i], move, targets));
	}
	aiMakePairs = false;
}


void CombatData::SelectMoves(){
	auto &actor = playerTeam->members[focus];

	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		Update(moveButtons[i]);
		if(moveButtons[i].state == GuiControlState::GUI_STATE_PRESSED && affordable){
			for(size_t j = 0; j < NUM_ACTOR_MOVES; ++j){
				if(actor->moves[i] && actor->moves[i] == affordable[j]){ //If the selection is in the affordable move list
					chosenMove = actor->moves[i];
					canAssign = true;
					break;
				}
			}
			break;
		}
	}
}


void CombatData::GetAffordableMoves(Actor &actor, struct Move **affordable){
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


void CombatData::AssignTargets(){
	//Make a macro-loop
	if(!begunAssigning){
		AssignTargetsSetup();
	}
	if((int)chosenTargets.size() < chosenMove->maxTargets){
		//Detect changes in selection and add/remove the list
		int prevActiveAlive = targetAliveList.active;
		int prevActiveSelect = targetSelectedList.active;
		Update(targetAliveList);
		Update(targetSelectedList);

		if(prevActiveAlive != -1 && targetAliveList.active != prevActiveAlive)
			AddFromAliveList(prevActiveAlive);
		if(prevActiveSelect != -1 && targetSelectedList.active != prevActiveSelect)
			RemoveFromSelectedList(prevActiveSelect);
	}
	else{
		canMakePair = true;
		canAssign = false;
	}
}


void CombatData::AssignTargetsSetup(){
	//TODO: Add checks for maxTargets == all enemies
	if(chosenMove->maxTargets == TARGET_ALL_ACTORS){
		chosenTargets.reserve(playerAlive.size() + botAlive.size());
		for(auto &it : playerAlive)
			chosenTargets.push_back(it);
		for(auto &it : botAlive)
			chosenTargets.push_back(it);
		
		targetAliveList.text.push_back("ALL");
	}
	ResetSelectAvailList();

	//Get potential targets
	if(chosenMove->isFriendly){ //Potential optimization: potTargets.reserve(is... * ...Alive.size())
		for(auto it : playerAlive)
			potTargets.push_back(it);
	}
	if(chosenMove->isHostile){
		for(auto it : botAlive)
			potTargets.push_back(it);
	}
	
	targetAliveList.text.reserve(potTargets.size());
	for(auto &it : potTargets) //TODO: Make this into a function, (GetAliveList())
		targetAliveList.text.push_back(it->name);

	//Populate list views with
	SetupListView(targetAliveList);
	SetupListView(targetSelectedList);

	begunAssigning = true;
}


void CombatData::MakeCTP(){
	auto &actor = playerTeam->members[focus];
	ctps.emplace(ctps.begin(), CasterTargetsPair(actor, chosenMove, chosenTargets));
	dispTargetLists = false;
	begunAssigning = false;

	hasMoveChosen[actor] = true;

	chosenMove = nullptr;
	chosenTargets.clear();

	canMakePair = false;
}


void CombatData::AddFromAliveList(int &prevActive){
	chosenTargets.push_back(potTargets[prevActive]);
	targetSelectedList.text.push_back(targetAliveList.text[prevActive]);
	SetupListView(targetSelectedList);
}


void CombatData::RemoveFromSelectedList(int &prevActive){
	chosenTargets.erase(chosenTargets.begin() + prevActive);
	targetSelectedList.text.erase(targetSelectedList.text.begin() + prevActive);
	SetupListView(targetSelectedList);
}


void CombatData::HandleCombatPortraits(){
	bool isToggled[8] = {false}; //Keep track of previous activation

	for(size_t i = 0; i < 8; ++i) //FIXME: magic numbers!
		isToggled[i] = portraits.toggles[i].active;

	for(size_t i = 0; i < playerTeam->members.size(); ++i){
		bool update = Update(portraits.toggles[i]); //a group toggling

		auto actor = playerTeam->members[i];
		if((isToggled[i] && hasMoveChosen[actor]) || actor->remHP == 0){ //If an actor is already selected and has chosen a move

			for(size_t j = 0; (j < playerTeam->members.size() && hasMoveChosen[actor]) || actor->remHP == 0; ++j){ //Cycle through characters who have yet to select moves
				i = (i + 1) % playerTeam->members.size();
				actor = playerTeam->members[i];
				portraits.toggles[i].active = true;
				focus = i;
			}

			for(size_t j = 0; j < playerAlive.size(); ++j){
				if(j != i) //Turn the others in the toggle group off
					portraits.toggles[j].active = false;
			}
			break;
		}

		if(update != isToggled[i]){
			if(update){
				focus = i;
				for(size_t j = 0; j < 4; ++j){
					if(j != i) //Turn the others in the toggle group off
						portraits.toggles[j].active = false;
				}
				break;
			}
			else
				portraits.toggles[i].active = true;
		}
	}
}


void CombatData::MoveButtonsSetup(){
	Vector2 pos = {96, 448};
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		moveButtons[i].bounds = (Rectangle){pos.x + (176 * (i % 4)), pos.y + (80 * (i / 4)), 160, 64}; //FIXME: magic numbers!
	}

	MoveButtonsTextSetup();
}


void CombatData::MoveButtonsTextSetup(){
	Actor *actor = playerTeam->members[focus];
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		moveButtons[i].text = "";
		if(actor->moves[i])
			moveButtons[i].text = actor->moves[i]->name;
		else
			break; //early exit b/c moves should always be valid until 1+ nullptr at the end
	}
}


void CombatData::TeamsSetup(){
	for(unsigned int i = 0; i < playerTeam->members.size(); ++i){
		Actor *actor = playerTeam->members[i];
		if(!IsDead(*actor))
			playerAlive.push_back(actor);
	}
	for(unsigned int i = 0; i < botTeam->members.size(); ++i){
		Actor *actor = botTeam->members[i];
		if(!IsDead(*actor))
			botAlive.push_back(actor);
	}
}


void CombatData::CombatSpriteSetup(){
	/* actorSprites[playerTeam->members[0]] = LoadSprite(cassandra_combat_anim); */ 
	
	//FIXME: kind of hacky, need to store looping in the anim file and embedded file
	for(size_t i = 0; i < playerTeam->members.size(); ++i){
		switch(i){
		case 0:
			actorSprites[playerTeam->members[i]] = LoadSprite(cassandra_combat_anim); break;
		case 1:
			actorSprites[playerTeam->members[i]] = LoadSprite(gordon_combat_anim); break;
		case 2:
			actorSprites[playerTeam->members[i]] = LoadSprite(lou_combat_anim); break;
		case 3:
			actorSprites[playerTeam->members[i]] = LoadSprite(persy_combat_anim); break;
		default:
			break;
		}
	}

	for(size_t i = 0; i < playerTeam->members.size(); ++i){
		auto &spr = actorSprites[playerTeam->members[i]];
		spr.pos = {(float)(440 + i * 64), (float)360}; //FIXME: magic numbers!
		spr.anims["Combat Idle"].looping = true;
		spr.playAnimation("Combat Idle");
	}

	for(size_t i = 0; i < playerTeam->members.size(); ++i){
		auto &spr = actorSprites[playerTeam->members[i]];
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


void CombatData::GoonSpriteSetup(){
	actorSprites[botTeam->members[0]] = LoadSprite(metis_combat_anim);
	auto &spr0 = actorSprites[botTeam->members[0]];
	spr0.pos = {248, 232};
	spr0.anims["Combat Idle"].looping = true;

	actorSprites[botTeam->members[1]] = LoadSprite(callisto_combat_anim);
	auto &spr1 = actorSprites[botTeam->members[1]];
	spr1.pos = {312, 232};
	spr1.anims["Combat Idle"].looping = true;

	spr0.playAnimation("Combat Idle");
	spr1.playAnimation("Combat Idle");

	spr0.texture = LoadTexture("../img/metis_combat.png");
	spr1.texture = LoadTexture("../img/callisto_combat.png");
}


void CombatData::DisableUnusedButtons(){
	Actor *actor = playerTeam->members[focus];
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(actor->moves[i])
			moveButtons[i].state = GuiControlState::GUI_STATE_NORMAL;
		else
			moveButtons[i].state = GuiControlState::GUI_STATE_DISABLED;
	}
}


bool CombatData::CanExecMoves(){
	Vec<Actor *> allInCombat;
	allInCombat.reserve(playerAlive.size() + botAlive.size());

	for(auto &it : playerAlive)
		allInCombat.push_back(it);
	for(auto &it : botAlive)
		allInCombat.push_back(it);

	//O(n^2) 
	for(auto &it : allInCombat){
		bool found = false;
		for(auto &jt : ctps){
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


void CombatData::BeginExecMoves(){
	if(!executingMoves){
		ResetSelectAvailList();

		/* ctpsPtrs.resize(0); */
		ctpsPtrs.clear();
		ctpsPtrs.reserve(ctps.size());
		for(auto &it : ctps)
			ctpsPtrs.push_back(&it);

		std::sort(ctpsPtrs.begin(), ctpsPtrs.end(), LessThanCTP); //sort on priority 

		execIndex = 0;
		executingMoves = true;
	}
}


//NOTE: August 2, 2020
//This function will execute a move by move
void CombatData::ExecMoves(){
	ExecMove(*ctpsPtrs[execIndex]);
	execIndex++;
	
	/* executingMoves = execIndex < ctpsPtrs.size(); */
	tickEffects = !(execIndex < ctpsPtrs.size());
}


//TODO: Make a tool that creates enemies
void CombatData::CreateGoons(){
	botTeam = new Team(); //ewww dynamic alloc...
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

	botTeam->members.push_back(foo);
	botTeam->members.push_back(bar);
}


void CombatData::ResetSelectAvailList(){
	chosenTargets.resize(0);
	potTargets.resize(0);
	targetAliveList.text.resize(0);
	targetSelectedList.text.resize(0);
}


void CombatData::BeginAnnounceMove(){
	auto &ctp = ctpsPtrs[execIndex];

	std::string announcment = "";
	announcment += ctp->caster->name + " uses " + ctp->move->name + " on ";
	for(size_t i = 0; i < ctp->targets.size(); ++i){
		if(i > 1)
			announcment += ", " + ctp->targets[i]->name;
		else
			announcment += ctp->targets[i]->name;
	}
	announcment += ".";
	moveAnnouncement.text = announcment;

	int w = GetGuiTextWidth(moveAnnouncement.text.c_str());
	Rectangle rect = {(float)(SCREENWIDTH / 2 - w / 2 - 8), (float)(SCREENHEIGHT / 4 - GuiGetStyle(DEFAULT, TEXT_SIZE) - 8), (float)(w + 16), (float)(GuiGetStyle(DEFAULT, TEXT_SIZE) * 2)};

	moveAnnouncement.bgBounds = rect;
	moveAnnouncement.bounds = rect;
	moveAnnouncement.disabled = false;
	moveAnnouncement.alignment = GUI_TEXT_ALIGN_CENTER;

	announcementTimer = 0.f;
}


void CombatData::AnnounceMove(){
	if(moveAnnouncement.disabled)
		BeginAnnounceMove();

	if(!moveAnnouncement.disabled){
		announcementTimer += GetFrameTime();
		announceMove = !(announcementTimer > announcementTime);
		moveAnnouncement.disabled = !announceMove;
	}
}


void CombatData::InterpolateStatBars(UMap<Actor *, float> &prevHP, UMap<Actor *, float> &prevMP){
	for(auto &it : playerAlive){
		float currHPnorm = (float)it->remHP / it->maxHP;
		float currMPnorm = (float)it->remMP / it->maxMP;

		float amtHP = EaseCircOut(statBarInterpTimer, prevHP[it], currHPnorm - prevHP[it], statBarInterpTime);
		float amtMP = EaseCircOut(statBarInterpTimer, prevMP[it], currMPnorm - prevMP[it], statBarInterpTime);

		statBars[it][0].k = amtHP;
		statBars[it][1].k = amtMP;
		statBars[it][0].denom = it->maxHP;
		statBars[it][1].denom = it->maxMP;
	}

	for(auto &it : botAlive){
		float currHPnorm = (float)it->remHP / it->maxHP;
		float currMPnorm = (float)it->remMP / it->maxMP;

		float amtHP = EaseCircOut(statBarInterpTimer, prevHP[it], currHPnorm - prevHP[it], statBarInterpTime);
		float amtMP = EaseCircOut(statBarInterpTimer, prevMP[it], currMPnorm - prevMP[it], statBarInterpTime);

		statBars[it][0].k = amtHP;
		statBars[it][1].k = amtMP;
	}

	statBarInterpTimer += GetFrameTime();
	interpStats = !(statBarInterpTimer > statBarInterpTime);

	announceMove = true; //After done moving stat bar, get ready to announce the next move
}


void CombatData::ResolveDeaths(){
	for(size_t i = 0; i < playerAlive.size(); ++i){
		auto &actor = playerAlive[i];
		if(actor && actor->remHP == 0){
			playerAlive.erase(playerAlive.begin() + i);
			i--;
		}
	}

	for(size_t i = 0; i < botAlive.size(); ++i){
		auto &actor = botAlive[i];
		if(actor && actor->remHP == 0){
			botAlive.erase(botAlive.begin() + i);
			i--;
		}
	}
}


void CombatData::FindExecutableCTP(){
	while(execIndex < ctpsPtrs.size() && ctpsPtrs[execIndex]->caster->remHP == 0)
		execIndex++;

	if(execIndex >= ctpsPtrs.size()){
		announceMove = false;
		moveAnnouncement.disabled = true;
		tickEffects = true;
	}
}

//NOTE: August 4, 2020. Tick all effects in one frame
void CombatData::TickEffects(){
	//Tick all effects first
	for(size_t i = ctpsPtrs.size()-1; i > 0; --i){
		auto &actor = ctpsPtrs[i]->caster;
		if(actor->remHP != 0){
			for(auto &jt : effects[actor])
				jt.Tick(actor);
		}
	}

	//Cleanup ones with no more duration
	for(auto &it : ctps){
		auto &eff = effects[it.caster];

		for(size_t i = 0; i < eff.size(); ++i){
			auto &meff = eff[i];

			if(meff.duration == 0){
				eff.erase(eff.begin() + i);
				i--;
			}
		}
	}

	tickEffects = false;
}


void CombatData::SetupStatBar(UMap<Actor *, float> &prevHP, UMap<Actor *, float> &prevMP){
	for(auto &it : CombatData::playerAlive){
		prevHP[it] = (float)it->remHP / it->maxHP;
		prevMP[it] = (float)it->remMP / it->maxMP;
	}
	for(auto &it : CombatData::botAlive){
		prevHP[it] = (float)it->remHP / it->maxHP;
		prevMP[it] = (float)it->remMP / it->maxMP;
	}
	statBarInterpTimer = 0.f;
}


void CombatData::EndExecution(){
	ctps.clear();
	GetAffordableMoves(*playerTeam->members[focus], affordable);
	
	moveAnimPlaying = interpStats = announceMove = tickEffects =
		endExec = executingMoves = false;

	moveAnnouncement.disabled = true;
	aiMakePairs = true;
}


