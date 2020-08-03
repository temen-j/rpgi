#pragma once
#ifndef COMBAT_H
#define COMBAT_H
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>

#include "raylib\rmem.h"
#include "gui.h"
#include "move.h"
#include "sprite.h"
#include "inventory.h"
#include "sprite.h"

#ifndef EASINGS_HEADER
#define EASINGS_HEADER
#define __cpluscplus
#include "..\include\raylib\easings.h"
#endif

constexpr size_t DIFF_MEM_SIZE = 1024 * sizeof(EffectDiff);

template<typename T>
using Vec = std::vector<T>;

template<typename T, typename U>
using Pair = std::pair<T, U>;

template<typename T, typename U>
using UMap = std::unordered_map<T, U>;

struct CasterMove{
	Actor *caster;
	struct Move *move;
};

struct CasterTargetsPair : CasterMove{
	Vec<Actor *> targets;

	CasterTargetsPair(){
		caster = nullptr;
		move = nullptr;
		targets.resize(0);
	}
	CasterTargetsPair(Actor *, struct Move *, const Vec<Actor *> &);
};

struct StatusEffects{
	bool incaps[2] = {false};
	bool immune[NUMELEMENTS + 2] = {false}; //the +2 is for physical/meta immunity
	bool disable = false;
};

struct CombatData{

	enum CombatStates{
		selectionPhase,
		executionPhase
	};

	static CombatPortraits portraits;
	static Texture halo;
	static UMap<Actor *, Sprite> actorSprites;
	static bool moveAnimPlaying;

	static Team *playerTeam;
	static Team *botTeam;

	static Vec<Actor *> playerAlive;
	static Vec<Actor *> botAlive;
	static Vec<Actor *> potTargets; //potential targets
	static Vec<Actor *> chosenTargets;

	static UMap<Actor *, Vec<MoveEffect> > effects;
	static MemPool diffMemPool;
	static UMap<Actor *, StatusEffects> statusEffects;

	static struct Move *affordable[NUM_ACTOR_MOVES];
	static struct Move *chosenMove;

	static bool aiMakePairs;
	static bool dispTargetLists;
	static bool begunAssigning;
	static bool canAssign;
	static bool canMakePair;
	static bool executingMoves;
	static bool interpStats;
	static bool announceMove;

	static UMap<Actor *, bool> hasMoveChosen;
	static Vec<CasterTargetsPair> ctps; //When exectuting moves, create an array of pointer and heapify that
	static Vec<CasterTargetsPair *> ctpsPtrs;
	static unsigned int execIndex;

	static ListView targetAliveList;
	static ListView targetSelectedList;
	static Button moveButtons[NUM_ACTOR_MOVES];
	static UMap<Actor *, StatBar[2]> statBars;
	static float statBarInterpTimer;
	static constexpr float statBarInterpTime = .375f;

	static BoxLabel moveAnnouncement;
	static float announcementTimer;
	static constexpr float announcementTime = 1.125f;

	static float tickEffectTimer;
	static constexpr float tickEffectTime = .375f;

	static unsigned char focus;
	static unsigned int animLockouts;
};

//The main combat loop of the game
void StartCombat(Game &game);

//A whole team selects moves
//1st - ally team, 2nd - opponents, 3rd - super convoluted BS for pairing actors and their targets
void SelectMoves(CombatData &);

//Populates a move ptr array with the moves the actor can afford to use
void GetAffordableMoves(Actor &, struct Move **); //2nd arg is the populated arr

//Based on the maxTargets of the move, select the target(s)
void AssignTargets(CombatData &);

//Based on the maxTargets of the move, select the target(s)
void AssignTargetsSetup(CombatData &);

//Once targets have been assigned make the caster-targets pair
void MakeCTP(CombatData &);

//From the pairs, the caster uses a move on all the targets
void BeginExecMoves();

//From the pairs, the caster uses a move on all the targets
void ExecMoves(CombatData &);

//Go through a hellish switch statement and execute moves
void ExecMove(CasterTargetsPair &);

//In reverse move order, tick all the effects on all the actors that have effects
void TickEffects(CasterTargetsPair &);

//Remove dead actors from the teams
void ResolveDeaths();


//AI Functions---------------------------------------------------------------------------------------
void AIMiniMax(CombatData &); //MiniMax w/ alpha-beta pruning, TODO: Find out if this can be done iteratively
//TODO: make a heuristic for minimax (find lowest hp? mp? death?)
//TODO: make a function that computes future timesteps for the heuristic

//NOTE: June 10, 2020
//These functions will work under the assumption that the AI is not trying very hard
//this is just to get the mvp out of dev
void AIMakeCTPs(CombatData &);


//Helper Functions-----------------------------------------------------------------------------------
void HandleCombatPortraits(CombatData &);
void MoveButtonsSetup(CombatData &);
void MoveButtonsTextSetup(CombatData &);
void DisableUnusedButtons(CombatData &);
void TeamsSetup(CombatData &);
void BeginAssignTargets(CombatData &);
void AddFromAliveList(CombatData &, int &); 
void RemoveFromSelectedList(CombatData &, int &); 
bool CanExecMoves(CombatData &);
void CreateGoons(CombatData &);
void UpdateFocus(CombatData &); //Update the combat data's character focus
void ResetSelectAvailList();
void FindExecutableCTP();
void CombatSpriteSetup(CombatData &);
void GoonSpriteSetup(CombatData &);

void BeginAnnounceMove(CombatData &);
void AnnounceMove(CombatData &);
void InterpolateStatBars(UMap<Actor *, float> &, UMap<Actor *, float> &); //Pass the previous ...p stats to interp from

bool LessThan(CasterTargetsPair *, CasterTargetsPair *);

#endif
