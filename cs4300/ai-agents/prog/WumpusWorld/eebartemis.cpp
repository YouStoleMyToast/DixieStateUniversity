#include "eebartemis.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>

namespace eeba
{
	const int BUF_SIZE=1024;
	static char buf[BUF_SIZE];
	//static char buf2[BUF_SIZE];
	int minx=1;
	int maxx=4;
	int miny=1;
	int maxy=4;
	bool firstpostshot=true;
	int turncount=0;
	int homely=0;
	Artemis::Artemis()
	{
		SetName("Artemis");
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
	Artemis::~Artemis(){/*None*/}
	ai::Agent::Action * Artemis::Program(const ai::Agent::Percept * percept)
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
			if(act==FORWARD)
			{
				turncount=0;
				if(this->dir==NORTH) {this->y=this->y+1;}
				else if(this->dir==SOUTH) {this->y=this->y-1;}
				else if(this->dir==EAST) {this->x=this->x+1;}
				else if(this->dir==WEST) {this->x=this->x-1;}
				action->SetCode(ai::Agent::WumpusAction::FORWARD);
			}
			else {action->SetCode(ai::Agent::WumpusAction::QUIT);}
		}
		return action;
	}
	bool Artemis::rules()
	{	
		int m,n;
		for(m=minx;m<maxx+1;m++)
		{
			for(n=miny;n<maxy+1;n++)
			{/*
				if((m>minx && m<maxx) && (n>miny && n<maxy))
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d | P_%d_%d | P_%d_%d)", m, n, m+1, n, m-1, n, m, n+1, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==minx && (n>miny && n<maxy))
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d | P_%d_%d)", m, n, m+1, n, m, n+1, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==maxx && (n>miny && n<maxy))
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d | P_%d_%d)", m, n, m-1, n, m, n+1, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if((m>minx && m<maxx) && n==miny)
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d | P_%d_%d)", m, n, m+1, n, m-1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if((m>minx && m<maxx) && n==maxy)
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d | P_%d_%d)", m, n, m+1, n, m-1, n, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==minx && n==miny)
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d)", m, n, m+1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==maxx && n==miny)
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d)", m, n, m-1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==minx && n==maxy)
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d)", m, n, m+1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==maxx && n==maxy)
				{
					sprintf(buf,"B_%d_%d <=> (P_%d_%d | P_%d_%d)", m, n, m-1, n, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}*/
				if((m>minx && m<maxx) && (n>miny && n<maxy))
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d | B_%d_%d | B_%d_%d)", m, n, m+1, n, m-1, n, m, n+1, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==minx && (n>miny && n<maxy))
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d | B_%d_%d)", m, n, m+1, n, m, n+1, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==maxx && (n>miny && n<maxy))
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d | B_%d_%d)", m, n, m-1, n, m, n+1, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if((m>minx && m<maxx) && n==miny)
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d | B_%d_%d)", m, n, m+1, n, m-1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if((m>minx && m<maxx) && n==maxy)
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d | B_%d_%d)", m, n, m+1, n, m-1, n, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==minx && n==miny)
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d)", m, n, m+1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==maxx && n==miny)
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d)", m, n, m-1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==minx && n==maxy)
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d)", m, n, m+1, n, m, n+1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
				else if(m==maxx && n==maxy)
				{
					sprintf(buf,"P_%d_%d <=> (B_%d_%d | B_%d_%d)", m, n, m-1, n, m, n-1);
					std::cout<<buf<<std::endl;
					eeb.AddSentence(buf);
				}
			}
		}
		return true;
	}
	bool Artemis::parsepercepts(const ai::Agent::Percept *percept)
	{
		unsigned int i;
		for(i=0;i<percept->NumAtom();i++)
		{
			if(percept->GetAtom("BREEZE").GetName() !="") {std::sprintf(buf,"B_%d_%d",this->x,this->y);}
			else if(percept->GetAtom("PIT").GetName() !="") {std::sprintf(buf,"P_%d_%d",this->x,this->y);}
			std::cout<<buf<<std::endl;
			eeb.AddSentence(buf);
		}
		return true;
	}
	bool Artemis::goalsearch()
	{
		if(!this->AskNextPit())
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		else {actqueue.push_back(QUIT);}
		return true;
	}
	bool Artemis::AskNextPit()
	{
		bool rval;
		if(this->dir==NORTH) 
		{
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "P_%d_%d", x, y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			if(rval) {std::cout<<"pit: "<<buf<<std::endl;}
			else {std::cout<<"not pit: "<<buf<<std::endl;}
			return rval;
		}
		else if(this->dir==SOUTH) 
		{
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "P_%d_%d", x, y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			if(rval) {std::cout<<"pit: "<<buf<<std::endl;}
			else {std::cout<<"not pit: "<<buf<<std::endl;}
			return rval;
		}
		else if(this->dir==EAST) 
		{
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "P_%d_%d", x+1, y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			if(rval) {std::cout<<"pit: "<<buf<<std::endl;}
			else {std::cout<<"not pit: "<<buf<<std::endl;}
			return rval;
		}
		else if(this->dir==WEST) 
		{
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "P_%d_%d", x-1, y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			if(rval) {std::cout<<"pit: "<<buf<<std::endl;}
			else {std::cout<<"not pit: "<<buf<<std::endl;}
			return rval;
		}
		return false;
	}
}
