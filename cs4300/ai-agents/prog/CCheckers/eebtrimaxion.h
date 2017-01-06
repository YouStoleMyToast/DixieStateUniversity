#ifndef _EBBTRIMAXION_H_
#define _EBBTRIMAXION_H_

#include <ai_ccheckers.h>

namespace eebx
{
	enum{TT_SCORE_ME=1,TT_SCORE_OTHER=2,TT_SCORE_DIFF=3,TT_H_1,TT_H_2,TT_H_3,TT_H_COMBO_3,TT_k13};
	
	class PlyData
	{
	public:
		PlyData(double utility_in);
		bool move_ok;
		ai::CCheckers::MoveData move;
		double utility;
	};

	class Trimaxion : public ai::Agent::AgentProgram
	{
	public:
		Trimaxion(ai::Agent::Options *opts);
		~Trimaxion();
		virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
		
	protected:
		PlyData PickMove(const ai::CCheckers::BasicBoard &board, int player);
		PlyData Max(const ai::CCheckers::BasicBoard &board, int player, int depth, double alpha, double beta);
		PlyData Min(const ai::CCheckers::BasicBoard &board, int player, int depth, double alpha, double beta);
		int Forwardness(const ai::CCheckers::BasicBoard &board, int player);
		
	private:
		double k13(const ai::CCheckers::BasicBoard &board, int player);
		int max_depth;
		int evaluation_method;
	};
};
#endif /* _EBBTRIMAXION_H_ */
