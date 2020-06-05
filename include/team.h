#pragma once
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
		/* for(Actor *a : members){ */
		/* 	if(a) */
		/* 		delete a; */
		/* 	a = nullptr; */
		/* } */
	}
};

void CalcLevelCap(const int&);

