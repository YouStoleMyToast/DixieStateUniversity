#ifndef _BIRGITTE_H_
#define _BIRGITTE_H_

//#include "eebaction.h"
//#include "eebmodel.h"
#include <ai_wumpus.h>
#include <ai_pl.h>
#include <list>


namespace eebb
{
	enum Moves { NORTH=0, SOUTH=1, EAST=2, WEST=3, FORWARD=4,TURN_RIGHT=5,TURN_LEFT=6,GRAB=7,SHOOT=8,QUIT=9,ERROR};
	
	class Birgitte : public ai::Agent::AgentProgram
	{
	public:
		Birgitte();
		~Birgitte();
		virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
		
	protected:
		bool rules();
		bool goalsearch();
		bool parsepercepts(const ai::Agent::Percept *percept);
		//questions
		bool AskBreeze();
		bool AskStench();
		
		bool AskPitNorth();
		bool AskNotPitNorth();
		bool AskWumpusNorth();
		bool AskNotWumpusNorth();
		bool AskVisitedNorth();
		bool AskNotVisitedNorth();
		
		bool AskPitSouth();
		bool AskNotPitSouth();
		bool AskWumpusSouth();
		bool AskNotWumpusSouth();
		bool AskVisitedSouth();
		bool AskNotVisitedSouth();
		
		bool AskPitEast();
		bool AskNotPitEast();
		bool AskWumpusEast();
		bool AskNotWumpusEast();
		bool AskVisitedEast();
		bool AskNotVisitedEast();
		
		bool AskPitWest();
		bool AskNotPitWest();
		bool AskWumpusWest();
		bool AskNotWumpusWest();
		bool AskVisitedWest();
		bool AskNotVisitedWest();
		
		bool AskNotNextPit();
		bool AskNotNextWumpus();
		
		bool AskVisited();
		bool AskNextSafe();
		bool AskNextPit();
		bool AskNextWumpus();
		bool AskNextWall();
		bool AskShoot();
		bool AskNotShoot();
		bool AskGlitter();
		bool ShotResults();
		bool AskVisited(int a,int b);
		bool AskNextVisited();
		bool AskNothing();
		bool AskLocalNothing();
		
		bool AskAllNothing();
		
		bool ChangeDirection(int goal);
		/* Things I know */
		ai::PL::KnowledgeBase eeb;
		/* my location */
		int minx;
		int maxx;
		int miny;
		int maxy;
		
		int x;
		int y;
		int dir;
		int turncount;
		int homely;
		bool arrow;
		bool golden;
		bool wumpus;
		
		std::list<Moves>actqueue;
	private:
	};
}

#endif /* _BIRGITTE_H_ */
