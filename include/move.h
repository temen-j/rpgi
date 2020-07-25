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


/* struct Move_serialized{ */
/* 	char name[24]; */
/* 	char id, priority, maxTargets, damage, healing, cost; */
/* 	//3 bits levelObtained, 3 bits for the isPhysical, IsFriendly, isHostile */
/* 	//2 bits owner */
/* 	char packed0; */ 
/* 	//2 bits for damage, healing, and cost extras */
/* 	char packed1; */
/* 	char elem; */
/* }; */


/* void loadAllMoves(std::vector<Move *>&); */
/* int bitExtracted(const int&, const int&, const int&); */


/* namespace Movefunctions{ */
/* 	//Tries to make the cost for the Move with a caster */
/* 	//Returns true if the caster can afford the Move, otherwise, returns false */
/* 	bool canAfford(const Move *, actor*); */
/* 	bool canAffordFLAMESWORD(const Move *, actor*, actor *target); */

/* 	//1st - Move ptr, 2nd - ally team, 3rd - opponent team */
/* 	std::vector<actor*> selectTargets(const Move *, const team&, const team&); */

/* 	//1st - dyn. arr. of damage, 2nd dyn. array of targets */
/* 	void resolveDamageHP(std::vector<int>&, std::vector<actor*>&); */

/* 	//Damage and heal calculators */
/* 	//1st param: Move ptr to self, 2nd: caster, 3rd: targets/target */

/* 	std::vector<int> pDamage(Move *, actor*, std::vector<actor*> &); */
/* 	std::vector<int> mDamage(Move *, actor*, std::vector<actor*> &); */
/* 	std::vector<int> pHeal(Move *, actor*, std::vector<actor*> &); */
/* 	std::vector<int> mHeal(Move *, actor*, std::vector<actor*> &); */

/* 	//Fire Moves */
/* 	void ignite(Move *, actor*, std::vector<actor*> &); */
/* 	void blaze(Move *, actor*, std::vector<actor*> &); */
/* 	void fireball(Move *, actor*, std::vector<actor*> &); */
/* 	void explosion(Move *, actor*, std::vector<actor*> &); */
/* 	void firebeam(Move *, actor*, std::vector<actor*> &); */
/* 	void flamesword(Move *, actor*, std::vector<actor*> &); */
/* 	void flarekick(Move *, actor*, std::vector<actor*> &); */
/* 	void firewall(Move *, actor*, std::vector<actor*> &); */
/* 	void searingflesh(Move *, actor*, std::vector<actor*> &); */
/* 	void moltenmeteor(Move *, actor*, std::vector<actor*> &); */
/* 	void wildfire(Move *, actor*, std::vector<actor*> &); */
/* 	void razeearth(Move *, actor*, std::vector<actor*> &); */
/* 	void fromtheashes(Move *, actor*, std::vector<actor*> &); */
/* 	void supernova(Move *, actor*, std::vector<actor*> &); */
/* 	void flashfriction(Move *, actor*, std::vector<actor*> &); */
/* 	void scorchingheat(Move *, actor*, std::vector<actor*> &); */
/* 	void dragonbreath(Move *, actor*, std::vector<actor*> &); */
/* 	void icarusinferno(Move *, actor*, std::vector<actor*> &); */

/* 	//Water Moves */
/* 	void waterwhip(Move *, actor*, std::vector<actor*> &); */
/* 	void torrent(Move *, actor*, std::vector<actor*> &); */
/* 	void tidalwave(Move *, actor*, std::vector<actor*> &); */
/* 	void coalesce(Move *, actor*, std::vector<actor*> &); */
/* 	void whirlpool(Move *, actor*, std::vector<actor*> &); */
/* 	void hailstorm(Move *, actor*, std::vector<actor*> &); */
/* 	void aquaprison(Move *, actor*, std::vector<actor*> &); */
/* 	void rainstorm(Move *, actor*, std::vector<actor*> &); */
/* 	void dewpoint(Move *, actor*, std::vector<actor*> &); */
/* 	void flashfreeze(Move *, actor*, std::vector<actor*> &); */
/* 	void riptide(Move *, actor*, std::vector<actor*> &); */
/* 	void vaporvortex(Move *, actor*, std::vector<actor*> &); */
/* 	void hellbroth(Move *, actor*, std::vector<actor*> &); */
/* 	void tsunami(Move *, actor*, std::vector<actor*> &); */
/* 	void rend(Move *, actor*, std::vector<actor*> &); */
/* 	void sirenstear(Move *, actor*, std::vector<actor*> &); */
/* 	void chillingblast(Move *, actor*, std::vector<actor*> &); */
/* 	void deluge(Move *, actor*, std::vector<actor*> &); */

