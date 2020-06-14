#include "include\moveinventory.h"
#include "include\move.h"
#include "include\game.h"

void OpenMoveInventory(Game &game){
	MoveInventoryData *minvData = game.player.minvData;

	minvData->focus = 0;

	minvData->portraits.toggles[0].active = true;
	minvData->portraits.toggles[0].texture = LoadTexture("../img/cassandra_dev.png");
	minvData->portraits.toggles[1].texture = LoadTexture("../img/gordon_dev.png");
	minvData->portraits.toggles[2].texture = LoadTexture("../img/lou_dev.png");
	minvData->portraits.toggles[3].texture = LoadTexture("../img/persy_dev.png");
	minvData->halo = LoadTexture("../img/portrait_halo.png");

	for(size_t i = 0; i < 4; ++i){
		ImageToggle *toggle = &minvData->portraits.toggles[i];
		toggle->bounds =
			(Rectangle){PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING), PORTRAIT_WIDTH, PORTRAIT_WIDTH};
	}
	minvData->moveInfo.bgColor = (Color){28, 33,  35, 200};
	minvData->moveInfo.textColor = (Color){219, 219, 235, 200};

	//FIXME: magic numbers!
	minvData->movesCurrList.bounds = (Rectangle){256, 64, 192, 192};
	minvData->movesAvailList.bounds = (Rectangle){256 + 192 + 128, 64, 192, 192};

	GetCurrent(game.player);
	GetAvailable(game.player);

	SetupListView(minvData->movesCurrList);
	SetupListView(minvData->movesAvailList);
}


void UnloadTexturesFrom(MoveInventoryData &minvData){
	for(size_t i = 0; i < 4; ++i){
		if(minvData.portraits.toggles[i].texture.id > 0)
			UnloadTexture(minvData.portraits.toggles[i].texture);
	}
	UnloadTexture(minvData.halo);
}


void HandleInventoryPortraits(MoveInventoryData &minvD){
	InventoryPortraits *invP = &minvD.portraits;
	//TODO: Make me work with int instead storing a bunch of bools
	bool isToggled[4]; //Keep track of previous activation
	for(size_t i = 0; i < 4; ++i)
		isToggled[i] = invP->toggles[i].active;

	for(size_t i = 0; i < 4; ++i){
		bool update = Update(invP->toggles[i]);
		if(update != isToggled[i] && !update && isToggled[i])
			invP->toggles[i].active = true;
		if(update != isToggled[i] && update){
			minvD.focus = i;
			for(size_t j = 0; j < 4; ++j){
				if(j != i) //Turn the others in the toggle group off
					invP->toggles[j].active = false;
			}
			break;
		}
	}
}


void GetCurrent(Player &player){
	GetCurrentMoves(player);
	GetCurrentList(player);
}


void GetCurrentMoves(Player &player){
	player.minvData->movesCurr.resize(0);
	Actor *actor = &Character::actors[player.minvData->focus];
	struct Move *move;
	player.minvData->movesCurr.resize(0);
	for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i){
		move = actor->moves[i];
		if(move)
			player.minvData->movesCurr.push_back(move);
	}
}


void GetCurrentList(Player &player){
	player.minvData->movesCurrList.text.resize(0);
	for(auto it: player.minvData->movesCurr)
		player.minvData->movesCurrList.text.push_back(it->name);
}


void GetAvailable(Player &player){
	GetAvailableMoves(player);
	GetAvailableList(player);
}


void GetAvailableMoves(Player &player){
	player.minvData->movesAvail.resize(0);
	Actor *actor = &Character::actors[player.minvData->focus];
	struct Move *move;
	//Go through all moves and add to the available list the ones that meet the criteria
	//Criteria: type, <= level, not in curr list
	for(size_t i = 0; i < NUM_MOVES; ++i){
		move = &AllMoves::moves[i];
		if((move->elem == actor->type[0] || move->elem == actor->type[1]) && move->levelObtained <= player.level &&
				(move->owner == player.minvData->focus + 1 || move->owner == 0)){
			bool found = false;
			for(unsigned int j = 0; !found && j < player.minvData->movesCurr.size(); ++j)
				found = move == player.minvData->movesCurr[j];
			if(!found)
				player.minvData->movesAvail.push_back(move);
		}
	}
}


