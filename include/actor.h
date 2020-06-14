#pragma once
#ifndef ACTOR_H
#define ACTOR_H
#include <fstream>
#include <math.h>
#include <vector>

#include "element.h"
#include "move.h"
#include "moveinventory.h"

//TODO re-enable move and effects once working/complete

template<typename T>
using Vec = std::vector<T>;

static const int NUMGRIDS = 3;
static const int NUMCELLS = 16;
static const int NUM_ACTOR_MOVES = 8;
static const int INITHP = 200;
static const int INITMP = 200;

static const int HPBONUS_FIRE = 2;
static const int HPBONUS_WATER = 4;
static const int HPBONUS_NATURE = 5;
static const int HPBONUS_LIGHTNING = 3;
static const int HPBONUS_METAL = 7;
static const int HPBONUS_ROCK = 6;
static const int HPBONUS_SPECTRE = 1;

static const int MPBONUS_FIRE = 6;
static const int MPBONUS_WATER = 4;
static const int MPBONUS_NATURE = 3;
static const int MPBONUS_LIGHTNING = 5;
static const int MPBONUS_METAL = 1;
static const int MPBONUS_ROCK = 2;
static const int MPBONUS_SPECTRE = 7;

static const float COMBATBONUS_MULT = 0.0234375f; //.375 / 16
static const float HPMPBONUS_MULT = 0.015625f; //2^-6
static const int MAXAMOUNT = 16; //0, 1, ..., 16
static const int MAXCUMAMOUNT = 112; //7  * 16, # of Elements  * # of cells

//NOTE: when recomputing hp/mp when changing eleminoes, when decreasing max _p, ceil the proportion * max
//when increasing max _p, floor the proportion * max
//this is so that the player cannot cheat and heal by just changing around eleminoes

struct Actor_serialized;

struct Actor{
	std::string name;

	Element grids[NUMGRIDS][NUMCELLS];
	int remHP, remMP, maxHP, maxMP, speed;
	int mAtk[NUMELEMENTS], mDef[NUMELEMENTS], pAtk[NUMELEMENTS], pDef[NUMELEMENTS], hpBonus, mpBonus;
	bool immune[NUMELEMENTS], pIncap, mIncap, isDisabled;
	struct Move *moves[NUM_ACTOR_MOVES];
	Element type[2];

	//Vec<effect *> currEffects;


	Actor(){
		for(int i = 0; i < NUMGRIDS; ++i)
			for(int j = 0; j < NUMCELLS; ++j)
				grids[i][j] = Element::none;

		remHP = maxHP = INITHP;
		remMP = maxMP = INITMP;
		speed = 0;

		for(int i = 0; i < NUMELEMENTS; ++i)
			mAtk[i] = mDef[i] = pAtk[i] = pDef[i] = 0;

		pIncap = mIncap = isDisabled = false;

		hpBonus = mpBonus = 0;
		type[0] = type[1] = Element::none;

		for(size_t i = 0; i < NUM_ACTOR_MOVES; ++i)
			moves[i] = nullptr;
	}

	//Actor(const Actor *);
	//Actor(const Actor_serialized&);
};

/* struct Actor_serialized{ */
/* 	Element grids[NUMGRIDS][NUMCELLS]; */
/* 	int remHP, remMP; */
/* 	int moveIds[NUM_ACTOR_MOVES] = { 0 }; */

/* 	//Copy relevant data over, stuff that can be reporduced will be and only */
/* 	//gameplay critical stuff goes into here */
/* 	Actor_serialized(Actor *); */
/* }; */

//Assigns the stats of an actor based off its grids, will also call AssignType()
void AssignStats(Actor *);

//Assigns the type based of the number of elements in the grids, also clears moves
//that do not match the type
void AssignType(Actor &);

bool IsDead(const Actor &);

void HealActor(Actor &, const unsigned int);

void FullHealActor(Actor &);

std::ostream& operator<<(std::ostream &, const Actor &);

#endif

