#ifndef COMBAT_AI_H
#define COMBAT_AI_H
/* #include "mcts.h" */
#include "actor.h"
#include "move.h"


/* struct CombatComputeOptions{ */
/* 	//NOTE: it's kind of redundant, to have 2 enum classes to indicate levels of things */

/* 	enum class IterationAmount : int{ */
/* 		LOW = 0, */
/* 		MEDIUM, */
/* 		HIGH, */
/* 		WTF */
/* 	}; */
/* 	static constexpr int[4] iteration_amt = { */
/* 		2000, //LOW */
/* 		4000, //MEDIUM */
/* 		8000, //HIGH */
/* 		16000 //WTF */
/* 	}; */

/* 	enum class ThreadAmount : int{ */
/* 		LOW = 0, */
/* 		MED, */
/* 		HIGH, */
/* 		WTF */
/* 	}; */
/* 	static constexpr int[4] thread_amt = { */
/* 		1, //LOW */
/* 		2, //MEDIUM */
/* 		4, //HIGH */
/* 		8 //WTF */
/* 	}; */
	
/* 	static bool verbosity; */
/* 	static constexpr double timeout = -1.0; */
/* }; */

/* struct CombatAIState{ */
/* 	typedef int move_option; */
/* 	static const move_option = -1; */
	
/* 	void do_move(move_option); */
/* 	void do_random_move(std::mt19937_64 *); */
/* 	bool has_moves(); */
/* 	const std::vector<move_option> get_moves(); */


/* 	double get_result(); */
/* 	int playerToMove; */

/* 	unsigned int num_bots = 0; */
/* 	Vec<Actor> actors; */
/* 	Vec<Actor> actors_copy; */
/* }; */

namespace CombatAIBehavior{
	enum class Behavior : int{
		aggresive,
		exhaustive,
		helpful,
		ambiguous,
		conservative
	};
	typedef UMap<Actor *, std::array<Behavior, 2> > BehaviorMap;
};

#endif

