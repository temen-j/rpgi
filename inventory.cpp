#include "include\inventory.h"
#include "include\game.h"
#include "include\player.h"
#include "include\stattext.h"

Elemino TotalEleminoes::storage[512];
unsigned int TotalEleminoes::size = 0;


void OpenInventory(Game &game){
	InventoryData *invData = game.player.invData;
	//Open up 1st character's 3 grids
	invData->focus = 0;
	invData->grids = game.gridMat[invData->focus];

	invData->portraits.toggles[0].active = true;
	invData->portraits.toggles[0].texture = LoadTexture("../img/cassandra_dev.png");
	invData->portraits.toggles[1].texture = LoadTexture("../img/gordon_dev.png");
	invData->portraits.toggles[2].texture = LoadTexture("../img/lou_dev.png");
	invData->portraits.toggles[3].texture = LoadTexture("../img/persy_dev.png");
	invData->halo = LoadTexture("../img/portrait_halo.png");

	for(size_t i = 0; i < 4; ++i){
		ImageToggle *toggle = &invData->portraits.toggles[i];
		toggle->bounds =
			(Rectangle){PORTRAIT_PADDING, (float)(i * PORTRAIT_SEPARATION + PORTRAIT_PADDING), PORTRAIT_WIDTH, PORTRAIT_WIDTH};
	}

	if(!game.justEnteredState){ //Move inventory pieces to their spot
		StatTextSetup(*invData, *game.player.team.members[invData->focus]);
		PositionEleminoes(game.player);
	}
	game.justEnteredState = true;
}


void UnloadTexturesFrom(InventoryData &invData){
	for(size_t i = 0; i < 4; ++i){
		if(invData.portraits.toggles[i].texture.id > 0)
			UnloadTexture(invData.portraits.toggles[i].texture);
	}
	UnloadTexture(invData.halo);
}


void HandleInventoryPortraits(InventoryData &invD){
	InventoryPortraits *invP = &invD.portraits;
	//TODO: Make me work with int instead storing a bunch of bools
	bool isToggled[4]; //Keep track of previous activation
	for(size_t i = 0; i < 4; ++i)
		isToggled[i] = invP->toggles[i].active;

	for(size_t i = 0; i < 4; ++i){
		bool update = Update(invP->toggles[i]);
		if(update != isToggled[i] && !update && isToggled[i])
			invP->toggles[i].active = true;
		if(update != isToggled[i] && update){
			invD.focus = i;
			for(size_t j = 0; j < 4; ++j){
				if(j != i) //Turn the others in the toggle group off
					invP->toggles[j].active = false;
			}
			break;
		}
	}
}


void PositionEleminoes(Player &player){
	unsigned int max = player.invData->MAX_INV_DISP;
	unsigned int size = player.inventory.size();

	for(unsigned int i = 0; i < size && i < max; ++i){
		Vector2 pos = INV_POS + (Vector2){ 16 + (float)(i % 5) * INV_ELMN_OFFSET, (float)(i / 5) * INV_ELMN_OFFSET};
		MoveTo(*player.inventory[i], pos);
		player.inventory[i]->disabled = false;
	}
}


