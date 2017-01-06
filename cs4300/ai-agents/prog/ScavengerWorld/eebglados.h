#ifndef _EEBGLADOS_H_
#define _EEBGLADOS_H_
#include <ai_scavenger.h>
#include <vector>
#include "eebmodel.h"
#include "eebaction.h"
#include <list>
#include <iostream>
#include <string>

namespace eeb
{
	enum {ALG_MIN,ALG_TREE,ALG_GRAPH,ALG_MAX};
	enum {FRINGE_MIN,FRINGE_BFS,FRINGE_UCS,FRINGE_DFS,FRINGE_DLS,FRINGE_IDS,FRINGE_MAX};
	
	struct Object
	{
		std::string object;
		std::string color;
		std::string shape;
		std::string size1;
		std::string size2;
		int points;
	};
	
	class Glados : public ai::Agent::AgentProgram
	{
	public:
		Glados(ai::Agent::Options *opts);
		~Glados();
		virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
		bool gethomebound();
		bool sethomebound(bool bound);

	protected:
		bool parsepercepts(const ai::Agent::Percept *percept);
		bool exploreparse(const ai::Agent::Percept *percept);
		bool goalsearch();
		bool exploresearch();
		bool lookarround();
		bool probably(const char* object);
		
		bool addgoalpoint(Point);
		
		
		double homecheck();
		double goalcheck(int x, int y);
		
		Model *model;
		
		int algtype;
		int fringetype;
		int maxdepth;
		
		//original code
		std::list<Action> actqueue;
		std::list<int> goalkeylist;
		
		//new code
		std::vector<char *> todepositvec;
		std::vector<char *> topickupvec;
		std::vector<char *> toexaminevec;
		
		std::vector<Object> objectvec;
		//std::vector<int> natvec;
		//std::vector<int> mimvec;
		//std::vector<int> junkvec;
	};
};
#endif /* _EEBGLADOS_H_ */
