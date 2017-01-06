#include "eebproblem.h"
#include "eebaction.h"
#include <ai_search.h>
#include <cmath>

namespace eebt
{
	Problem::Problem(ai::Search::State *initstate, Model *model)
		: ai::Search::Problem(initstate), model(model), goalstate(0)
	{/* empty */}
	Problem::~Problem()
	{/* Do not delete the model.  It is only on loan. */
		if(this->goalstate)
	    {
			delete this->goalstate;
			this->goalstate=0;
	    }
	}
	bool Problem::GoalTest(const ai::Search::State * const statein)const
	{
		const State * const state=dynamic_cast<const State * const>(statein);
		return *(this->goalstate)==*state;
	}
	bool Problem::FindSuccessors(const ai::Search::State * const statein,
								std::vector<ai::Search::ActionStatePair>
								&resultsout)const
	{
		const State * const state=dynamic_cast<const State * const>(statein);
		int i;
		int newx, newy;
		Cell newcell;
		Cell currcell=this->model->getcell(state->getx(),state->gety());
		bool ok;
		for(i=1+(int)D_MIN;i<(int)D_MAX;i++)
		{
			newx=state->getx()+1;
			newy=state->gety()+1;
			newcell=this->model->getcell(newx,newy);
			Cell emptycell=Cell();
			if(newcell==emptycell) {continue;}
			else
			{
				State *newstate=new State(*state);
				Action *newaction=new Action();
				newstate->setx(newcell.getx());
				newstate->sety(newcell.gety());
				newaction->settype(((int)Action::A_NORTH)+i);
				ai::Search::ActionStatePair asp(newstate, newaction);
				resultsout.push_back(asp);
			}
		}
		return (resultsout.size() > 0);
	}
	bool Problem::setgoal(State *goalstatein)
	{
		this->goalstate=goalstatein;
		return true;
	}
};
