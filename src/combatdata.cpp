#include "..\include\combat.h"

Team *CombatData::playerTeam = nullptr;
Team *CombatData::botTeam = nullptr;

UMap<Actor *, Vec<MoveEffect> > CombatData::effects;
UMap<Actor *, StatusEffects> CombatData::statusEffects;
MemPool CombatData::diffMemPool = CreateMemPool(DIFF_MEM_SIZE);

CombatPortraits CombatData::portraits;
Texture CombatData::halo;

UMap<Actor *, bool> CombatData::hasMoveChosen;

UMap<Actor *, Sprite> CombatData::actorSprites;

bool CombatData::moveAnimPlaying = false;

Vec<Actor *> CombatData::playerAlive;
Vec<Actor *> CombatData::botAlive;
Vec<Actor *> CombatData::potTargets;
Vec<Actor *> CombatData::chosenTargets;

struct Move *CombatData::affordable[NUM_ACTOR_MOVES] = {nullptr};
struct Move *CombatData::chosenMove = nullptr;

Vec<CasterTargetsPair> CombatData::ctps;
Vec<CasterTargetsPair *> CombatData::ctpsPtrs;

unsigned char CombatData::focus = 0;
unsigned int CombatData::animLockouts = 0;

//TODO: make into bit flags -----------------------
bool CombatData::dispTargetLists = false;
bool CombatData::begunAssigning = false;
bool CombatData::canAssign = false;
bool CombatData::canMakePair = false;
bool CombatData::executingMoves = false;
bool CombatData::interpStats = false;
bool CombatData::announceMove = false;
bool CombatData::aiMakePairs = false;
//-------------------------------------------------

unsigned int CombatData::execIndex = 0;
float CombatData::statBarInterpTimer = 0.f;
float CombatData::announcementTimer = 0.f;

ListView CombatData::targetAliveList;
ListView CombatData::targetSelectedList;

UMap<Actor *, StatBar[2]> CombatData::statBars;

BoxLabel CombatData::moveAnnouncement;

Button CombatData::moveButtons[NUM_ACTOR_MOVES];

float CombatData::tickEffectTimer = 0.f;

