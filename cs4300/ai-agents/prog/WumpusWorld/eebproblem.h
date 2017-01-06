#ifndef _EEBPROBLEM_H_
#define _EEBPROBLEM_H_
#include <ai_search.h>
#include "eebstate.h"
#include "eebmodel.h"

namespace eebt
{ 
	class Problem : public ai::Search::Problem
	{
	public:
	 	Problem(ai::Search::State *initstate, Model *model);
	 	virtual ~Problem();
	 	virtual bool GoalTest(const ai::Search::State * const state)const;
	 	virtual bool FindSuccessors(const ai::Search::State * const state, 
	 								std::vector<ai::Search::ActionStatePair> 	
	 								&resultsout)const;
	 	virtual int StepCost(const ai::Search::State * const state1,
	 							const ai::Search::Action * const action, 
	 							const ai::Search::State * const state2)const;
	 	bool setgoal(State *goalstate);
	 	
	protected:
		Model *model;
		State *goalstate;
	};
};
#endif
