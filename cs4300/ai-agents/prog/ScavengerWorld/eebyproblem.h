#ifndef _EEBYPROBLEM_H_
#define _EEBYPROBLEM_H_
#include <ai_search.h>
#include "eebymodel.h"
#include "eebystate.h"

namespace eeby
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
	 	virtual double StepCost(const ai::Search::State * const state1,
	 							const ai::Search::Action * const action, 
	 							const ai::Search::State * const state2)const;
	 	bool setgoal(State *goalstate);
	 	
	protected:
		Model *model;
		State *goalstate;
	};
};
#endif