void GetAvailableList(Player &player){
	player.minvData->movesAvailList.text.resize(0);
	for(auto &it: player.minvData->movesAvail)
		player.minvData->movesAvailList.text.push_back(it->name);
}


void AddToCurrentMoves(Player &player, int &prevActive){
	struct Move *move = player.minvData->movesAvail[prevActive];
	Actor *actor = player.team.members[player.minvData->focus];

	//Add the move to the actor's move list
	bool addedMove = false;
	for(int i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(!actor->moves[i]){
			actor->moves[i] = move;
			addedMove = true;
			break;
		}
	}

	//the 'move' array is not filled to capacity if added 
	if(addedMove){
		GetCurrent(player);
		GetAvailable(player);

		SetupListView(player.minvData->movesCurrList);
		SetupListView(player.minvData->movesAvailList);
	}
}


void RemoveFromCurrentMoves(Player &player, int &prevActive){
	struct Move *move = player.minvData->movesCurr[prevActive];
	Actor *actor = player.team.members[player.minvData->focus];

	bool removedMove = false;
	for(int i = 0; i < NUM_ACTOR_MOVES; ++i){
		if(move == actor->moves[i]){
			removedMove = true;
			actor->moves[i] = nullptr;
			//Sift down moves in the array
			for(int j = i; j < NUM_ACTOR_MOVES - 1; ++j)
				actor->moves[j] = actor->moves[j+1];
			actor->moves[NUM_ACTOR_MOVES-1] = nullptr;
		}
	}
	if(removedMove){
		GetCurrent(player);
		GetAvailable(player);

		SetupListView(player.minvData->movesCurrList);
		SetupListView(player.minvData->movesAvailList);
	}
}


void SetupMoveInfo(MoveInventoryData &minvD){
	struct Move *move = nullptr;
	if(minvD.info == 0){
		if(minvD.movesCurrList.active > -1){
			move = minvD.movesCurr[minvD.movesCurrList.active];
			std::string *text = &minvD.moveInfo.text;
			*text = "";
			*text += "Element: " + to_string(move->elem) + "\t\t";
			*text += "Damage: " + std::to_string(move->damage) + "\t\t";
			*text += "Healing: " + std::to_string(move->healing) + "\t\t";
			*text += "Cost: " + std::to_string(move->cost) + "\n";
			if(move->isPhysical)
				*text += "Physical\t\t\t";
			else
				*text += "Meta\t\t\t";
			
			*text += "Obtained at level " + std::to_string(move->levelObtained);
			//TODO: Description
		}
	}
	else{
		if(minvD.movesAvailList.active > -1){
			move = minvD.movesAvail[minvD.movesAvailList.active];
			std::string *text = &minvD.moveInfo.text;
			*text = "";
			*text += "Element: " + to_string(move->elem) + "\t\t";
			*text += "Damage: " + std::to_string(move->damage) + "\t\t";
			*text += "Healing: " + std::to_string(move->healing) + "\t\t";
			*text += "Cost: " + std::to_string(move->cost) + "\n";
			if(move->isPhysical)
				*text += "Physical\t\t\t";
			else
				*text += "Meta\t\t\t";
			
			*text += "Obtained at level " + std::to_string(move->levelObtained);
			//TODO: Description
		}
	}
	Vector2 textSize = MeasureTextEx(GuiGetFont(), minvD.moveInfo.text.c_str(), GuiGetStyle(DEFAULT, TEXT_SIZE), GuiGetStyle(DEFAULT, TEXT_SPACING));
	minvD.moveInfo.bounds = (Rectangle){256, 288 - textSize.y / 2, textSize.x, textSize.y};
	minvD.moveInfo.bgBounds = (Rectangle){minvD.moveInfo.bounds.x - 8, minvD.moveInfo.bounds.y - 16 + textSize.y/2, textSize.x + 16, textSize.y + 16};
}

