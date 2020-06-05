#pragma once
#ifndef FOO_H
#define FOO_H

#include "qwer.h"

struct foo{
	int bar;
};
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
	~Move(){
	};

};
#endif
