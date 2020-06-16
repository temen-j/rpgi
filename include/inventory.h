#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <vector>

#include "element.h"
#include "elemino.h"
#include "actor.h"
#include "raylib\raylib.h"

const int PORTRAIT_PADDING = 8;
const int PORTRAIT_SEPARATION = 80;
const int PORTRAIT_WIDTH = 64;
const int NUM_STATS = 6;

const Vector2 INV_POS = (Vector2){320, 64};
const int INV_GRID_WIDTH = 400;
const int INV_ELMN_OFFSET = 80;

const int MAX_TOTAL_ELMN = 512;

struct Player;
struct Actor;

template<typename T>
using Vec = std::vector<T>;

struct InventoryData{
	Grid *grids;
	Elemino *inFlight = nullptr; //The elemino not being dragged in open space

	InventoryPortraits portraits;
	Texture halo;
	Label statText[6];
	BoxLabel tooltip;
	DropDown elemdd;

	Vec<Elemino *> eleminoesAvail; //The eleminoes available to the pages
	Vec<Elemino *> interactable; //The eleminoes on the page

	const unsigned int MAX_INV_DISP = 25;
	unsigned char page = 0;
	unsigned char focus;
	unsigned char lastFocus;
};

struct TotalEleminoes{
	static Elemino storage[MAX_TOTAL_ELMN];
	static unsigned int size;
};

void OpenInventory(Game &);
void HandleInventoryPortraits(InventoryData &);
void PositionEleminoes(Player &); //For the inventory
void PositionEleminoes(InventoryData &);
void StatTextSetup(InventoryData &, Actor &);
void UpdateStatText(InventoryData &, Actor &);
void StatToolTip(InventoryData &, Actor &);

void CheckForEleminoClicked(Game &); //Check if an elemino has been clicked on to start dragging
void MouseTouchElemino(Game &); //Drag, Rotate, and Check for release while mouse if touching elemino
void HandleFlyingElemino(Game &); //Either snap it to a grid or back into the inventory
void UpdateInteractable(Player &); //Remake the interactable vector

void UnloadTexturesFrom(InventoryData &);

void AssignElementGrid(Grid *, Actor &); //Loop over grid and add the element to the actor's grid
#endif

