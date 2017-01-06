#ifndef _EBBHYMIE_H_
#define _EBBHYMIE_H_

#include <ai_ccheckers.h>

namespace eebh
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

	class Hymie : public ai::Agent::AgentProgram
	{
	public:
		Hymie(ai::Agent::Options *opts);
		~Hymie();
		virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
		
	protected:
		PlyData PickMove(const ai::CCheckers::BasicBoard &board, int player);
		PlyData Max(const ai::CCheckers::BasicBoard &board, int player, int depth, double alpha, double beta);
		PlyData Min(const ai::CCheckers::BasicBoard &board, int player, int depth, double alpha, double beta);
		double Evaluate(const ai::CCheckers::BasicBoard &board, int player);
		int Forwardness(const ai::CCheckers::BasicBoard &board, int player);
		
	private:
		double EvaluateScoreMe(const ai::CCheckers::BasicBoard &board, int player);
		double EvaluateScoreOther(const ai::CCheckers::BasicBoard &board, int player);
		double EvaluateScoreDiff(const ai::CCheckers::BasicBoard &board, int player);
		double hCloseToWinningMe(const ai::CCheckers::BasicBoard &board, int player);
		double hCloseToWinningOther(const ai::CCheckers::BasicBoard &board, int player);
		double k13(const ai::CCheckers::BasicBoard &board, int player);
		int max_depth;
		int evaluation_method;
	};
};
#endif /* _EBBHYMIE_H_ */
