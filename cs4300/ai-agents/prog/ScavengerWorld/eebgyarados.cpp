#include "eebgyarados.h"
#include "eebyaction.h"
#include "eebystate.h"
#include "eebyproblem.h"
#include <cstdio>
#include <cstring>

namespace eeby
{
	bool rockmode=false;
	bool first=true;
	Gyarados::Gyarados(ai::Agent::Options *opts)
		: algtype(ALG_GRAPH),
		fringetype(FRINGE_UCS),
		maxdepth(0)
	{
		SetName("Gyarados");
		this->model=new Model();
		if(opts->GetArgInt("user1")>0){this->algtype=opts->GetArgInt("user1");}
		if(opts->GetArgInt("user2")>0){this->fringetype=opts->GetArgInt("user2");}
		if(opts->GetArgInt("user3")>0){this->maxdepth=opts->GetArgInt("user3");}
		if(this->algtype<=ALG_MIN||this->algtype>=ALG_MAX||this->fringetype<=FRINGE_MIN||this->fringetype>=FRINGE_MAX)
		{
			std::cout<<"Usage: "<<std::endl
			<<"-U num: "<<ALG_TREE<<"=Tree, "<<ALG_GRAPH<<"=Graph "<<std::endl
			<<"-V num: "<<FRINGE_BFS<<"=BFS, "<<FRINGE_UCS<<"=UCS, "
			<<""<<FRINGE_DFS<<"=DFS, "<<FRINGE_DLS<<"=DLS, "<<FRINGE_IDS<<"=IDS "<<std::endl
			<<"-W num: Max depth for DLS or IDS"<<std::endl
			<<std::endl;
		}
	}
	Gyarados::~Gyarados()
	{
		if(this->model)
		{
			delete this->model;
			this->model=0;
		}
	}
	ai::Agent::Action * Gyarados::Program(const ai::Agent::Percept * percept)
	{
		if(first==true)
		{
			this->model->setcurx(0);
			this->model->setcury(0);
			this->model->setvisited(true);
			this->model->setlooked(false);
			//this->model->setexamined(false);
			Cell homecell=Cell(0,0);
			if(!this->model->addcell(homecell)){std::cerr<<"Error adding home Cell: "<<homecell<<std::endl;}
			first=false;
		}
		ai::Scavenger::Action *action=new ai::Scavenger::Action;
		this->parsepercepts(percept);
		if(this->actqueue.size()==0){this->goalsearch();}
		if(this->actqueue.size()==0){action->SetCode(ai::Scavenger::Action::QUIT);}
		else
		{	
			Action act = this->actqueue.front();
			this->actqueue.pop_front();
			switch(act.gettype())
			{
				case Action::A_NORTH:
					action->SetCode(ai::Scavenger::Action::GO_NORTH);
					break;
				case Action::A_SOUTH:
					action->SetCode(ai::Scavenger::Action::GO_SOUTH);
					break;
				case Action::A_EAST:
					action->SetCode(ai::Scavenger::Action::GO_EAST);
					break;
				case Action::A_WEST:
					action->SetCode(ai::Scavenger::Action::GO_WEST);
					break;
				case Action::RECHARGE:
					action->SetCode(ai::Scavenger::Action::RECHARGE);
					break;
				case Action::L_NORTH:
					action->SetDirection(ai::Scavenger::Location::NORTH);
					action->SetCode(ai::Scavenger::Action::LOOK);
					this->model->setlastlooked(0);
					break;
				case Action::L_SOUTH:
					action->SetDirection(ai::Scavenger::Location::SOUTH);
					action->SetCode(ai::Scavenger::Action::LOOK);
					this->model->setlastlooked(1);
					break;
				case Action::L_EAST:
					action->SetDirection(ai::Scavenger::Location::EAST);
					action->SetCode(ai::Scavenger::Action::LOOK);
					this->model->setlastlooked(2);
					break;
				case Action::L_WEST:
					action->SetDirection(ai::Scavenger::Location::WEST);
					action->SetCode(ai::Scavenger::Action::LOOK);
					this->model->setlastlooked(3);
					break;
				//case Action::EXAMINE:
					//action->SetCode(ai::Scavenger::Action::EXAMINE);
					//break;
				default:
					action->SetCode(ai::Scavenger::Action::QUIT);
					break;
			}
		}
		return action;
	}
	bool Gyarados::parsepercepts(const ai::Agent::Percept *percept)
	{
		double x,y,z,charge,hp;
		int north,south,east,west;
		int nx,ny,nkey,sx,sy,skey,ex,ey,ekey,wx,wy,wkey;
		//const char* object;
		x=atof(percept->GetAtom("X_LOC").GetValue().c_str());
		y=atof(percept->GetAtom("Y_LOC").GetValue().c_str());
		z=atof(percept->GetAtom("Z_LOC").GetValue().c_str());
		charge=atof(percept->GetAtom("CHARGE").GetValue().c_str());
		hp=atof(percept->GetAtom("HP").GetValue().c_str());

		this->model->setcurx(x);
		this->model->setcury(y);
		this->model->setcurz(z);
		this->model->setcharge(charge);
		this->model->sethp(hp);
		std::cout<<"percept "<<percept<<std::endl;
		
		Cell curnewcell=Cell(x,y);
		if(!this->model->addcell(curnewcell)){std::cerr<<"Error adding world Cell: "<<curnewcell<<std::endl;}
		this->model->getcell(x,y).setz(z);
		this->model->getcell(x,y).setvisited(true);
		
		if(this->model->getcell(x,y).getlooked()==false)
		{
			this->lookarround();
			this->model->getcell(x,y).setlooked(true);
			return true;
		}
		/*if(this->model->getcell(x,y).getexamined()==false)
		{
			Action EXAMINE=Action();
			EXAMINE.settype(Action::EXAMINE);
			this->actqueue.push_back(EXAMINE);
			this->model->getcell(x,y).setexamined(true);
			return true;
		}
		if(this->model->getcell(x,y).getexamined()==true)
		{
			object=percept->GetAtom("OBJECT_OBJ00016").GetValue().c_str();
			std::cout<<"object: "<<object<<std::endl;
		}*/
		else if(this->model->getcell(x,y).getlooked()==true)
		{
			if(this->model->getlastlooked()==0)
			{
				north=Cell::TerrainLabelToEnum(percept->GetAtom("LOOK").GetValue().c_str());
				this->model->setcurnorth(north);
				this->model->getcell(this->model->getcurx(),this->model->getcury()).setnorth(north);
				if(north!=3 && north!=4)// || (rockmode==true && north!=4))
				{
					nx=x;
					ny=y+1000;
					nkey=this->model->PositionToKey(nx,ny);
					Cell nnewcell=Cell(nx,ny);
					if(!this->model->addcell(nnewcell)){std::cerr<<"Error adding world Cell: "<<nnewcell<<std::endl;}
					if(this->model->getcell(nx,ny).getvisited()==false)
					{
						if(!this->model->addgoal(nnewcell)){std::cerr<<"Error adding goal Cell: "<<nnewcell<<std::endl;}
						this->goalkeylist.push_back(nkey);
					}
				}
			}
			if(this->model->getlastlooked()==1)
			{
				south=Cell::TerrainLabelToEnum(percept->GetAtom("LOOK").GetValue().c_str());
				this->model->setcursouth(south);
				this->model->getcell(this->model->getcurx(),this->model->getcury()).setsouth(south);
				if(south!=3 && south!=4)// || (rockmode==true && south!=4))
				{
					sx=x;
					sy=y-1000;
					skey=this->model->PositionToKey(sx,sy);
					Cell snewcell=Cell(sx,sy);
					if(!this->model->addcell(snewcell)){std::cerr<<"Error adding world Cell: "<<snewcell<<std::endl;}
					if(this->model->getcell(sx,sy).getvisited()==false)
					{
						if(!this->model->addgoal(snewcell)){std::cerr<<"Error adding goal Cell: "<<snewcell<<std::endl;}
						this->goalkeylist.push_back(skey);
					}
				}
			}
			if(this->model->getlastlooked()==2)
			{
				east=Cell::TerrainLabelToEnum(percept->GetAtom("LOOK").GetValue().c_str());
				this->model->setcureast(east);
				this->model->getcell(this->model->getcurx(),this->model->getcury()).seteast(east);
				if(east!=3 && east!=4)// || (rockmode==true && east!=4))
				{
					ex=x+1000;
					ey=y;
					ekey=this->model->PositionToKey(ex,ey);
					Cell enewcell=Cell(ex,ey);
					if(!this->model->addcell(enewcell)){std::cerr<<"Error adding world Cell: "<<enewcell<<std::endl;}
					if(this->model->getcell(ex,ey).getvisited()==false)
					{
						if(!this->model->addgoal(enewcell)){std::cerr<<"Error adding goal Cell: "<<enewcell<<std::endl;}
						this->goalkeylist.push_back(ekey);
					}
				}
			}
			if(this->model->getlastlooked()==3)
			{
				west=Cell::TerrainLabelToEnum(percept->GetAtom("LOOK").GetValue().c_str());
				this->model->setcurwest(west);
				this->model->getcell(this->model->getcurx(),this->model->getcury()).setwest(west);
				if(west!=3 && west!=4)// || (rockmode==true && west!=4))
				{
					wx=x-1000;
					wy=y;
					wkey=this->model->PositionToKey(wx,wy);
					Cell wnewcell=Cell(wx,wy);
					if(!this->model->addcell(wnewcell)){std::cerr<<"Error adding world Cell: "<<wnewcell<<std::endl;}
					if(this->model->getcell(wx,wy).getvisited()==false)
					{
						if(!this->model->addgoal(wnewcell)){std::cerr<<"Error adding goal Cell: "<<wnewcell<<std::endl;}
						this->goalkeylist.push_back(wkey);
					}
				}
			}
		}
		return true;
	}
	bool Gyarados::lookarround()
	{
		Action L_WEST=Action();
		L_WEST.settype(Action::L_WEST);
		this->actqueue.push_back(L_WEST);
		
		Action L_EAST=Action();
		L_EAST.settype(Action::L_EAST);
		this->actqueue.push_back(L_EAST);
		
		Action L_SOUTH=Action();
		L_SOUTH.settype(Action::L_SOUTH);
		this->actqueue.push_back(L_SOUTH);
		
		Action L_NORTH=Action();
		L_NORTH.settype(Action::L_NORTH);
		this->actqueue.push_back(L_NORTH);
		return true;
	}
	bool Gyarados::goalsearch()
	{	
		bool done=false;
		int depth=1;
		int goalkey; 
		int goalx=0; 
		int goaly=0;
		
		
		State *curstate=new State();
		curstate->setx(this->model->getcurx());
		curstate->sety(this->model->getcury());
		curstate->setz(this->model->getcurz());
		curstate->setcharge(this->model->getcharge());
		curstate->sethp(this->model->gethp());
		if(this->model->getcurx()==0 && this->model->getcury()==0 && this->model->getcharge()<95)
		{
			Action RECHARGE=Action();
			RECHARGE.settype(Action::RECHARGE);
			this->actqueue.push_back(RECHARGE);
			return true;
		}
		while(!done)
		{	
			/*std::cerr<<"this->goalkeylist.size(): "<<this->goalkeylist.size()<<std::endl;
			std::cerr<<"this->model->goals.size(): " << this->model->goals.size() << std::endl;
			for(std::map<int, Cell>::const_iterator it = this->model->goals.begin();
				it != this->model->goals.end();
				it++)
				{
					std::cerr << it->first << " " << it->second.getx() << "," << it->second.gety() << std::endl;
				}
		
		
			std::cerr<<"this->model->world.size(): " << this->model->world.size() << std::endl;
			for(std::map<int, Cell>::const_iterator it = this->model->world.begin();
				it != this->model->world.end();
				it++)
				{
					std::cerr << it->first << " " << it->second.getx() << "," << it->second.gety() << std::endl;
				}*/
				
			State *goalstate=new State();
			
			goalkey=this->goalkeylist.back();
			goalx=this->model->goals.find(goalkey)->second.getx();
			goaly=this->model->goals.find(goalkey)->second.gety();
			if(this->model->world.find(goalkey)->second.getvisited()==false)
			{
				goalstate->setx(goalx);
				goalstate->sety(goaly);
			}
			else if(this->model->world.find(goalkey)->second.getvisited()==true)
			{
				this->goalkeylist.pop_back();
				this->model->goals.erase(goalkey);
				continue;
			}
			if(this->model->getcharge()<=(this->homecheck()+this->goalcheck(goalx, goaly)+7))
			{
				goalstate->setx(0);
				goalstate->sety(0);
				goalstate->setz(0);
			}
			else if(this->model->getcharge()>(this->homecheck()+this->goalcheck(goalx, goaly)))
			{
				this->goalkeylist.pop_back();
				this->model->goals.erase(goalkey);
			}
			Problem *curproblem=new Problem(curstate,this->model);
			curproblem->setgoal(goalstate);

			ai::Search::Fringe *thefrontier=0;
			switch(this->fringetype)
			{
				case FRINGE_BFS:
					thefrontier=new ai::Search::BFFringe();
					done=true;
					break;
				case FRINGE_UCS:
					thefrontier=new ai::Search::UCFringe();
					done=true;
					break;
				case FRINGE_DFS:
					thefrontier=new ai::Search::DFFringe();
					done=true;
					break;
				case FRINGE_DLS:
					thefrontier=new ai::Search::DLFringe(depth);
					done=true;
					break;
				case FRINGE_IDS:
					thefrontier=new ai::Search::DLFringe(depth);
					if(depth==this->maxdepth){done=true;}
					depth++;
					break;
			}
			ai::Search::Algorithm *thealgorithm=0;
			//std::cout<<"this->algtype: "<<this->algtype<<std::endl;
			//std::cout << "### Types ###" << std::endl;
			//std::cout << ALG_TREE << std::endl;
			//std::cout << ALG_GRAPH << std::endl;
			switch (this->algtype)
			{
				case ALG_TREE:
					thealgorithm=new ai::Search::Tree(curproblem,thefrontier);
					break;
				case ALG_GRAPH:
					thealgorithm=new ai::Search::Graph(curproblem,thefrontier);
					break;
			}
			if(thealgorithm->Search())
			{
				std::list<ai::Search::Node*> *solution=thealgorithm->GetSolution().GetList();
				std::list<ai::Search::Node*>::const_iterator it;
				double cost=0;
				int depth=0;
				for(it=solution->begin();it!=solution->end();it++)
				{
					if((*it)->GetAction())
					{
						const Action * const action=dynamic_cast<const Action * const>((*it)->GetAction());
						std::cout<<*action<<" ";
						this->actqueue.push_back(*action);
					}
					if((*it)->GetState())
					{
						const State * const state=dynamic_cast<const State * const>((*it)->GetState());
						std::cout<<*state<<" ";
					}
					cost=(*it)->GetPathCost();
					depth=(*it)->GetDepth();
					std::cout<<std::endl;
				}
				size_t nodes_generated=thealgorithm->GetNumberNodesGenerated();
				size_t nodes_stored=thealgorithm->GetMaxNodesStored();
				std::cout<<"Results: T "<<cost<<" "<<depth<<" "<<nodes_generated<<" "<<nodes_stored<<std::endl;
				done=true;
			}
			delete thealgorithm;
		}
		return true;
	}
	double Gyarados::homecheck()
	{
		int homedepth=1;
		double homecost=0;
		State *curstate=new State();
		curstate->setx(this->model->getcurx());
		curstate->sety(this->model->getcury());
		curstate->setz(this->model->getcurz());
		curstate->setcharge(this->model->getcharge());
		curstate->sethp(this->model->gethp());

		State *homestate=new State();
		homestate->setx(0);
		homestate->sety(0);
		
		Problem *curproblem=new Problem(curstate,this->model);
		curproblem->setgoal(homestate);
		
		ai::Search::Fringe *thefrontier=0;
		switch(this->fringetype)
		{
			case FRINGE_BFS:
				thefrontier=new ai::Search::BFFringe();
				break;
			case FRINGE_UCS:
				thefrontier=new ai::Search::UCFringe();
				break;
			case FRINGE_DFS:
				thefrontier=new ai::Search::DFFringe();
				break;
			case FRINGE_DLS:
				thefrontier=new ai::Search::DLFringe(homedepth);
				break;
			case FRINGE_IDS:
				thefrontier=new ai::Search::DLFringe(homedepth);
				homedepth++;
				break;
		}
		ai::Search::Algorithm *homealgorithm=0;
		switch(this->algtype)
		{
		case ALG_TREE:
			homealgorithm=new ai::Search::Tree(curproblem,thefrontier);
			break;
		case ALG_GRAPH:
			homealgorithm=new ai::Search::Graph(curproblem,thefrontier);
			break;
		}
		if(homealgorithm->Search())
		{
			std::list<ai::Search::Node*> *solution=homealgorithm->GetSolution().GetList();
			std::list<ai::Search::Node*>::const_iterator it;
			homecost=0;
			homedepth=0;
			for(it=solution->begin();it!=solution->end();it++)
			{
				homecost=(*it)->GetPathCost();
				homedepth=(*it)->GetDepth();
				std::cout<<"homecost: "<<homecost<<" "<<"homedepth: "<<homedepth<<std::endl;
			}
			delete homealgorithm;
			return homecost;
		}
		else
		{
			std::cout<<"home check error"<<std::endl;
			return -1;
		}
	}
	double Gyarados::goalcheck(int x, int y)
	{
		std::cout<<"GC"<<std::endl;
		int goaldepth=1;
		double goalcost;
		State *curstate=new State();
		curstate->setx(this->model->getcurx());
		curstate->sety(this->model->getcury());
		curstate->setz(this->model->getcurz());
		curstate->setcharge(this->model->getcharge());
		curstate->sethp(this->model->gethp());
		
		State *goalstate=new State();
		goalstate->setx(x);
		std::cout<<"goalx: "<<goalstate->getx()<<std::endl;
		goalstate->sety(y);
		std::cout<<"goaly: "<<goalstate->gety()<<std::endl;

		Problem *curproblem=new Problem(curstate,this->model);
		curproblem->setgoal(goalstate);
		
		ai::Search::Fringe *thefrontier=0;
		switch(this->fringetype)
		{
			case FRINGE_BFS:
				thefrontier=new ai::Search::BFFringe();
				break;
			case FRINGE_UCS:
				thefrontier=new ai::Search::UCFringe();
				break;
			case FRINGE_DFS:
				thefrontier=new ai::Search::DFFringe();
				break;
			case FRINGE_DLS:
				thefrontier=new ai::Search::DLFringe(goaldepth);
				break;
			case FRINGE_IDS:
				thefrontier=new ai::Search::DLFringe(goaldepth);
				goaldepth++;
				break;
		}
		ai::Search::Algorithm *goalalgorithm=0;
		switch(this->algtype)
		{
		case ALG_TREE:
			goalalgorithm=new ai::Search::Tree(curproblem,thefrontier);
			break;
		case ALG_GRAPH:
			goalalgorithm=new ai::Search::Graph(curproblem,thefrontier);
			break;
		}
		if(goalalgorithm->Search())
		{

			std::list<ai::Search::Node*> *goalsolution=goalalgorithm->GetSolution().GetList();
			std::list<ai::Search::Node*>::const_iterator it;
			goalcost=0;
			goaldepth=0;
			for(it=goalsolution->begin();it!=goalsolution->end();it++)
			{
				goalcost=(*it)->GetPathCost();
				goaldepth=(*it)->GetDepth();
				std::cout<<"goalcost: "<<goalcost<<" "<<"goaldepth: "<<goaldepth<<std::endl;
			}
			delete goalalgorithm;
			return goalcost;
		}
		else
		{
			std::cout<<"goal check error"<<std::endl;
			return -1;
		}
	}
};
	

 
