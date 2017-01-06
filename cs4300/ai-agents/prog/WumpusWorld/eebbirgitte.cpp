#include "eebbirgitte.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>

namespace eebb
{
	const int BUF_SIZE=1024;
	static char buf[BUF_SIZE];
	//static char buf2[BUF_SIZE];
	Birgitte::Birgitte()
	{
		SetName("Birgitte");
		this->minx=1;
		this->maxx=4;
		this->miny=1;
		this->maxy=4;
		this->x=1;
		this->y=1;
		this->dir=EAST;
		this->arrow=true;
		this->golden=false;
		this->wumpus=true;
		this->turncount=0;
		this->homely=0;
		std::sprintf(buf,"!P_1_1");
		eeb.AddSentence(buf);
		std::sprintf(buf,"!W_1_1");
		eeb.AddSentence(buf);
		rules();
	}
	Birgitte::~Birgitte(){/*None*/}
	ai::Agent::Action * Birgitte::Program(const ai::Agent::Percept * percept)
	{
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
				this->turncount=0;
				if(this->dir==NORTH) {this->y=this->y+1;}
				else if(this->dir==SOUTH) {this->y=this->y-1;}
				else if(this->dir==EAST) {this->x=this->x+1;}
				else if(this->dir==WEST) {this->x=this->x-1;}
				std::sprintf(buf,"V_%d_%d",this->x,this->y);
				eeb.AddSentence(buf);
				std::cout<<buf<<std::endl;
				action->SetCode(ai::Agent::WumpusAction::FORWARD);
			}
			else if(act==TURN_RIGHT)
			{
				this->turncount++;
				if(this->dir==NORTH) {this->dir=EAST;}
				else if(this->dir==SOUTH) {this->dir=WEST;}
				else if(this->dir==EAST) {this->dir=SOUTH;}
				else if(this->dir==WEST) {this->dir=NORTH;}
				action->SetCode(ai::Agent::WumpusAction::TURN_RIGHT);
			}
			else if(act==TURN_LEFT)
			{
				this->turncount++;
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
	bool Birgitte::rules()
	{	
		int m,n,a,b,c,d,x,z;
		std::string statement1, statement2, statement3;
		std::string stench,stench1,stench2,stench3,stench4,stench5;
		std::string breeze,breeze1,breeze2,breeze3,breeze4,breeze5;
		std::string stra,strb,strc,strd,stre,strf,strg,strh,stri,strj,strk,strl,strm,strn,stro,strp,strq,strr,strx,strz;
		
		/*sprintf(buf,"W_1_2 | W_1_3 | W_1_4 | W_2_1 | W_2_2 | W_2_3 | W_2_4 | W_3_1 | W_3_2 | W_3_3 | W_3_4 | W_4_1 | W_4_2 | W_4_3 | W_4_4");	
		std::cout<<buf<<std::endl;
		eeb.AddSentence(buf);
		sprintf(buf,"G_1_2 | G_1_3 | G_1_4 | G_2_1 | G_2_2 | G_2_3 | G_2_4 | G_3_1 | G_3_2 | G_3_3 | G_3_4 | G_4_1 | G_4_2 | G_4_3 | G_4_4");	
		std::cout<<buf<<std::endl;
		eeb.AddSentence(buf);*/
		stre = "(S_";
		strf = "_";
		strg = ") <=> ";
		strh = "(W_";
		stri = ") | ";
		strj = "(B_";
		strk = "(P_";
		strl = ")";
		stro = "(W_";
		strp = "(G_";
		strq = "(!W_";
		strr = " & ";
		
		
		for(m=this->minx;m<=this->maxx;m++)
		{
			for(n=this->miny;n<=this->maxy;n++)
			{
				a=m+1;
				b=m-1;
				c=n+1;
				d=n-1;
				stra = static_cast<std::ostringstream*>( &(std::ostringstream() << a))->str();
				strb = static_cast<std::ostringstream*>( &(std::ostringstream() << b))->str();
				strc = static_cast<std::ostringstream*>( &(std::ostringstream() << c))->str();
				strd = static_cast<std::ostringstream*>( &(std::ostringstream() << d))->str();
				strm = static_cast<std::ostringstream*>( &(std::ostringstream() << m))->str();
				strn = static_cast<std::ostringstream*>( &(std::ostringstream() << n))->str();
				statement3 = "";
				statement3.append(stro+strm+strf+strn+strg);
				for(x=minx;x<=maxx;x++)
				{
					for(z=miny;z<=maxy;z++)
					{
						strx = static_cast<std::ostringstream*>( &(std::ostringstream() << x))->str();
						strz = static_cast<std::ostringstream*>( &(std::ostringstream() << z))->str();
						if((x==this->maxx && z==this->maxy) && (x!=m || z!=n)){statement3.append(strq+strx+strf+strz+strl);}
						else if((m==this->maxx && n==this->maxy) && (x==m && z==n-1)) {statement3.append(strq+strx+strf+strz+strl);}
						else if((x!=this->maxx || z!=this->maxy) && (x!=m || z!=n)) {statement3.append(strq+strx+strf+strz+strl+strr);}
					}
				}
				std::cout<<statement3<<std::endl;
				eeb.AddSentence(statement3);
			}
		}
		for(m=this->minx;m<=this->maxx;m++)
		{
			for(n=this->miny;n<=this->maxy;n++)
			{
				a=m+1;
				b=m-1;
				c=n+1;
				d=n-1;
				stra = static_cast<std::ostringstream*>( &(std::ostringstream() << a))->str();
				strb = static_cast<std::ostringstream*>( &(std::ostringstream() << b))->str();
				strc = static_cast<std::ostringstream*>( &(std::ostringstream() << c))->str();
				strd = static_cast<std::ostringstream*>( &(std::ostringstream() << d))->str();
				strm = static_cast<std::ostringstream*>( &(std::ostringstream() << m))->str();
				strn = static_cast<std::ostringstream*>( &(std::ostringstream() << n))->str();
				if(m!=this->maxx || n!=this->maxy) {statement1.append(stro+strm+strf+strn+stri);}
				else {statement1.append(stro+strm+strf+strn+strl);}	
				if(m!=this->maxx || n!=this->maxy) {statement2.append(strp+strm+strf+strn+stri);}
				else {statement2.append(strp+strm+strf+strn+strl);}
			}
		}
		std::cout<<statement1<<std::endl;
		eeb.AddSentence(statement1);
		std::cout<<statement2<<std::endl;
		eeb.AddSentence(statement2);
		for(m=this->minx;m<=this->maxx;m++)
		{
			for(n=this->miny;n<=this->maxy;n++)
			{
				a=m+1;
				b=m-1;
				c=n+1;
				d=n-1;
				stra = static_cast<std::ostringstream*>( &(std::ostringstream() << a))->str();
				strb = static_cast<std::ostringstream*>( &(std::ostringstream() << b))->str();
				strc = static_cast<std::ostringstream*>( &(std::ostringstream() << c))->str();
				strd = static_cast<std::ostringstream*>( &(std::ostringstream() << d))->str();
				strm = static_cast<std::ostringstream*>( &(std::ostringstream() << m))->str();
				strn = static_cast<std::ostringstream*>( &(std::ostringstream() << n))->str();

				stench1=stre+strm+strf+strn+strg;
				stench2=strh+stra+strf+strn;
				stench3=strh+strb+strf+strn;
				stench4=strh+strm+strf+strc;
				stench5=strh+strm+strf+strd;
				
				breeze1=strj+strm+strf+strn+strg;
				breeze2=strk+stra+strf+strn;
				breeze3=strk+strb+strf+strn;
				breeze4=strk+strm+strf+strc;
				breeze5=strk+strm+strf+strd;

				//all
				if(a<maxx+1 && b>minx-1 && c<maxx+1 && d>minx-1)
				{
					stench=stench1+stench2+stri+stench3+stri+stench4+stri+stench5+strl;
					breeze=breeze1+breeze2+stri+breeze3+stri+breeze4+stri+breeze5+strl;
				}
				//non a
				else if(a==maxx+1 && b>minx-1 && c<maxx+1 && d>minx-1)
				{
					stench=stench1+stench3+stri+stench4+stri+stench5+strl;
					breeze=breeze1+breeze3+stri+breeze4+stri+breeze5+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c<maxx+1 && d>minx-1)
				{
					stench=stench1+stench3+stri+stench4+stri+stench5+strl;
					breeze=breeze1+breeze3+stri+breeze4+stri+breeze5+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench3+stri+stench5+strl;
					breeze=breeze1+breeze3+stri+breeze5+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench3+stri+stench4+strl;
					breeze=breeze1+breeze3+stri+breeze4+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench5+strl;
					breeze=breeze1+breeze5+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench4+strl;
					breeze=breeze1+breeze4+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench4+strl;
					breeze=breeze1+breeze4+strl;
				}
				//non b
				else if(a<maxx+1 && b==minx-1 && c<maxx+1 && d>minx-1)
				{
					stench=stench1+stench2+stri+stench4+stri+stench5+strl;
					breeze=breeze1+breeze2+stri+breeze4+stri+breeze5+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c<maxx+1 && d>minx-1)
				{
					stench=stench1+stench4+stri+stench5+strl;
					breeze=breeze1+breeze4+stri+breeze5+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench2+stri+stench5+strl;
					breeze=breeze1+breeze2+stri+breeze5+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+stri+stench4+strl;
					breeze=breeze1+breeze2+stri+breeze4+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench5+strl;
					breeze=breeze1+breeze5+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+strl;
					breeze=breeze1+breeze2+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench4+strl;
					breeze=breeze1+breeze4+strl;
				}
				//non c
				else if(a<maxx+1 && b>minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench2+stri+stench3+stri+stench5+strl;
					breeze=breeze1+breeze2+stri+breeze3+stri+breeze5+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench3+stri+stench5+strl;
					breeze=breeze1+breeze3+stri+breeze5+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench2+stri+stench5+strl;
					breeze=breeze1+breeze2+stri+breeze5+strl;
				}
				else if(a<maxx+1 && b>minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+stri+stench3+strl;
					breeze=breeze1+breeze2+stri+breeze3+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+strl;
					breeze=breeze1+breeze2+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench3+strl;
					breeze=breeze1+breeze3+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c==maxx+1 && d>minx-1)
				{
					stench=stench1+stench5+strl;
					breeze=breeze1+breeze5+strl;
				}
				//non d
				else if(a<maxx+1 && b>minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+stri+stench3+stri+stench4+strl;
					breeze=breeze1+breeze2+stri+breeze3+stri+breeze4+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench3+stri+stench4+strl;
					breeze=breeze1+breeze3+stri+breeze4+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+stri+stench4+strl;
					breeze=breeze1+breeze2+stri+breeze4+strl;
				}
				else if(a<maxx+1 && b>minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+stri+stench3+strl;
					breeze=breeze1+breeze2+stri+breeze3+strl;
				}
				else if(a<maxx+1 && b==minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench2+strl;
					breeze=breeze1+breeze2+strl;
				}
				else if(a==maxx+1 && b>minx-1 && c==maxx+1 && d==minx-1)
				{
					stench=stench1+stench3+strl;
					breeze=breeze1+breeze3+strl;
				}
				else if(a==maxx+1 && b==minx-1 && c<maxx+1 && d==minx-1)
				{
					stench=stench1+stench4+strl;
					breeze=breeze1+breeze4+strl;
				}
				std::cout<<stench<<std::endl;
				eeb.AddSentence(stench);
				std::cout<<breeze<<std::endl;
				eeb.AddSentence(breeze);
			}
		}
		return true;
	}
	bool Birgitte::parsepercepts(const ai::Agent::Percept *percept)
	{
		if(percept->GetAtom("GLITTER").GetName() !="") 
		{
			this->golden=true;
			std::sprintf(buf,"G_%d_%d",x,y);
			actqueue.push_back(GRAB);
			ai::Agent::Action *action=new ai::Agent::WumpusAction;
			action->SetCode(ai::Agent::WumpusAction::GRAB);
			return true;
		}
		if(percept->GetAtom("GLITTER").GetName() =="")  {std::sprintf(buf,"!G_%d_%d",x,y);}
		if(percept->GetAtom("ARROW").GetName() =="1") {this->arrow=true;}
		if(percept->GetAtom("ARROW").GetName() =="0") {this->arrow=false;}
		if(percept->GetAtom("GOLD").GetName() =="1") {this->golden=true;}
		if(percept->GetAtom("BREEZE").GetName() !="") 
		{
			std::sprintf(buf,"B_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("BREEZE").GetName() =="")  
		{
			std::sprintf(buf,"!B_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("STENCH").GetName() !="") 
		{
			std::sprintf(buf,"S_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("STENCH").GetName() =="") 
		{
			std::sprintf(buf,"!S_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("WUMPUS").GetName() !="") 
		{
			std::sprintf(buf,"W_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("WUMPUS").GetName() =="") 
		{
			std::sprintf(buf,"!W_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("PIT").GetName() !="") 
		{
			std::sprintf(buf,"P_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("PIT").GetName() =="") 
		{
			std::sprintf(buf,"!P_%d_%d",x,y);
			eeb.AddSentence(buf);
			std::cout<<"Percepts added: "<<buf<<std::endl;
		}
		if(percept->GetAtom("SCREAM").GetName() !="") {this->wumpus=false;}
		if(percept->GetAtom("BUMP").GetName() !="") {std::sprintf(buf,"M_%d_%d",x,y);}
		else {std::sprintf(buf,"N_%d_%d",x,y);}
		eeb.AddSentence(buf);
		std::cout<<"Percepts added: "<<buf<<std::endl;

		return true;
	}
	bool Birgitte::goalsearch()
	{
		//asking
		if(x==1 && y==1){homely++;}
		if(homely>10)
		{
			actqueue.push_back(QUIT);
			ai::Agent::Action *action=new ai::Agent::WumpusAction;
			action->SetCode(ai::Agent::WumpusAction::QUIT);
			return true;
		}
		if(this->golden)
		{
			actqueue.push_back(QUIT);
			ai::Agent::Action *action=new ai::Agent::WumpusAction;
			action->SetCode(ai::Agent::WumpusAction::QUIT);
			return true;
		}
		if(this->AskStench() && this->x==this->minx && this->y==this->miny && this->arrow)
		{
			actqueue.push_back(SHOOT);
			this->arrow=false;
			return true;
		}
		if(this->AskBreeze() && this->x==this->minx && this->y==this->miny) 
		{
			actqueue.push_back(QUIT);
			return true;
		}
		
		if(AskNotWumpusSouth() && AskNotWumpusEast() && AskNotWumpusWest() && this->dir==NORTH && this->AskStench() && this->arrow)
		{
			actqueue.push_back(SHOOT);
			this->arrow=false;
			return true;
		}
		if(AskNotWumpusNorth() && AskNotWumpusEast() && AskNotWumpusWest() && this->dir==SOUTH && this->AskStench() && this->arrow)
		{
			actqueue.push_back(SHOOT);
			this->arrow=false;
			return true;
		}
		if(AskNotWumpusNorth() && AskNotWumpusSouth() && AskNotWumpusWest() && this->dir==EAST && this->AskStench() && this->arrow)
		{
			actqueue.push_back(SHOOT);
			this->arrow=false;
			return true;
		}
		if(AskNotWumpusNorth() && AskNotWumpusSouth() && AskNotWumpusEast() && this->dir==WEST && this->AskStench() && this->arrow)
		{
			actqueue.push_back(SHOOT);
			this->arrow=false;
			return true;
		}
		/*
		if(AskShoot() && this->arrow)
		{
			actqueue.push_back(SHOOT);
			this->arrow=false;
			return true;
		}*/
		
		//regular
		if(this->AskNextVisited() && this->turncount>4)
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		else if(!this->AskNextVisited())
		{
			if(this->wumpus && this->AskNotNextPit() && this->AskNotNextWumpus())
			{
				actqueue.push_back(FORWARD);
				return true;
			}
			else if(!this->wumpus && this->AskNotNextPit())
			{
				actqueue.push_back(FORWARD);
				return true;
			}
			else
			{
				actqueue.push_back(TURN_RIGHT);
				return true;
			}
		}
		else
		{
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		return true;
		
		/*
		if(this->AskNextWall())
		{
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		else if(this->wumpus)
		{

			if(!this->AskNextPit() && !this->AskNextWumpus() && !this->AskNextVisited())
			{
				actqueue.push_back(FORWARD);
				return true;
			}
			else if(!this->AskNextPit() && !this->AskNextWumpus() && this->AskNextVisited() && turncount<=4)
			{
				actqueue.push_back(TURN_RIGHT);
				return true;
			}
			else if(!this->AskNextPit() && !this->AskNextWumpus() && this->AskNextVisited() && turncount>4)
			{
				actqueue.push_back(FORWARD);
				return true;
			}
		}
		else if(!this->wumpus)
		{
			if(!this->AskNextPit() && !this->AskNextVisited())
			{
				actqueue.push_back(FORWARD);
				return true;
			}
			if(!this->AskNextPit() && this->AskNextVisited() && turncount<=4)
			{
				actqueue.push_back(TURN_RIGHT);
				return true;
			}
			else if(!this->AskNextPit() && this->AskNextVisited() && turncount>4)
			{
				actqueue.push_back(FORWARD);
				return true;
			}
		}
		else
		{
			actqueue.push_back(QUIT);
			return true;
		}
		return true;*/
		/*
		if(this->AskNextWumpus() && this->wumpus)
		{
			std::cout<<"this->AskNextWumpus(): "<<this->AskNextWumpus()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(this->AskNextWall())
		{
			std::cout<<"this->AskNextWall(): "<<this->AskNextWall()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(!this->AskNextVisited() && turncount<4)
		{
			std::cout<<"!this->AskNextVisited(): "<<!this->AskNextVisited()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(this->AskNextVisited() && turncount>4)
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		else
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		return true;*/
		
		
		
		//regulars
		/*
		if(this->AskNextPit())
		{
			std::cout<<"this->AskNextPit(): "<<this->AskNextPit()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(this->AskNextWumpus() && this->wumpus)
		{
			std::cout<<"this->AskNextWumpus(): "<<this->AskNextWumpus()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(this->AskNextWall())
		{
			std::cout<<"this->AskNextWall(): "<<this->AskNextWall()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(!this->AskNextVisited() && turncount<4)
		{
			std::cout<<"!this->AskNextVisited(): "<<!this->AskNextVisited()<<std::endl;
			actqueue.push_back(TURN_RIGHT);
			return true;
		}
		if(this->AskNextVisited() && turncount>4)
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		else
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		return true;*/
		/*
		if((this->AskNextSafe()) && (!this->AskNextWall()) && (!this->AskNextVisited())) 
		{
			std::cout<<"this->AskNextSafe(): "<<this->AskNextSafe()<<std::endl;
			std::cout<<"!this->AskNextWall(): "<<!this->AskNextWall()<<std::endl;
			std::cout<<"!this->AskNextVisited(): "<<!this->AskNextVisited()<<std::endl;
			actqueue.push_back(FORWARD);
			return true;
		}
		if((!this->AskNextSafe()) || (this->AskNextWall()) || (this->AskNextVisited())) 
		{
			if(turncount<4)
			{
				actqueue.push_back(TURN_RIGHT);
				return true;
			}
		}
		if((this->AskNextSafe()) && (!this->AskNextWall()) && (this->AskNextVisited()) && (turncount>4)) 
		{
			actqueue.push_back(FORWARD);
			return true;
		}
		else
		{
			actqueue.push_back(QUIT);
			std::cout<<"end"<<std::endl;
		}
		return true;*/
	}
	bool Birgitte::AskStench()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(S_%d_%d)", this->x, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskStench: "<<rval <<std::endl;
			return rval; 
		}
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!S_%d_%d)", this->x, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskStench: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskBreeze()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(B_%d_%d)", this->x, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskBreeze: "<<rval <<std::endl;
			return rval; 
		}
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!B_%d_%d)", this->x, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskBreeze: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNothing()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(N_%d_%d)", this->x, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskNothing: "<<rval <<std::endl;
			return rval; 
		}
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!N_%d_%d)", this->x, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskNothing: "<<rval <<std::endl;
			return rval; 
		}
	}
	
	//north
	bool Birgitte::AskPitNorth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(P_%d_%d)", this->x, this->y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitNorth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotPitNorth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!P_%d_%d)", this->x, this->y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitNorth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskWumpusNorth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(W_%d_%d)", this->x, this->y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusNorth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotWumpusNorth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!W_%d_%d)", this->x, this->y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusNorth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskVisitedNorth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(V_%d_%d)", this->x, this->y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedNorth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotVisitedNorth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!V_%d_%d)", this->x, this->y+1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedNorth: "<<rval <<std::endl;
			return rval; 
		}
	}
	//south
	bool Birgitte::AskPitSouth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(P_%d_%d)", this->x, this->y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitSouth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotPitSouth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!P_%d_%d)", this->x, this->y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitSouth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskWumpusSouth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(W_%d_%d)", this->x, this->y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusSouth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotWumpusSouth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!W_%d_%d)", this->x, this->y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusSouth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskVisitedSouth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(V_%d_%d)", this->x, this->y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedSouth: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotVisitedSouth()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!V_%d_%d)", this->x, this->y-1);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedSouth: "<<rval <<std::endl;
			return rval; 
		}
	}
	//east
	bool Birgitte::AskPitEast()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(P_%d_%d)", this->x+1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitEast: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotPitEast()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!P_%d_%d)", this->x+1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskNotPitEast: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskWumpusEast()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(W_%d_%d)", this->x+1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusEast: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotWumpusEast()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!W_%d_%d)", this->x+1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusEast: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskVisitedEast()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(V_%d_%d)", this->x+1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedEast: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotVisitedEast()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!V_%d_%d)", this->x+1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedEast: "<<rval <<std::endl;
			return rval; 
		}
	}
	//west
	bool Birgitte::AskPitWest()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(P_%d_%d)", this->x-1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitWest: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotPitWest()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!P_%d_%d)", this->x-1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskPitWest: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskWumpusWest()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(W_%d_%d)", this->x-1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusWest: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotWumpusWest()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!W_%d_%d)", this->x-1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskWumpusWest: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskVisitedWest()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(V_%d_%d)", this->x-1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedWest: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNotVisitedWest()
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!V_%d_%d)", this->x-1, this->y);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			std::cout<<"AskVisitedWest: "<<rval <<std::endl;
			return rval; 
		}
	}
	bool Birgitte::AskNextPit()
	{
		if(this->dir==NORTH) 
		{
			if(AskPitNorth()){return true;}
			return false;
		}
		else if(this->dir==SOUTH)
		{
			if(AskPitSouth()){return true;}
			return false;
		}
		else if(this->dir==EAST)
		{
			if(AskPitEast()){return true;}
			return false;
		}
		else if(this->dir==WEST)
		{
			if(AskPitWest()){return true;}
			return false;
		}
		std::cout<<"Error: Shouldn't be reached "<<std::endl;
		return false;
	}
	bool Birgitte::AskNotNextPit()
	{
		if(this->dir==NORTH) 
		{
			if(AskNotPitNorth()){return true;}
			return false;
		}
		else if(this->dir==SOUTH)
		{
			if(AskNotPitSouth()){return true;}
			return false;
		}
		else if(this->dir==EAST)
		{
			if(AskNotPitEast()){return true;}
			return false;
		}
		else if(this->dir==WEST)
		{
			if(AskNotPitWest()){return true;}
			return false;
		}
		std::cout<<"Error: Shouldn't be reached "<<std::endl;
		return false;
	}
	bool Birgitte::AskNextWumpus()
	{
		if(this->dir==NORTH) 
		{
			if(AskWumpusNorth()){return true;}
			return false;
		}
		else if(this->dir==SOUTH)
		{
			if(AskWumpusSouth()){return true;}
			return false;
		}
		else if(this->dir==EAST)
		{
			if(AskWumpusEast()){return true;}
			return false;
		}
		else if(this->dir==WEST)
		{
			if(AskWumpusWest()){return true;}
			return false;
		}
		std::cout<<"Error: Shouldn't be reached "<<std::endl;
		return false;
	}
	bool Birgitte::AskNotNextWumpus()
	{
		if(this->dir==NORTH) 
		{
			if(AskNotWumpusNorth()){return true;}
			return false;
		}
		else if(this->dir==SOUTH)
		{
			if(AskNotWumpusSouth()){return true;}
			return false;
		}
		else if(this->dir==EAST)
		{
			if(AskNotWumpusEast()){return true;}
			return false;
		}
		else if(this->dir==WEST)
		{
			if(AskNotWumpusWest()){return true;}
			return false;
		}
		std::cout<<"Error: Shouldn't be reached "<<std::endl;
		return false;
	}
	bool Birgitte::AskNextSafe()
	{
		if(this->wumpus)
		{
			//std::cout<<"living wumpus"<<std::endl;
			if(this->dir==NORTH) 
			{
				std::cout<<"!AskPitNorth(): "<<!AskPitNorth()<<std::endl;
				std::cout<<"!AskWumpusNorth(): "<<!AskWumpusNorth()<<std::endl;
				std::cout<<"AskVisitedNorth(): "<<  AskVisitedNorth()<<std::endl;
				if(((!AskPitNorth()) && (!AskWumpusNorth())) || AskVisitedNorth()){return true;}
				return false;
			}
			else if(this->dir==SOUTH)
			{
				std::cout<<"!AskPitSouth(): "<<!AskPitSouth()<<std::endl;
				std::cout<<"!AskWumpusSouth(): "<<!AskWumpusSouth()<<std::endl;
				std::cout<<"AskVisitedSouth(): "<<  AskVisitedSouth()<<std::endl;
				if(((!AskPitSouth()) && (!AskWumpusSouth())) || (AskVisitedSouth())){return true;}
				return false;
			}
			else if(this->dir==EAST)
			{
				std::cout<<"!AskPitEast(): "<<!AskPitEast()<<std::endl;
				std::cout<<"!AskWumpusEast(): "<<!AskWumpusEast()<<std::endl;
				std::cout<<"AskVisitedEast(): "<<  AskVisitedEast()<<std::endl;
				if(((!AskPitEast()) && (!AskWumpusEast())) || AskVisitedEast()){return true;}
				return false;
			}
			else if(this->dir==WEST)
			{
				std::cout<<"!AskPitWest(): "<<!AskPitWest()<<std::endl;
				std::cout<<"!AskWumpusWest(): "<<!AskWumpusWest()<<std::endl;
				std::cout<<"AskVisitedWest(): "<<  AskVisitedWest()<<std::endl;
				if(((!AskPitWest()) && (!AskWumpusWest())) || AskVisitedWest()){return true;}
				return false;
			}
		}
		else
		{
			if(this->dir==NORTH) 
			{
				if((!AskPitNorth()) || (AskVisitedNorth())){return true;}
				return false;
			}
			else if(this->dir==SOUTH)
			{
				if((!AskPitSouth()) || (AskVisitedSouth())){return true;}
				return false;
			}
			else if(this->dir==EAST)
			{
				if((!AskPitEast()) || (AskVisitedEast())){return true;}
				return false;
			}
			else if(this->dir==WEST)
			{
				if((!AskPitWest()) || (AskVisitedWest())){return true;}
				return false;
			}
		}
		std::cout<<"Error: Shouldn't be reached "<<std::endl;
		return false;
	}
	bool Birgitte::AskNextVisited()
	{
		{
			if(this->dir==NORTH) 
			{
				if(AskVisitedNorth()){return true;}
				return false;
			}
			else if(this->dir==SOUTH)
			{
				if(AskVisitedSouth()){return true;}
				return false;
			}
			else if(this->dir==EAST)
			{
				if(AskVisitedEast()){return true;}
				return false;
			}
			else if(this->dir==WEST)
			{
				if(AskVisitedWest()){return true;}
				return false;	
			}
		}
		std::cout<<"Error: Shouldn't be reached "<<std::endl;
		return false;	
	}
	bool Birgitte::AskVisited(int a, int b)
	{
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(V_%d_%d)", a, b);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			return rval;
		}
		{
			bool rval;
			ai::PL::KnowledgeBase question;
			std::sprintf(buf, "(!V_%d_%d)", a, b);
			question.AddSentence(buf);
			rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
			return rval;
		}
	}
	bool Birgitte::AskNextWall()
	{
		if(this->dir==NORTH && y==this->maxy) {return true;}
		else if(this->dir==SOUTH && y==this->miny) {return true;}
		else if(this->dir==EAST && x==this->maxy) {return true;}
		else if(this->dir==WEST && x==this->miny) {return true;}
		else {return false;}
	}
	bool Birgitte::AskLocalNothing()
	{
		bool rval;
		ai::PL::KnowledgeBase question;
		std::sprintf(buf, "(N_%d_%d)", this->x, this->y);
		question.AddSentence(buf);
		rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
		return rval;
	}
	bool Birgitte::AskAllNothing()
	{
		int a,b;
		for(a=this->minx;a<=this->maxx;a++)
		{
			for(b=this->miny;b<this->maxy;b++)
			{
				bool rval;
				ai::PL::KnowledgeBase question;
				std::sprintf(buf, "(N_%d_%d)", a, b);
				question.AddSentence(buf);
				rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
				if(rval) {return rval;}
			}
		}
		return false;
	}
	bool Birgitte::AskShoot()
	{
		if(this->dir == NORTH)
		{
			int n;
			for(n=this->y;n<this->maxy;n++)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot NORTH: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot NORTH: "<<rval <<std::endl;
					return rval; 
				}
			}
			return false;
		}
		else if(this->dir == SOUTH) 
		{

			int n;
			for(n=this->y;n>this->miny;n--)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot SOUTH: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot SOUTH: "<<rval <<std::endl;
					return rval; 
				}
			}
			return false;
		}
		else if(this->dir == EAST)
		{
			int m;
			for(m=this->x;m<this->maxx;m++)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot EAST: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot EAST: "<<rval <<std::endl;
					return rval;
				}
			}
			return false;
		}
		else if(this->dir == WEST)
		{

			int m;
			for(m=this->x;m>this->minx;m--)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot WEST: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot WEST: "<<rval <<std::endl;
					return rval;
				}
			}
			return false;
		}
		return false;
	}
	
	bool Birgitte::AskNotShoot()
	{
		if(this->dir == NORTH)
		{
			int n;
			for(n=this->y;n<this->maxy;n++)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot NORTH: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot NORTH: "<<rval <<std::endl;
					return rval; 
				}
			}
			return false;
		}
		else if(this->dir == SOUTH) 
		{

			int n;
			for(n=this->y;n>this->miny;n--)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot SOUTH: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", this->x, n);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot SOUTH: "<<rval <<std::endl;
					return rval; 
				}
			}
			return false;
		}
		else if(this->dir == EAST)
		{
			int m;
			for(m=this->x;m<this->maxx;m++)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot EAST: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot EAST: "<<rval <<std::endl;
					return rval;
				}
			}
			return false;
		}
		else if(this->dir == WEST)
		{

			int m;
			for(m=this->x;m>this->minx;m--)
			{
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot WEST: "<<rval <<std::endl;
					return rval; 
				}
				{
					bool rval;
					ai::PL::KnowledgeBase question;
					std::sprintf(buf, "(!W_%d_%d)", m, this->y);
					question.AddSentence(buf);
					rval = (eeb.DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
					std::cout<<"AskShoot WEST: "<<rval <<std::endl;
					return rval;
				}
			}
			return false;
		}
		return false;
	}
}




