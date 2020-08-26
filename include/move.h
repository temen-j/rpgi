#pragma once
#ifndef MOVE_H
#define MOVE_H

#include "element.h"

struct Actor;
struct Team;

const int NUM_MOVES = 126;
const int TARGET_ALL_ACTORS = 127; //To be used with maxTargets
const int TARGET_ALL_ENEMY= 126;
const int TARGET_SELF = -1; //To be used with maxTargets

enum Ownership : int {
	general = 0,
	character0 = 1,
	character1 = 2,
	character2 = 3,
	character3 = 4,
	boss
};

struct Move_serialized;

struct Move{
	std::string name;
	int id, levelObtained, priority, maxTargets, damage, healing, cost;
	Ownership owner;
	bool isPhysical, isFriendly, isHostile;
	Element elem;

	Move();
	Move(int id, const char *name, Element elem, int levelObtained, int priority, int maxTargets, int damage, int healing, int cost,
		bool isPhysical, bool isFriendly, bool isHostile, Ownership owner);
	Move(const Move_serialized&);

};

struct AllMoves{
	static struct Move moves[126];
};

#endif