/* 	//Nature Moves */
/* 	void seedshot(Move *, actor*, std::vector<actor*> &); */
/* 	void acornassault(Move *, actor*, std::vector<actor*> &); */
/* 	void sappingstems(Move *, actor*, std::vector<actor*> &); */
/* 	void nourish(Move *, actor*, std::vector<actor*> &); */
/* 	void leaflance(Move *, actor*, std::vector<actor*> &); */
/* 	void fungalspores(Move *, actor*, std::vector<actor*> &); */
/* 	void barbedhusk(Move *, actor*, std::vector<actor*> &); */
/* 	void grassblades(Move *, actor*, std::vector<actor*> &); */
/* 	void petalpike(Move *, actor*, std::vector<actor*> &); */
/* 	void undergrowth(Move *, actor*, std::vector<actor*> &); */
/* 	void symbiosis(Move *, actor*, std::vector<actor*> &); */
/* 	void ensnaringvine(Move *, actor*, std::vector<actor*> &); */
/* 	void rancidroses(Move *, actor*, std::vector<actor*> &); */
/* 	void dryadscurse(Move *, actor*, std::vector<actor*> &); */
/* 	void needle(Move *, actor*, std::vector<actor*> &); */
/* 	void bloom(Move *, actor*, std::vector<actor*> &); */
/* 	void treecleaver(Move *, actor*, std::vector<actor*> &); */
/* 	void venomcoating(Move *, actor*, std::vector<actor*> &); */

/* 	//Lightning Moves */
/* 	void zap(Move *, actor*, std::vector<actor*> &); */
/* 	void charge(Move *, actor*, std::vector<actor*> &); */
/* 	void discharge(Move *, actor*, std::vector<actor*> &); */
/* 	void lightningbolt(Move *, actor*, std::vector<actor*> &); */
/* 	void dazzlinglights(Move *, actor*, std::vector<actor*> &); */
/* 	void electrostorm(Move *, actor*, std::vector<actor*> &); */
/* 	void lightningkick(Move *, actor*, std::vector<actor*> &); */
/* 	void sparkingskin(Move *, actor*, std::vector<actor*> &); */
/* 	void superconduct(Move *, actor*, std::vector<actor*> &); */
/* 	void staticshock(Move *, actor*, std::vector<actor*> &); */
/* 	void evanescentfield(Move *, actor*, std::vector<actor*> &); */
/* 	void highvoltage(Move *, actor*, std::vector<actor*> &); */
/* 	void mjolnir(Move *, actor*, std::vector<actor*> &); */
/* 	void closedcircuit(Move *, actor*, std::vector<actor*> &); */
/* 	void surge(Move *, actor*, std::vector<actor*> &); */
/* 	void overload(Move *, actor*, std::vector<actor*> &); */
/* 	void ionstrike(Move *, actor*, std::vector<actor*> &); */
/* 	void plasmapulse(Move *, actor*, std::vector<actor*> &); */