void StatTextSetup(InventoryData &invD, Actor &actor){
	Label *lab = invD.statText;
	
	lab[0].text = TEXT_MATK;
	lab[1].text = TEXT_MDEF;
	std::string health = std::to_string(actor.remHP) + " / " + std::to_string(actor.maxHP);
	lab[2].text = TEXT_HP + health;
	lab[3].text = TEXT_PDEF;
	lab[4].text = TEXT_PATK;
	std::string magic = std::to_string(actor.remMP) + " / " + std::to_string(actor.maxMP);
	lab[5].text = TEXT_MP + magic;
	
	Vector2 textSize[6];
	
	//FIXME: magic numbers!
	for(size_t i = 0; i < NUM_STATS; ++i)
		textSize[i] = MeasureTextEx(GuiGetFont(), lab[i].text.c_str(), GuiGetStyle(DEFAULT, TEXT_SIZE), GuiGetStyle(DEFAULT, TEXT_SPACING));
	
	lab[2].bounds = (Rectangle){INV_POS.x, INV_POS.y + INV_GRID_WIDTH + textSize[2].y, textSize[2].x, textSize[2].y}; 
	lab[5].bounds = (Rectangle){INV_POS.x, INV_POS.y + INV_GRID_WIDTH + textSize[5].y + 48, textSize[5].x, textSize[5].y}; 

	lab[0].bounds = (Rectangle){INV_POS.x + 128, INV_POS.y + INV_GRID_WIDTH + textSize[0].y, textSize[0].x, textSize[0].y}; 
	lab[1].bounds = (Rectangle){INV_POS.x + 128, INV_POS.y + INV_GRID_WIDTH + textSize[1].y + 48, textSize[1].x, textSize[1].y}; 
	lab[4].bounds = (Rectangle){INV_POS.x + 256, INV_POS.y + INV_GRID_WIDTH + textSize[4].y, textSize[4].x, textSize[4].y}; 
	lab[3].bounds = (Rectangle){INV_POS.x + 256, INV_POS.y + INV_GRID_WIDTH + textSize[3].y + 48, textSize[3].x, textSize[3].y}; 

	invD.tooltip.disabled = true;
	invD.tooltip.bgColor = (Color){28, 33,  35, 200}; //FIXME: magic numbers!
	invD.tooltip.textColor = (Color){219, 219, 235, 200};
}


void UpdateStatText(InventoryData &invD, Actor &actor){
	Label *lab = invD.statText;

	lab[0].text = TEXT_MATK;
	lab[1].text = TEXT_MDEF;
	std::string health = std::to_string(actor.remHP) + " / " + std::to_string(actor.maxHP);
	lab[2].text = TEXT_HP + health;
	lab[3].text = TEXT_PDEF;
	lab[4].text = TEXT_PATK;
	std::string magic = std::to_string(actor.remMP) + " / " + std::to_string(actor.maxMP);
	lab[5].text = TEXT_MP + magic;
}


void StatToolTip(InventoryData &invD, Actor &actor){
	Label *lab = invD.statText;
	Vector2 mousePos = GetMousePosition();
	for(size_t i = 0; i < 5; ++i){
		invD.tooltip.disabled = !CheckCollisionPointRec(mousePos, lab[i].bounds);
		if(!invD.tooltip.disabled){ //FIXME: Way too long! Find ways of reducing the size of this func
			std::string num;
			std::string elemNames[NUMELEMENTS] = {
				"Fire:      +",
				"Water:     +",
				"Nature:    +",
				"Lightning: +",
				"Metal:     +",
				"Rock:      +",
				"Spectre:   +"
			};
			size_t j;
			switch(i){
			case 0:
				invD.tooltip.text = "";
				for(j = 0; j < NUMELEMENTS; ++j){
					num = std::to_string(actor.mAtk[j] * COMBATBONUS_MULT * 100);
					num = num.substr(0, num.length()-4);
					invD.tooltip.text += elemNames[j] + num + "%" + ((j == 6) ? "" : "\n");
				}
				break;
			case 1:
				invD.tooltip.text = "";
				for(j = 0; j < NUMELEMENTS; ++j){
					num = std::to_string(actor.mDef[j] * COMBATBONUS_MULT * 100);
					num = num.substr(0, num.length()-4);
					invD.tooltip.text += elemNames[j] + num + "%" + ((j == 6) ? "" : "\n");
				}
				break;
			case 3:
				invD.tooltip.text = "";
				for(j = 0; j < NUMELEMENTS; ++j){
					num = std::to_string(actor.pDef[j] * COMBATBONUS_MULT * 100);
					num = num.substr(0, num.length()-4);
					invD.tooltip.text += elemNames[j] + num + "%" + ((j == 6) ? "" : "\n");
				}
				break;
			case 4:
				invD.tooltip.text = "";
				for(j = 0; j < NUMELEMENTS; ++j){
					num = std::to_string(actor.pAtk[j] * COMBATBONUS_MULT * 100);
					num = num.substr(0, num.length()-4);
					invD.tooltip.text += elemNames[j] + num + "%" + ((j == 6) ? "" : "\n");
				}
				break;
			}
			Vector2 textSize = MeasureTextEx(GuiGetFont(), invD.tooltip.text.c_str(), GuiGetStyle(DEFAULT, TEXT_SIZE), GuiGetStyle(DEFAULT, TEXT_SPACING));
			if(mousePos.y <= GetScreenHeight() / 2){
				invD.tooltip.bounds =  (Rectangle){mousePos.x + 16, mousePos.y - textSize.y / 2, textSize.x, textSize.y + 64};
				invD.tooltip.bgBounds =  (Rectangle){mousePos.x + 8, mousePos.y + 16, textSize.x + 16, textSize.y + 16};
			}
			else{
				invD.tooltip.bounds =  (Rectangle){mousePos.x + 16, mousePos.y - 32 - 3 * textSize.y / 2, textSize.x, textSize.y + 64};
				invD.tooltip.bgBounds =  (Rectangle){mousePos.x + 8, mousePos.y - 16 - textSize.y, textSize.x + 16, textSize.y + 16};
			}
			break;
		}

		if(i == 1)
			++i;
	}
}


