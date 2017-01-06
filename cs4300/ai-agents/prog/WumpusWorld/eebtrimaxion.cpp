#include "eebtrimaxion.h"
//#include "eebstate.h"
//#include "eebproblem.h"
//#include "eebaction.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>

namespace eebt
{
	const int BUF_SIZE=1024;
	static char buf[BUF_SIZE];
	//static char buf2[BUF_SIZE];
	Trimaxion::Trimaxion()
	{
		SetName("Trimaxion");
		this->minx=1;
		this->maxx=4;
		this->miny=1;
		this->maxy=4;
		
		this->firstpostshot=true;
		this->turncount=0;
		this->homely=0;
	
		this->x=1;
		this->y=1;
		this->dir=EAST;
		this->arrow=true;
		this->golden=false;
		this->wumpus=true;
		/* I know there is no pit in 1,1 */
		std::sprintf(buf,"!P_1_1");
		eeb.AddSentence(buf);
		std::sprintf(buf,"!W_1_1");
		eeb.AddSentence(buf);
		this->rules();
	}
	Trimaxion::~Trimaxion(){/*None*/}
	ai::Agent::Action * Trimaxion::Program(const ai::Agent::Percept * percept)
	{
		if(this->x==minx && this->y==miny){homely++;}
		ai::PL::KnowledgeBase question;
		ai::Agent::Action *action=new ai::Agent::WumpusAction;
		this->parsepercepts(percept);
		if(this->actqueue.size()==0){this->goalsearch();}
		if(this->actqueue.size()==0){action->SetCode(ai::Agent::WumpusAction::QUIT);}
		else
		{
			Moves act = actqueue.front();
			this->actqueue.pop_front();
			std::cout<<"act: "<<act<<std::endl;
			if(act==FORWARD)
			{
				turncount=0;
				if(this->dir==NORTH) {this->y=this->y+1;}
				else if(this->dir==SOUTH) {this->y=this->y-1;}
				else if(this->dir==EAST) {this->x=this->x+1;}
				else if(this->dir==WEST) {this->x=this->x-1;}
				std::sprintf(buf,"V_%d_%d",this->x,this->y);
				eeb.AddSentence(buf);
				action->SetCode(ai::Agent::WumpusAction::FORWARD);
			}
			else if(act==TURN_RIGHT)
			{
				turncount++;
				if(this->dir==NORTH) {this->dir=EAST;}
				else if(this->dir==SOUTH) {this->dir=WEST;}
				else if(this->dir==EAST) {this->dir=SOUTH;}
				else if(this->dir==WEST) {this->dir=NORTH;}
				action->SetCode(ai::Agent::WumpusAction::TURN_RIGHT);
			}
			else if(act==TURN_LEFT)
			{
				turncount++;
				if(this->dir==NORTH) {this->dir=WEST;}
				else if(this->dir==SOUTH) {this->dir=EAST;}
				else if(this->dir==EAST) {this->dir=NORTH;}
				else if(this->dir==WEST) {this->dir=SOUTH;}
				action->SetCode(ai::Agent::WumpusAction::TURN_LEFT);
			}
			else if(act==GRAB) {action->SetCode(ai::Agent::WumpusAction::GRAB);}
			else if(act==SHOOT) {action->SetCode(ai::Agent::WumpusAction::SHOOT);}
			else {action->SetCode(ai::Agent::WumpusAction::QUIT);}
		}
		return action;
	}
	bool Trimaxion::rules()
	{	
		int a,b;
		int m,n;
		std::string statement, sentance;
		for(a=minx;a<=maxx;a++)
		{
			for(b=miny;b<maxy;b++)
			{
				std::string stra = static_cast<std::ostringstream*>( &(std::ostringstream() << a) )->str();
				std::string strb = static_cast<std::ostringstream*>( &(std::ostringstream() << b) )->str();
				if(a!=maxx) {std::string sentance=("W_"+stra+"_"+strb+" | ");}
				else {std::string sentance=("W_"+stra+"_"+strb);}
				statement.append(sentance);
			}
		}
		eeb.AddSentence(statement);
		for(m=minx;m<=maxx;m++)
		{
			for(n=miny;n<maxy;n++)
			{
				sprintf(buf,"S_%d_%d <=> W_%d_%d | W_%d_%d | W_%d_%d | W_%d_%d", m, n, m+1, n, m-1, n, m, n+1, m, n-1);
				eeb.AddSentence(buf);
				sprintf(buf,"B_%d_%d <=> P_%d_%d | P_%d_%d | P_%d_%d | P_%d_%d", m, n, m+1, n, m-1, n, m, n+1, m, n-1);
				eeb.AddSentence(buf);
				sprintf(buf,"N_%d_%d <=> (!P_%d_%d) & (!P_%d_%d) & (!P_%d_%d) & (!P_%d_%d) & (!W_%d_%d) & (!W_%d_%d) & (!W_%d_%d) & (!W_%d_%d)", 
										m, n, m+1, n, m-1, n, m, n+1, m, n-1, m+1, n, m-1, n, m, n+1, m, n-1);
				eeb.AddSentence(buf);
				if(m!=minx && n!=miny) 
				{	
					sprintf(buf,"!V_%d_%d", m, n);
					eeb.AddSentence(buf);
				}
			}
		}
		sprintf(buf,"V_%d_%d", minx, miny);
		eeb.AddSentence(buf);
		return true;
	}
	bool Trimaxion::parsepercepts(const ai::Agent::Percept *percept)
	{
		unsigned int i;
		for(i=0;i<percept->NumAtom();i++)
		{
			std::cout<<percept<<std::endl;
			if(percept->GetAtom("GLITTER").GetName() !="") 
			{
				std::sprintf(buf,"G_%d_%d",x,y);
				actqueue.push_back(GRAB);
				std::cout<<"shiny"<<std::endl;
				return true;
				
			}
			else if(percept->GetAtom("ARROW").GetName() =="1") {this->arrow=true;}
			else if(percept->GetAtom("ARROW").GetName() =="0") {this->arrow=false;}
			else if(percept->GetAtom("GOLD").GetName() =="1") {this->golden=true;}
			else if(percept->GetAtom("GOLD").GetName() =="0") {this->golden=false;}
			else if(percept->GetAtom("BREEZE").GetName() !="") {std::sprintf(buf,"B_%d_%d",x,y);}
			else if(percept->GetAtom("STENCH").GetName() !="") {std::sprintf(buf,"S_%d_%d",x,y);}
			else if(percept->GetAtom("WUMPUS").GetName() !="") {std::sprintf(buf,"W_%d_%d",x,y);}
			else if(percept->GetAtom("PIT").GetName() !="") {std::sprintf(buf,"P_%d_%d",x,y);}
			else if(percept->GetAtom("SCREAM").GetName() !="")
			{
				std::sprintf(buf,"R_%d_%d",x,y);
				this->wumpus=false;
			}
			else if(percept->GetAtom("BUMP").GetName() !="") {std::sprintf(buf,"M_%d_%d",x,y);}
			else {std::sprintf(buf,"N_%d_%d",x,y);}
			eeb.AddSentence(buf);
		}
		return true;
	}
	bool Trimaxion::goalsearch()
	{
		//special cases																										/*if(!this->arrow && this->wumpus && firstpostshot){firstpostshot=false;ShotResults();}*/
		if(this->golden)
		{
			actqueue.push_back(QUIT);
			std::cout<<"I'm in the money!"<<std::endl;
			ai::Agent::Action *action=new ai::Agent::WumpusAction;
			action->SetCode(ai::Agent::WumpusAction::QUIT);
			return true;
		}
		/*
		if(this->AskGlitter()) 
		{
			actqueue.push_back(GRAB);
			std::cout<<"shiny"<<std::endl;
			return true;
		}*/
		if(this->AskBreezyStart() && this->x==minx && this->y==miny) 
		{
			actqueue.push_back(QUIT);
			std::cout<<"breezy entrance"<<std::endl;
			return true;
		}
		if(this->AskSmellyStart() && this->x==minx && this->y==miny && this->arrow) 										//actqueue.push_back(SHOOT);//this->arrow=false;
		{
			actqueue.push_back(QUIT);
			std::cout<<"smelly entrance"<<std::endl;
			this->arrow=false;
			return true;
		}//regular moves  																									/*if(this->AskShoot()){actqueue.push_back(SHOOT);this->arrow=false;std::cout<<"The wumpus is there"<<std::endl;return true;}*/
		if(this->AskNextSafe() && !this->AskNextWall())
		{
			if(turncount>4)
			{
				actqueue.push_back(FORWARD);
				std::cout<<"go forward"<<std::endl;
				return true;
			}
			if(!this->AskNextVisited())
			{
				actqueue.push_back(FORWARD);
				std::cout<<"go forward"<<std::endl;
				return true;
			}
			else if(this->AskNextVisited())
			{
				if(!this->AskVisited(this->x,this->y+1)) {this->ChangeDirection(NORTH);}
				else if(!this->AskVisited(this->x,this->y-1)) {this->ChangeDirection(SOUTH);}
				else if(!this->AskVisited(this->x+1,this->y)) {this->ChangeDirection(EAST);}
				else if(!this->AskVisited(this->x-1,this->y)) {this->ChangeDirection(WEST);}
				return true;
			}
			return false;
		}
		//nowhere left to go
		//if(!this->AskNothing())
		if(homely>3)
		{
			actqueue.push_back(QUIT);
			std::cout<<"No where is safe, I quit!"<<std::endl;
			return true;
		}
		//default																											//else{actqueue.push_back(QUIT);std::cout<<"I don't know what to do so I'll quit"<<std::endl;return true;}
		else {actqueue.push_back(TURN_RIGHT);}
		return true;
	}
	bool Trimaxion::AskNextSafe()
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		if(this->wumpus)
		{
			if(this->dir==NORTH) {std::sprintf(buf, "(!W_%d_%d) & (!P_%d_%d)", x, y+1, x, y+1);}
			else if(this->dir==SOUTH) {std::sprintf(buf, "(!W_%d_%d) & (!P_%d_%d)", x, y-1, x, y-1);}
			else if(this->dir==EAST) {std::sprintf(buf, "(!W_%d_%d) & (!P_%d_%d)", x+1, y, x+1, y);}
			else if(this->dir==WEST) {std::sprintf(buf, "(!W_%d_%d) & (!P_%d_%d)", x-1, y, x-1, y);}
		}
		else if(!(this->wumpus))
		{
			if(this->dir==NORTH) {std::sprintf(buf, "!P_%d_%d", x, y+1);}
			else if(this->dir==SOUTH) {std::sprintf(buf, "!P_%d_%d", x, y-1);}
			else if(this->dir==EAST) {std::sprintf(buf, "!P_%d_%d", x+1, y);}
			else if(this->dir==WEST) {std::sprintf(buf, "!P_%d_%d", x-1, y);}
		}
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}
	bool Trimaxion::AskNextVisited()
	{
		if(this->dir==NORTH) { return (this->AskVisited(this->x, this->y+1));}
		else if(this->dir==SOUTH) { return (this->AskVisited(this->x, this->y-1));}
		else if(this->dir==EAST) { return (this->AskVisited(this->x+1, this->y));}
		else if(this->dir==WEST) { return (this->AskVisited(this->x-1, this->y));}
		else {return false;}
	}
	bool Trimaxion::AskNextWall()
	{
		if(this->dir==NORTH && y==maxy) {return true;}
		else if(this->dir==SOUTH && y==miny) {return true;}
		else if(this->dir==EAST && x==maxy) {return true;}
		else if(this->dir==WEST && x==miny) {return true;}
		else {return false;}
	}
	bool Trimaxion::AskSmellyStart()
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		std::sprintf(buf, "S_%d_%d ", minx, miny);
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}
	bool Trimaxion::AskBreezyStart()
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		std::sprintf(buf, "B_%d_%d ", minx, miny);
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}
	/*
	bool Trimaxion::AskGlitter()
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		std::sprintf(buf, "G_%d_%d ", this->x, this->y);
		
		std::cout<<"buf: "<<buf<<std::endl;
		std::cout<<"x: "<<this->x<<std::endl;
		std::cout<<"y: "<<this->y<<std::endl;
		
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}*/
	bool Trimaxion::AskVisited(int a, int b)
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		std::sprintf(buf, "V_%d_%d ", a, b);
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}
	bool Trimaxion::ChangeDirection(int goal)
	{
		if(this->dir == NORTH)
		{
			if(goal == NORTH){return true;}
			else if(goal == SOUTH) 
			{
				actqueue.push_back(TURN_RIGHT);
				actqueue.push_back(TURN_RIGHT);
			}
			else if(goal == EAST) {actqueue.push_back(TURN_RIGHT);}
			else if(goal == WEST) {actqueue.push_back(TURN_LEFT);}
		}
		else if(dir == SOUTH) 
		{
			if(goal == NORTH)
			{
				actqueue.push_back(TURN_RIGHT);
				actqueue.push_back(TURN_RIGHT);
			}
			else if(goal == SOUTH) {return true;}
			else if(goal == EAST) {actqueue.push_back(TURN_LEFT);}
			else if(goal == WEST) {actqueue.push_back(TURN_RIGHT);}
		}
		else if(this->dir == EAST)
		{
			if(goal == NORTH) {actqueue.push_back(TURN_LEFT);}
			else if(goal == SOUTH) {actqueue.push_back(TURN_RIGHT);}
			else if(goal == EAST) {return true;}
			else if(goal == WEST)
			{
				actqueue.push_back(TURN_RIGHT);
				actqueue.push_back(TURN_RIGHT);
			}
		}
		else if(dir == WEST)
		{
			if(goal == NORTH) {actqueue.push_back(TURN_RIGHT);}
			else if(goal == SOUTH) {actqueue.push_back(TURN_LEFT);}
			else if(goal == EAST)
			{
				actqueue.push_back(TURN_RIGHT);
				actqueue.push_back(TURN_RIGHT);
			}
			else if(goal == WEST){return true;}
		}
		return true;
	}
	bool Trimaxion::AskLocalNothing()
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		std::sprintf(buf, "N_%d_%d ", this->x, this->y);
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}
	bool Trimaxion::AskNothing()
	{
		int a,b;
		for(a=minx;a<=maxx;a++)
		{
			for(b=miny;b<maxy;b++)
			{
				bool rval;
				ai::PL::KnowledgeBase question;
				std::sprintf(buf, "N_%d_%d ", a, b);
				question.AddSentence(buf);
				rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
				if(rval) {return rval;}
			}
		}
		return false;
	}
}
	
	
	/*
	bool Trimaxion::ShotResults()
	{
		ai::PL::KnowledgeBase question;
		if(this->dir == NORTH)
		{
			int a=this->y;
			while(a<=maxy)
			{
				std::sprintf(buf, "!W_%d_%d ", this->x, a);
				question.AddSentence(buf);
				a++;
			}
			return true;
		}
		else if(this->dir == SOUTH) 
		{
			int a=this->y;
			while(a>=miny)
			{
				std::sprintf(buf, "!W_%d_%d ", this->x, a);
				question.AddSentence(buf);
				a--;
			}
			return true;
		}
		else if(this->dir == EAST)
		{
			int a=this->x;
			while(a<=maxx)
			{
				std::sprintf(buf, "!W_%d_%d ", a, this->y);
				question.AddSentence(buf);
				a++;
			}
			return true;
		}
		else if(this->dir == WEST)
		{
			int a=this->x;
			while(a>=minx)
			{
				std::sprintf(buf, "!W_%d_%d ", a, this->y);
				question.AddSentence(buf);
				a--;
			}
			return true;
		}
		return false;
	}*/
	/*
	bool Trimaxion::AskShoot()
	{
		if(this->dir == NORTH)
		{
			bool rval;
			int n=this->y;
			ai::PL::KnowledgeBase question;
			for(n=this->y;n<maxy;n++)
			{
				std::sprintf(buf, "W_%d_%d ", this->x, n);
				question.AddSentence(buf);
				rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
				if(rval){return rval;}
			}
			return false;
		}
		else if(this->dir == SOUTH) 
		{
			bool rval;
			int n;
			ai::PL::KnowledgeBase question;
			for(n=this->y;n>miny;n--)
			{
				std::sprintf(buf, "W_%d_%d ", this->x, n);
				question.AddSentence(buf);
				rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
				if(rval){return rval;}
			}
			return false;
		}
		else if(this->dir == EAST)
		{
			bool rval;
			int m;
			ai::PL::KnowledgeBase question;
			for(m=this->x;m<maxx;m++)
			{
				std::sprintf(buf, "W_%d_%d ", m, this->y);
				question.AddSentence(buf);
				rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
				if(rval){return rval;}
			}
			return false;
		}
		else if(this->dir == WEST)
		{
			bool rval;
			int m;
			ai::PL::KnowledgeBase question;
			for(m=this->x;m>minx;m--)
			{
				std::sprintf(buf, "W_%d_%d ", m, this->y);
				question.AddSentence(buf);
				rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
				if(rval){return rval;}
			}
			return false;
		}
		return false;
	}
}*/

		
		/*
		if(this->AskLocalNothing())
		{
			if(!this->AskVisited(this->x,this->y+1)) 
			{
				this->ChangeDirection(NORTH);
				//actqueue.push_back(FORWARD);
			}
			else if(!this->AskVisited(this->x,this->y-1)) 
			{
				this->ChangeDirection(SOUTH);
				//actqueue.push_back(FORWARD);
			}
			else if(!this->AskVisited(this->x+1,this->y)) 
			{
				this->ChangeDirection(EAST);
				//actqueue.push_back(FORWARD);
			}
			else if(!this->AskVisited(this->x-1,this->y)) 
			{
				this->ChangeDirection(WEST);
				//actqueue.push_back(FORWARD);
			}
			return true;
		}
		*/
		/*
		if(!this->AskVisited(this->x,this->y+1))
		{
			this->ChangeDirection(NORTH);
			if(this->AskNextSafe()) {actqueue.push_back(FORWARD);}
			std::cout<<"Face North"<<std::endl;
			return true;
		}
		else if(!this->AskVisited(this->x,this->y-1))
		{
			this->ChangeDirection(SOUTH);
			if(this->AskNextSafe()) {actqueue.push_back(FORWARD);}
			std::cout<<"Face South"<<std::endl;
			return true;
		}
		else if(!this->AskVisited(this->x+1,this->y))
		{
			this->ChangeDirection(EAST);
			if(this->AskNextSafe()) {actqueue.push_back(FORWARD);}
			std::cout<<"Face East"<<std::endl;
			return true;
		}
		else if(!this->AskVisited(this->x-1,this->y))
		{
			this->ChangeDirection(WEST);
			if(this->AskNextSafe()) {actqueue.push_back(FORWARD);}
			std::cout<<"Face West"<<std::endl;
			return true;
		}
		*/



















