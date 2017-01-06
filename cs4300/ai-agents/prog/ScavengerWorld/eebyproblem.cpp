#include "eebyproblem.h"
#include "eebyaction.h"
#include <ai_search.h>
#include <cmath>

namespace eeby
{
	Problem::Problem(ai::Search::State *initstate, Model *model)
		: ai::Search::Problem(initstate), 
		model(model),
		goalstate(0)
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
		/* consider each of 4 directions
		* this is in order NORTH, SOUTH, EAST, WEST
		* which matches the order in the Action class enum,
		* also matches order of directions in Model enum.
		* this is important for the SetType() method call below.
		*/
		int dx[4]={0,0,1,-1};
		int dy[4]={1,-1,0,0};
		int i;
		double newx, newy, newcharge;
		Cell newcell;
		Cell currcell=this->model->getcell(state->getx(),state->gety());
		/*std::cout<<"state->getx(): "<<state->getx()<<std::endl;
		std::cout<<"state->gety(): "<<state->gety()<<std::endl;
		std::cout<<"currcell.GetTerrain(0): "<<currcell.GetTerrain(0)<<std::endl;
		std::cout<<"currcell.GetTerrain(1): "<<currcell.GetTerrain(1)<<std::endl;
		std::cout<<"currcell.GetTerrain(2): "<<currcell.GetTerrain(2)<<std::endl;
		std::cout<<"currcell.GetTerrain(3): "<<currcell.GetTerrain(3)<<std::endl;*/
		int terrain;
		bool ok;
		double chargecost;
		//std::cout<<"populating"<<std::endl;
		for(i=1+(int)D_MIN;i<(int)D_MAX;i++)
		{
			//std::cout << "Pop itter: " << i << std::endl;
			terrain=currcell.GetTerrain(i);
			//std::cout << "terrain: " << terrain << std::endl;
			switch(terrain)
			{
				/* passable interfaces */
				case I_MUD:
					chargecost=2.0;
					ok=true;
					break;
				case I_PLAIN:
					chargecost=1.0;
					ok=true;
					break;
				case I_ICE:
					chargecost=10.0;
					ok=true;
					break;
				
				/* impassable interfaces */
				case I_CLIFF:
				case I_ROCKS:
				case I_WALL:
				default:
					ok=false;
					break;
			}
			if(!ok) {
				//std::cout << "Celltype invalid." << std::endl;
				continue;
			}
			newx=state->getx()+1000.*dx[i];
			newy=state->gety()+1000.*dy[i];
			newcharge=state->getcharge()-chargecost;
			newcell=this->model->getcell(newx,newy);
			
			Cell emptycell=Cell();
		
			//std::cout << "Pushing cell: " << std::endl;
			if(newcell==emptycell) {continue;}
			else
			{
				State *newstate=new State(*state);
				Action *newaction=new Action();
				newstate->setx(newcell.getx());
				//std::cout<<"newstate->setx(newcell.getx()): "<<newstate->setx(newcell.getx())<<std::endl;
				newstate->sety(newcell.gety());
				newstate->setz(newcell.getz());
				newstate->setcharge(newcharge);
				newaction->settype(((int)Action::A_NORTH)+i);
				ai::Search::ActionStatePair asp(newstate, newaction);
				//std::cout<<"asp: " << newstate << std::endl;
				resultsout.push_back(asp);
				//std::cout <<"back: " << resultsout.back() << std::endl;
			}
		}
		return (resultsout.size() > 0);
	}
	double Problem::StepCost(const ai::Search::State * const state1in,
							const ai::Search::Action * const actionin,
							const ai::Search::State * const state2in)const
	{
		const State * const state1=dynamic_cast<const State * const>(state1in);
		const Action * const action=dynamic_cast<const Action * const>(actionin);
		const State * const state2=dynamic_cast<const State * const>(state2in);
		/* calculate the actual cost */
		double chargecost=1.0;
		int type=action->gettype();
		if(type>=Action::A_NORTH && type<=Action::A_WEST)
		{
			Cell currcell=this->model->getcell(state1->getx(),state1->gety());
			int direction=type;// because of care in ordering
			int terrain=currcell.GetTerrain(direction);
			if(terrain==I_MUD) {chargecost=2.0;}
			else if(terrain==I_ICE) {chargecost=10.0;}
		}
		else {/* must deal with other actions sometime */}
		double elevationcost=(state2->getz()-state1->getz())/1000.0;
		double totalcost=elevationcost+chargecost;
		return totalcost;
	}
	bool Problem::setgoal(State *goalstatein)
	{
		this->goalstate=goalstatein;
		return true;
	}
};
