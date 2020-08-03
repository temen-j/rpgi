#include "..\include\game.h"
#include "..\include\moveinventory.h"


GameState Game::gamestate;
Mouse Game::mouse;
TextureManager Game::textures;

unsigned int Game::delay = 0;

Game::Game(){
	justEnteredState = false;
	consoleOpen = false;
	inventoryOpen = false;
	minventoryOpen = false;
	Vector2 addPos[NUM_RECT];
	for(size_t i = 0; i < NUM_RECT; ++i){
		addPos[i] = 
			(Vector2){(float)(i % 4) * RECT_WIDTH, (float)(i / 4) * RECT_WIDTH} +
			(Vector2){RECT_WIDTH / 2, RECT_WIDTH / 2}; //Centers anchors
	}
	for(size_t i = 0; i < 4; ++i){
		for(size_t j = 0; j < 3; ++j){
			gridMat[i][j].disabled = false;
			gridMat[i][j].pos = (Vector2){GRID_PADDING, 32 + (float)j * 7 * RECT_WIDTH}; //FIXME: magic numbers!

			for(size_t k = 0; k < NUM_RECT; ++k)
				gridMat[i][j].anchors[k].pos = gridMat[i][j].pos + addPos[k];
		}
	}
}


Game::~Game(){
}


int InventoryState(Game &game){
	Player &player = game.player;

	if(!player.invData){
		player.invData = new InventoryData(); //ewww heap alloc
		OpenInventory(game);
	}

	unsigned char prevFocus = player.invData->focus;
	HandleInventoryPortraits(*player.invData);
	if(prevFocus != player.invData->focus){
		player.invData->grids = game.gridMat[player.invData->focus];
		UpdateStatText(*player.invData, *player.team.members[player.invData->focus]);
	}

	bool prevPlusPage = player.invData->plusPage.pressed;
	Update(player.invData->plusPage);
	if(!prevPlusPage && player.invData->plusPage.pressed){
		int max = player.invData->eleminoesAvail.size() / player.invData->MAX_INV_DISP;
		max = player.invData->eleminoesAvail.size() % player.invData->MAX_INV_DISP > 0 ? max : max - 1;
		if(player.invData->page < max){
			player.invData->page++;
			UpdateInteractable(player);
			PositionEleminoes(*player.invData);
		}
	}

	bool prevMinusPage = player.invData->minusPage.pressed;
	Update(player.invData->minusPage);
	if(!prevMinusPage && player.invData->minusPage.pressed){
		if(player.invData->page > 0){
			player.invData->page--;
			UpdateInteractable(player);
			PositionEleminoes(*player.invData);
		}
	}

	int prevActive = player.invData->elemdd.active;
	Update(player.invData->elemdd);
	if(prevActive != player.invData->elemdd.active){
		UpdateInteractable(player);
		PositionEleminoes(*player.invData);
	}

	CheckForEleminoClicked(game);
	MouseTouchElemino(game);
	HandleFlyingElemino(game);


	Unoccupy(player.invData->grids[0]);
	Unoccupy(player.invData->grids[1]);
	Unoccupy(player.invData->grids[2]);

	StatToolTip(*player.invData, Character::actors[player.invData->focus]);

	return 0;
}


int MoveInventoryState(Game &game){
	Player *player = &game.player;

	if(!player->minvData){
		player->minvData = new MoveInventoryData(); //ewww heap alloc
		OpenMoveInventory(game);
	}

	unsigned char prevFocus = player->minvData->focus;
	HandleInventoryPortraits(*(player->minvData));
	if(prevFocus != player->minvData->focus){
		GetCurrent(game.player);
		GetAvailable(game.player);

		SetupListView(game.player.minvData->movesCurrList);
		SetupListView(game.player.minvData->movesAvailList);
	}

	int prevActiveAvail = game.player.minvData->movesAvailList.active;
	int prevActiveCurr = game.player.minvData->movesCurrList.active;
	Update(game.player.minvData->movesCurrList);
	Update(game.player.minvData->movesAvailList);

	if(game.player.minvData->movesAvailList.active == -1 && game.player.minvData->movesAvailList.active != prevActiveAvail){
		AddToCurrentMoves(game.player, prevActiveAvail);
		game.player.minvData->info = 0;
		SetupMoveInfo(*game.player.minvData);
	}
	else if(game.player.minvData->movesAvailList.active != prevActiveAvail){
		game.player.minvData->info = 1;
		SetupMoveInfo(*game.player.minvData);
	}
	if(game.player.minvData->movesCurrList.active == -1 && game.player.minvData->movesCurrList.active != prevActiveCurr){
		RemoveFromCurrentMoves(game.player, prevActiveCurr);
		game.player.minvData->info = 1;
		SetupMoveInfo(*game.player.minvData);
	}
	else if(game.player.minvData->movesCurrList.active != prevActiveCurr){
		game.player.minvData->info = 0;
		SetupMoveInfo(*game.player.minvData);
	}

	return 0;
}


