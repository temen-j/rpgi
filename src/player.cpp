#include "..\include\player.h"
#include "..\include\move.h"
#include "..\include\moveinventory.h"

Actor Character::actors[NUM_PLAYER_CHARACTERS];

Player::Player(){
	invData = nullptr;
	minvData = nullptr;
	inventory.resize(0);
}


Player::~Player(){
	if(invData){
		delete invData;
		invData = nullptr;
	}
	if(minvData){
		delete minvData;
		minvData = nullptr;
	}
}


void AddCharacters(Player &player){
	for(unsigned int i = 0; i < NUM_PLAYER_CHARACTERS; ++i)
		player.team.members.push_back(&Character::actors[i]);

	Character::actors[0].name = "Cassandra";
	Character::actors[1].name = "Gordon";
	Character::actors[2].name = "Lou";
	Character::actors[3].name = "Persy";
}


void SetMaxLevel(Player &player){
	player.level = 8; //FIXME: magic numbers!
}

/* void Player::AddElemino(Elemino *e){ */
/* 	inventory.push_back(e); */
/* } */