/* 	//Metal Moves */
/* 	void ironspikes(Move *, actor*, std::vector<actor*> &); */
/* 	void cannonball(Move *, actor*, std::vector<actor*> &); */
/* 	void sharpen(Move *, actor*, std::vector<actor*> &); */
/* 	void shattershrapnel(Move *, actor*, std::vector<actor*> &); */
/* 	void ballandchain(Move *, actor*, std::vector<actor*> &); */
/* 	void quicksilver(Move *, actor*, std::vector<actor*> &); */
/* 	void coppercutlass(Move *, actor*, std::vector<actor*> &); */
/* 	void brassknuckles(Move *, actor*, std::vector<actor*> &); */
/* 	void midastouch(Move *, actor*, std::vector<actor*> &); */
/* 	void chromeplated(Move *, actor*, std::vector<actor*> &); */
/* 	void magnetize(Move *, actor*, std::vector<actor*> &); */
/* 	void steelfist(Move *, actor*, std::vector<actor*> &); */
/* 	void alloyassault(Move *, actor*, std::vector<actor*> &); */
/* 	void piercingplatinum(Move *, actor*, std::vector<actor*> &); */
/* 	void scrapslug(Move *, actor*, std::vector<actor*> &); */
/* 	void anneal(Move *, actor*, std::vector<actor*> &); */
/* 	void anodize(Move *, actor*, std::vector<actor*> &); */
/* 	void galvanizedglaive(Move *, actor*, std::vector<actor*> &); */

/* 	//Rock Moves */
/* 	void hurlrock(Move *, actor*, std::vector<actor*> &); */
/* 	void stonespear(Move *, actor*, std::vector<actor*> &); */
/* 	void fortify(Move *, actor*, std::vector<actor*> &); */
/* 	void quicksand(Move *, actor*, std::vector<actor*> &); */
/* 	void entomb(Move *, actor*, std::vector<actor*> &); */
/* 	void crush(Move *, actor*, std::vector<actor*> &); */
/* 	void tremor(Move *, actor*, std::vector<actor*> &); */
/* 	void rockslide(Move *, actor*, std::vector<actor*> &); */
/* 	void rollingboulder(Move *, actor*, std::vector<actor*> &); */
/* 	void sapphirestrike(Move *, actor*, std::vector<actor*> &); */
/* 	void rubyrush(Move *, actor*, std::vector<actor*> &); */
/* 	void garnetgaze(Move *, actor*, std::vector<actor*> &); */
/* 	void emeraldedge(Move *, actor*, std::vector<actor*> &); */
/* 	void obsidianonslaught(Move *, actor*, std::vector<actor*> &); */
/* 	void gravelspin(Move *, actor*, std::vector<actor*> &); */
/* 	void sandbomb(Move *, actor*, std::vector<actor*> &); */
/* 	void crystalcage(Move *, actor*, std::vector<actor*> &); */
/* 	void fissure(Move *, actor*, std::vector<actor*> &); */

/* 	//Spectre Moves */
/* 	void ectoray(Move *, actor*, std::vector<actor*> &); */
/* 	void torment(Move *, actor*, std::vector<actor*> &); */
/* 	void chaosclaw(Move *, actor*, std::vector<actor*> &); */
/* 	void phantomwaltz(Move *, actor*, std::vector<actor*> &); */
/* 	void gravetender(Move *, actor*, std::vector<actor*> &); */
/* 	void mindinvasion(Move *, actor*, std::vector<actor*> &); */
/* 	void bindingpain(Move *, actor*, std::vector<actor*> &); */
/* 	void plague(Move *, actor*, std::vector<actor*> &); */
/* 	void wickedhex(Move *, actor*, std::vector<actor*> &); */
/* 	void petrifyingpalm(Move *, actor*, std::vector<actor*> &); */
/* 	void decay(Move *, actor*, std::vector<actor*> &); */
/* 	void vividnightmare(Move *, actor*, std::vector<actor*> &); */
/* 	void etherealfog(Move *, actor*, std::vector<actor*> &); */
/* 	void noxiousvoid(Move *, actor*, std::vector<actor*> &); */
/* 	void shadowslash(Move *, actor*, std::vector<actor*> &); */
/* 	void pilfer(Move *, actor*, std::vector<actor*> &); */
/* 	void bloodcurdle(Move *, actor*, std::vector<actor*> &); */
/* 	void blackhole(Move *, actor*, std::vector<actor*> &); */

/* } */

#endif

