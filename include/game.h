#pragma once
#ifndef GAME_H
#define GAME_H

/* #include "move.h" */
#include "elemino.h"
#include "console.h"
#include "player.h"
#include "gamestate.h"
#include "moveinventory.h"

#include "raylib\raylib.h"

const int GRID_PADDING = 96;

struct Game{
	Console console;
	Player player;
	GameState gs;
	Mouse mouse;

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

#endif
