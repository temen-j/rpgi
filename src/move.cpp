#include "..\include\move.h"
#include "..\include\actor.h"


Move::Move(){
		id = 0;
		levelObtained = 0;
		priority = -1;
		maxTargets = -1;
		damage = -1;
		healing = -1;
		cost = -1;
		elem = Element::none;
		isPhysical = false;
		isFriendly = false;
		isHostile = false;
		owner = Ownership::general;
}


Move::Move(int id, const char *name, Element elem, int levelObtained, int priority, int maxTargets, int damage, int healing, int cost,
		bool isPhysical, bool isFriendly, bool isHostile, Ownership owner){
		this->id = id;
		this->name = name;
		this->levelObtained = levelObtained;
		this->priority = priority;
		this->maxTargets = maxTargets;
		this->damage = damage;
		this->healing = healing;
		this->cost = cost;
		this->elem = elem;
		this->isPhysical = isPhysical;
		this->isFriendly = isFriendly;
		this->isHostile = isHostile;
		this->owner = owner;
}


/* move::move(const move_serialized &ms){ */
/* 	name = ms.name; */
/* 	id = ms.id; */
/* 	std::cout << "levelObtained: " << bitExtracted(ms.packed0, 3, 0) << std::endl; */
/* 	levelObtained = bitExtracted(ms.packed0, 3, 0); */
/* 	priority = ms.priority; */
/* 	maxTargets = ms.maxTargets; */
/* 	//damage = bitExtracted(ms.packed1, 2, 0) >> 8 + ms.damage; */
/* 	std::cout << damage << std::endl; */
/* 	healing = bitExtracted(ms.packed1, 2, 2) >> 8 + ms.healing; */
/* 	cost = bitExtracted(ms.packed1, 2, 4) >> 8 + ms.cost; */
/* 	owner = (ownership)bitExtracted(ms.packed0, 1, 6); */
/* 	isPhysical = (bool)bitExtracted(ms.packed0, 1, 3); */
/* 	isFriendly = (bool)bitExtracted(ms.packed0, 1, 4); */
/* 	isHostile = (bool)bitExtracted(ms.packed0, 1, 5); */
/* 	elem = (element)ms.elem; */
/* 	use = nullptr; */
/* } */


