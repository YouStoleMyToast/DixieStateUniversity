#ifndef _EEBCYRUS_H_
#define _EEBCYRUS5_H_

#include <ai_ccheckers.h>

namespace eebc
{
	enum{TT_SCORE_ME=1,TT_SCORE_OTHER=2,TT_SCORE_DIFF=3,TT_H_1,TT_H_2,TT_H_3,TT_H_4,TT_H_5,TT_H_6,TT_H_COMBO_1,TT_H_COMBO_2,TT_H_COMBO_3,};
	
	class PlyData
	{
	public:
		PlyData(double utility_in);
		bool move_ok;
		ai::CCheckers::MoveData move;
		double utility;
	};

	class Cyrus : public ai::Agent::AgentProgram
	{
	public:
		Cyrus(ai::Agent::Options *opts);
		~Cyrus();
		virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
		
	protected:
		PlyData PickMove(const ai::CCheckers::BasicBoard &board, int player);
		PlyData Max(const ai::CCheckers::BasicBoard &board, int player, int depth);
		PlyData Min(const ai::CCheckers::BasicBoard &board, int player, int depth);
		double Evaluate(const ai::CCheckers::BasicBoard &board, int player);
		
	private:
		int max_depth;
		
	};
    
};
#endif /* _EEBJOHNNY5_H_ */
