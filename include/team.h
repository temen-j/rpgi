#pragma once
#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include "actor.h"
#include "raylib\raylib.h"

struct Actor;

template<typename T>
using Vec = std::vector<T>;

const int BASECAP = 128; //experience cap of first level

struct Team{
	Vec<Actor*> members;

	Team(){
		members.resize(0);
	}
	~Team(){
	}
};

void CalcLevelCap(const int&);

#endif