int CombatState(Game &game){
	if(!game.cbtData){
		game.cbtData = new CombatData();
		StartCombat(game);
	}

	bool prevMoveAnimPlaying = CombatData::moveAnimPlaying;
	CombatData::moveAnimPlaying = CombatData::animLockouts > 0;

	if(Game::gamestate.curr == State::combat_act){
		if(game.cbtData->aiMakePairs)
			AIMakeCTPs(*game.cbtData);
		
		unsigned char prevFocus = game.cbtData->focus;
		HandleCombatPortraits(*game.cbtData);

		if(prevFocus != game.cbtData->focus){
			GetAffordableMoves(*game.cbtData->playerTeam->members[game.cbtData->focus], game.cbtData->affordable);
			MoveButtonsTextSetup(*game.cbtData);
		}

		SelectMoves(*game.cbtData);

		if(game.cbtData->canAssign){
			game.cbtData->dispTargetLists = true;
			AssignTargets(*game.cbtData);
		}
		if(game.cbtData->canMakePair){
			MakeCTP(*game.cbtData);
		}
		if(CanExecMoves(*game.cbtData)){ //You are now watching a movie :)
			for(auto &it : CombatData::hasMoveChosen)
				it.second = false;

			CombatData::announceMove = true;
			Game::gamestate.prev = Game::gamestate.curr;
			Game::gamestate.curr = State::combat_watch;
		}
	}
	if(Game::gamestate.curr == State::combat_watch){
		static UMap<Actor *, float> prevHP; //For interpolating the stat bars
		static UMap<Actor *, float> prevMP;

		CombatData::interpStats = CombatData::interpStats || (prevMoveAnimPlaying != CombatData::moveAnimPlaying && !CombatData::moveAnimPlaying); //Ending moveAnimPlaying

		FindExecutableCTP();

		if(!CombatData::moveAnimPlaying && !CombatData::interpStats && !CombatData::announceMove && CombatData::executingMoves){
			for(auto &it : CombatData::playerAlive){
				prevHP[it] = (float)it->remHP / it->maxHP;
				prevMP[it] = (float)it->remMP / it->maxMP;
			}
			CombatData::statBarInterpTimer = 0.f;
			ExecMoves(*game.cbtData);
		}

		//TODO: Tick Effects here!
		//TODO: Resolve deaths

		if(CombatData::announceMove && CombatData::executingMoves)
			AnnounceMove(*game.cbtData); //Announce the move used on which actors

		if(CombatData::interpStats){
			InterpolateStatBars(prevHP, prevMP); //modifies interpStats, and announcMove
			if(!CombatData::interpStats)
				ResolveDeaths();
		}

		if(!CombatData::executingMoves){ //Stopped exec moves go back to input
			CombatData::ctps.clear();
			GetAffordableMoves(*CombatData::playerTeam->members[game.cbtData->focus], game.cbtData->affordable);

			Game::gamestate.prev = Game::gamestate.curr;
			Game::gamestate.curr = State::combat_act;
		}
	}

	for(auto &it : CombatData::actorSprites){
		Update(it.second);
		if(!it.second.currAnim)
			it.second.playAnimation("Combat Idle");
	}

	//TODO: End the battle and delete goons
	return 0;
}


