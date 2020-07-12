#pragma once
#ifndef GAME_H
#define GAME_H

#include "elemino.h"
#include "console.h"
#include "player.h"
#include "gamestate.h"
#include "moveinventory.h"
#include "combat.h"
#include "sprite.h"

#include "raylib\raylib.h"

const int GRID_PADDING = 96;

struct Game{
	unsigned int frameCounter = 0;

	Console console;
	Player player;
	GameState gs;
	Mouse mouse;
	CombatData *cbtData = nullptr;
	static TextureManager textures;

	bool justEnteredState;
	bool consoleOpen;
	bool inventoryOpen;
	bool minventoryOpen;

	Grid gridMat[4][3]; //array of 4 characters' elematrices

	Game();
	~Game();
};

int InventoryState(Game &);
int MoveInventoryState(Game &);
void InventoryStatesToggle(Game &);
int CombatState(Game &);
void DrawCombat(const Game &);

#endif
