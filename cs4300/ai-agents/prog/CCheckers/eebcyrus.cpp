#include "eebcyrus.h"
#include <cstdio>


namespace eebc
{
	
	const double MY_INFINITY = 1.e10;
	
	PlyData::PlyData(double utility_in)
		: move_ok(false), utility(utility_in)
	{/*empty*/}
    
	Cyrus::Cyrus(ai::Agent::Options *opts)
		: max_depth(3)
	{
		if(opts->GetArgInt("user1")>0){this->max_depth = opts->GetArgInt("user1");}
		{
			char buf[128];
			std::sprintf(buf,"Cyrus (ABR-%d)",this->max_depth);
			SetName(buf);
		}
		std::cout<<"Options:"<<std::endl;
		std::cout<<"-U num : maximum search depth (in ply)."<<std::endl;
	}
		
	Cyrus::~Cyrus(){/*empty*/}
	


	ai::Agent::Action * Cyrus::Program(const ai::Agent::Percept * percept)
	{
		ai::CCheckers::CCheckersAction *action = new ai::CCheckers::CCheckersAction;
		std::string board_str = percept->GetAtom("BASIC_BOARD").GetValue();
		ai::CCheckers::BasicBoard board(board_str);
		int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());
		//Pause();
		PlyData ply_data=this->PickMove(board, player);
		if(ply_data.move_ok)
		{
			action->SetCode(ai::CCheckers::CCheckersAction::MOVE);
			action->SetMove(ply_data.move);
		}
		else /* no legal move, or bad choice */
		{
			action->SetCode(ai::CCheckers::CCheckersAction::QUIT);
		}
		return action;
	}

	PlyData Cyrus::PickMove(const ai::CCheckers::BasicBoard &board, int player)
	{
		PlyData ply_data=this->Max(board, player, 1);
		return ply_data;
	}

	PlyData Cyrus::Max(const ai::CCheckers::BasicBoard &board, int player, int depth)
	{
		PlyData ply_data(-1.e6);
		if(board.HaveWinner() || depth>this->max_depth)
		{
			ply_data.utility=this->Evaluate(board, player);
			return ply_data;
		}
		ai::CCheckers::BasicBoard my_board(board);
		const std::vector<ai::CCheckers::MoveData> & moves=my_board.DetermineLegalMoves(player);
		int i;
		for(i=0; i<(int)moves.size(); i++)
		{
			ai::CCheckers::BasicBoard tmp_board(board);
			tmp_board.Move(player, moves[i]);
			PlyData tmp_ply_data=this->Min(tmp_board, player, depth + 1);
			if((tmp_ply_data.utility>ply_data.utility) || ((tmp_ply_data.utility == ply_data.utility) && (std::rand() % 2)))
			{
				ply_data.utility=tmp_ply_data.utility;
				ply_data.move=moves[i];
				ply_data.move_ok=true;
			}
		}
		return ply_data;
	}

	PlyData Cyrus::Min(const ai::CCheckers::BasicBoard &board, int player, int depth)
	{
		PlyData ply_data(1.e6);
		if(board.HaveWinner() || depth>this->max_depth)
		{
			ply_data.utility=this->Evaluate(board, player);
			return ply_data;
		}

		int other_player=(player==1)? 2:1;
		ai::CCheckers::BasicBoard my_board(board);
		const std::vector<ai::CCheckers::MoveData> & moves = my_board.DetermineLegalMoves(other_player);
		int i;
		for(i=0; i<(int)moves.size(); i++)
		{
			ai::CCheckers::BasicBoard tmp_board(board);
			tmp_board.Move(other_player, moves[i]);
			PlyData tmp_ply_data=this->Max(tmp_board, player, depth + 1);
			if((tmp_ply_data.utility<ply_data.utility) || ((tmp_ply_data.utility==ply_data.utility) && (std::rand()%2)))
			{
				ply_data.utility=tmp_ply_data.utility;
				ply_data.move=moves[i];
				ply_data.move_ok=true;
			}
		}

		return ply_data;
	}
	
	double Cyrus::Evaluate(const ai::CCheckers::BasicBoard &board, int player)
	{
		return board.Forwardness(player);
	}
}
