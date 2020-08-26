#include "include\combat_ai.h"

/* void CombatAIState::do_move(move_option ){ */
/* 	return; */
/* } */

/* void CombatAIState::do_random_move(std::mt19937_64 *rng){ */
/* 	//Reset the chosen moves */
/* 	/1* static struct Move *chosen_moves[16] = {nullptr}; *1/ */
/* 	/1* for(size_t i = 0; i < 16 && chosen_moves[i]; i++) *1/ */
/* 	/1* 	chosen_moves[i] = nullptr; *1/ */
/* 	Vec<CasterTargetsPair> ctps; */
/* 	//NUM_MOVES * num_bots * num_player_actors * move->maxTargets(applicable) = */
/* 	//8 * 4 * 4 * 4 = 512 */

/* 	bool gen_player_moves = false; */
/* 	for(size_t i = 0; i < actors_copy.size(); i++){ */
/* 		gen_player_moves = i > num_bots; */
/* 		struct Move *avail[NUM_MOVES]; */
/* 		GetAffordableMoves(actors[i], avail); */

/* 		int count = 0; */
/* 		for(auto *j = &count; *j < NUM_MOVES && avail[count]; (*j)++) */
/* 		std::uniform_int_distribution<move_option> moves(0, count); */
		
/* 		struct Move *chosen_move = avail[moves(*rng)]; */
		
/* 		Vec<Actor *> targets; */
/* 		if(chosen_move->maxTargets == TARGET_ALL_ACTORS){ */
/* 			targets.reserve(actor.size()); */
/* 			for(auto &it : actor_copy) */
/* 				targets.push_back(&it); */
/* 		} */
/* 		else if(chosen_move->maxTargets == TARGET_SELF){ */
/* 			targets.push_back(&actors_copy[i]); */
/* 		} */
/* 		else if(chosen_move->isFriendly){ */
/* 			targets.reserve(chosen_move->maxTargets); */
/* 			for(size_t j = 0; j < chosen_move->maxTargets; j++){ */
/* 				int upper_bound = gen_player_moves ? actors_copy.size() - num_bots : num_bots; */
/* 				std::uniform_int_distribution<int> target_rng(0, upper_bound); */
/* 				targets.push_back(actor[target_rng(*rng)]); */
/* 			} */
/* 		} */
/* 		else if(chosen_move->isHostile){ */
/* 			targets.reserve(chosen_move->maxTargets); */
/* 			for(size_t j = 0; j < chosen_move->maxTargets; j++){ */
/* 				int upper_bound = gen_player_moves ? actors_copy.size() - num_bots : num_bots; */
/* 				std::uniform_int_distribution<int> target_rng(0, upper_bound); */
/* 				targets.push_back(actor[target_rng(*rng)]); */
/* 			} */
/* 		} */
/* 		ctps.emplace_back(&actors_copy[i], chosen_move, targets); */
/* 	} */
/* } */