void CheckForEleminoClicked(Game &game){
	Player *player = &game.player;
	for(unsigned int i = 0; i < player->inventory.size(); ++i){
		bool clicked = CheckLPressed(*player->inventory[i], game.mouse);
		if(clicked){
			player->invData->inFlight = nullptr;
			player->inventory.erase(player->inventory.begin() + i);
			PositionEleminoes(*player);
			break;
		}
	}
	for(size_t i = 0; i < 3; ++i){
		for(unsigned int j = 0; j < player->invData->grids[i].attached.size(); ++j){
			bool clicked = CheckLPressed(*player->invData->grids[i].attached[j], game.mouse);
			if(clicked){
				player->invData->inFlight = nullptr;
				player->invData->grids[i].attached.erase(player->invData->grids[i].attached.begin() + j); //FIXME: Verbose
				break;
			}
		}
	}
}


void MouseTouchElemino(Game &game){
	Player *player = &game.player;

	if(game.mouse.touch && game.mouse.interface == InterfaceID::ELEMINO){
		Elemino *elemino = static_cast<Elemino *>(game.mouse.touch);
		Drag(*elemino);

		if(IsKeyPressed(KEY_R))
			Rotate(*elemino);

		CheckLReleased(*elemino, game.mouse);

		if(!game.mouse.touch)
			player->invData->inFlight = elemino; //Set the elemino to be in open space
	}
}


void HandleFlyingElemino(Game &game){
	Player *player = &game.player;

	if(player->invData->inFlight){
		Elemino *elemino = player->invData->inFlight;
		for(size_t i = 0; i < 3; ++i){
			Grid *grid = &player->invData->grids[i];
			bool prevAlignment = elemino->aligned;
			Snap(*elemino, *grid); //Snap this floating elemino
			
			bool addEleminoToGrid = true;
			//Lin. search for this pointer to see if it is alread attached to the grid
			for(unsigned int j = 0; j < player->invData->grids[i].attached.size(); ++j){ //FIXME: Verbose!
				if(elemino == player->invData->grids[i].attached[j])
					addEleminoToGrid = false;
			}

			if(elemino->aligned && !prevAlignment){
				if(addEleminoToGrid){
					player->invData->grids[i].attached.push_back(elemino);
					AssignElementGrid(player->invData->grids, *player->team.members[player->invData->focus]); //FIXME: Verbose!
					UpdateStatText(*player->invData, *player->team.members[player->invData->focus]);
				}
				break;
			}
		}
		if(!elemino->aligned && !elemino->dragging){ //TODO: turn this into a function?
				elemino->inInventory = true;
				player->inventory.push_back(elemino);
				PositionEleminoes(*player);
				MakeRectanglesSmall(*elemino);
				player->invData->inFlight = nullptr;
				AssignElementGrid(player->invData->grids, *player->team.members[player->invData->focus]); //FIXME: Verbose!
				UpdateStatText(*player->invData, *player->team.members[player->invData->focus]);
		}
	}
}


void AssignElementGrid(Grid *g, Actor &a){
	for(unsigned int i = 0; i < NUMGRIDS; ++i){
		for(unsigned int j = 0; j < NUMCELLS; ++j){
			Element elem = Element::none;
			if(g[i].anchors[j].occupier)
				elem = g[i].anchors[j].occupier->elem;

			a.grids[i][j] = elem;
		}
	}
	AssignStats(&a);
}

