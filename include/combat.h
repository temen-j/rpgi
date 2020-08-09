#pragma once
#ifndef COMBAT_H
#define COMBAT_H
#include <algorithm>
#include <vector>
#include <array>

#include "raylib\rmem.h"
#include "robin_hood\robin_hood.h"
#include "gui.h"
#include "move.h"
#include "sprite.h"
#include "inventory.h"
#include "sprite.h"

#include "..\include\raylib\easings.h"

constexpr size_t DIFF_MEM_SIZE = 1024 * sizeof(EffectDiff);

template<typename T>
using Vec = std::vector<T>;

template<typename T, typename U>
using Pair = std::pair<T, U>;

template<typename T, typename U>
using UMap = robin_hood::unordered_flat_map<T, U>;

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
	/* static UMap<Actor *, StatBar[2]> statBars; */
	static UMap<Actor *, std::array<StatBar, 2> > statBars;
	static float statBarInterpTimer;
	static constexpr float statBarInterpTime = .375f;

	static BoxLabel moveAnnouncement;
	static float announcementTimer;
	static constexpr float announcementTime = 1.125f;

	static bool tickEffects;
	static float tickEffectTimer;
	static constexpr float tickEffectTime = .375f;

	static bool endExec;

	static unsigned char focus;
	static unsigned int animLockouts;


//Setup the combat of the game
/* static void StartCombat(Game &game); */
static void StartCombat(Team *, Team *);

//A whole team selects moves
//1st - ally team, 2nd - opponents, 3rd - super convoluted BS for pairing actors and their targets
static void SelectMoves();

//Populates a move ptr array with the moves the actor can afford to use
static void GetAffordableMoves(Actor &, struct Move **); //2nd arg is the populated arr

//Based on the maxTargets of the move, select the target(s)
static void AssignTargets();

//Based on the maxTargets of the move, select the target(s)
static void AssignTargetsSetup();

//Once targets have been assigned make the caster-targets pair
static void MakeCTP();

//From the pairs, the caster uses a move on all the targets
static void BeginExecMoves();

//From the pairs, the caster uses a move on all the targets
static void ExecMoves();

//Go through a hellish switch statement and execute moves
static void ExecMove(CasterTargetsPair &);

//In reverse move order, tick all the effects on all the actors that have effects
static void TickEffects();

//Remove dead actors from the teams
static void ResolveDeaths();


//AI Functions---------------------------------------------------------------------------------------
static void AIMiniMax(); //MiniMax w/ alpha-beta pruning, TODO: Find out if this can be done iteratively
//TODO: make a heuristic for minimax (find lowest hp? mp? death?)
//TODO: make a function that computes future timesteps for the heuristic

//NOTE: June 10, 2020
//These functions will work under the assumption that the AI is not trying very hard
//this is just to get the mvp out of dev
static void AIMakeCTPs();


//Helper Functions-----------------------------------------------------------------------------------
static void HandleCombatPortraits();
static void MoveButtonsSetup();
static void MoveButtonsTextSetup();
static void DisableUnusedButtons();
static void TeamsSetup();
static void BeginAssignTargets();
static void AddFromAliveList(int &); 
static void RemoveFromSelectedList(int &); 
static bool CanExecMoves();
static void CreateGoons();
static void UpdateFocus(); //Update the combat data's character focus
static void ResetSelectAvailList();
static void FindExecutableCTP();
static void CombatSpriteSetup();
static void GoonSpriteSetup();
static void BeginAnnounceMove();
static void SetupStatBar(UMap<Actor *, float> &, UMap<Actor *, float> &);
static void EndExecution();
static void RecoverMP();

static void AnnounceMove();
static void InterpolateStatBars(UMap<Actor *, float> &, UMap<Actor *, float> &); //Pass the previous ...p stats to interp from
static void CalcStatBarsMP();

static bool LessThan(CasterTargetsPair *, CasterTargetsPair *);
};

#endif
