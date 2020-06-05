#include "team.h"
#include "move.h"


team::team(const int &n){
	members.resize(n);
}


team::~team(){
	for(actor *a : members){
		if(a)
			delete a;
		a = nullptr;
	}
	members.clear();
}


void CalcLevelCap(const int &level){
	int powOfTwo = 1;
	for(int i = level; i > 0; --i){
		powOfTwo *= 2;
	}
	levelCap = BASECAP * powOfTwo;
}


