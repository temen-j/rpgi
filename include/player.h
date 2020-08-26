#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

/* #include "team.h" */
#include "elemino.h"
#include "inventory.h"
#include "actor.h"
#include "moveinventory.h"
#include "combat_ai.h"

#include "raylib\raylib.h"

template<typename T>
using Vec = std::vector<T>;

struct Team;
struct Elemino;
struct Grid;
struct Move;
struct MoveInventoryData;

const unsigned int NUM_PLAYER_CHARACTERS = 4;

struct Character{
	static Actor actors[NUM_PLAYER_CHARACTERS];
};

struct Team{
	Vec<Actor*> members;

	Team(){
		members.resize(0);
	}
	~Team(){
	}
};

struct Player{
	int exp;
	int level;

	Vec<Elemino *> inventory;
	InventoryData *invData;
	struct MoveInventoryData *minvData;

	Team team;

	Player();
	~Player();

	void AddElemino(Elemino *);
};


void AddCharacters(Player &);
void SetMaxLevel(Player &);

#endif
