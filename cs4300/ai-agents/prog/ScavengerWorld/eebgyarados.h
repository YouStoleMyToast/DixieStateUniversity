#ifndef _EEBGYARADOS_H_
#define _EEBGYARADOS_H_
#include <ai_scavenger.h>
#include "eebymodel.h"
#include "eebyaction.h"
#include <list>

namespace eeby
{
	enum {ALG_MIN,ALG_TREE,ALG_GRAPH,ALG_MAX};
	enum {FRINGE_MIN,FRINGE_BFS,FRINGE_UCS,FRINGE_DFS,FRINGE_DLS,FRINGE_IDS,FRINGE_MAX};
	class Gyarados : public ai::Agent::AgentProgram
	{
	public:
		Gyarados(ai::Agent::Options *opts);
		~Gyarados();
		virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
		bool gethomebound();
		bool sethomebound(bool bound);

	protected:
		bool parsepercepts(const ai::Agent::Percept *percept);
		bool exploreparse(const ai::Agent::Percept *percept);
		bool goalsearch();
		bool exploresearch();
		bool lookarround();
		double homecheck();
		double goalcheck(int x, int y);
		
		Model *model;
		
		int algtype;
		int fringetype;
		int maxdepth;
		std::list<Action>actqueue;
		std::list<int>goalkeylist;
		std::list<char>objectlist;
	};
};
#endif /* _EEBGYARADOS_H_ */
