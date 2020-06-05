#pragma once
#ifndef MOVEINVENTORY_H
#define MOVEINVENTORY_H
#include <vector>

#include "move.h"
#include "player.h"
#include "gui.h"

struct Game;
struct InventoryPortraits;
struct ListView;

template<typename T>
using Vec = std::vector<T>;

struct MoveInventoryData{
	InventoryPortraits portraits;

	//ListView of the move that are available to the character
	ListView movesAvailList;
	//Internal list rep. the moves the focused character can have
	Vec<struct Move *> movesAvail;

	//ListView of the current moves the focused character has
	ListView movesCurrList;
	//Internal list rep. the current moves the focused character has
	Vec<struct Move *> movesCurr;

	unsigned char focus = 0;
};

void OpenMoveInventory(Game &);
void HandleInventoryPortraits(MoveInventoryData &);
void GetCurrent(Player &);
void GetCurrentMoves(Player &);
void GetCurrentList(Player &);
void GetAvailable(Player &);
void GetAvailableMoves(Player &);
void GetAvailableList(Player &);
void AddToCurrentMoves(Player &, int &); //2nd arg is the index of move being added of the available
void RemoveFromCurrentMoves(Player &, int &); //2nd arg is the index of move being removed of the current

void UnloadTexturesFrom(MoveInventoryData &);
#endif

