#include "eebhymie.h"
#include <cstdio>
#include <iostream>
#include <math.h>

namespace eebh
{
	bool maxdash=false;
	const double MY_INFINITY=1.e10;
	
	PlyData::PlyData(double utility_in)
		: move_ok(false), utility(utility_in)
	{/*empty*/}
    
	Hymie::Hymie(ai::Agent::Options *opts)
		: max_depth(3), evaluation_method(TT_k13)
	{
		if(opts->GetArgInt("user1")>0){this->max_depth=opts->GetArgInt("user1");}
		{
			char buf[128];
			std::sprintf(buf,"Hymie (%d)",this->max_depth);
			SetName(buf);
		}
		std::cout<<"Options:"<<std::endl;
		std::cout<<"-U num : maximum search depth (in ply)."<<std::endl;
	}
	
	Hymie::~Hymie(){/*empty*/}
	
	ai::Agent::Action * Hymie::Program(const ai::Agent::Percept * percept)
	{
		ai::CCheckers::CCheckersAction *action=new ai::CCheckers::CCheckersAction;
		std::string board_str=percept->GetAtom("BASIC_BOARD").GetValue();
		ai::CCheckers::BasicBoard board(board_str);
		int player=atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());
		PlyData ply_data=this->PickMove(board, player);
		if(ply_data.move_ok)
		{
			action->SetCode(ai::CCheckers::CCheckersAction::MOVE);
			action->SetMove(ply_data.move);
		}
		else {action->SetCode(ai::CCheckers::CCheckersAction::QUIT);}/*no legal move, or bad choice*/
		return action;
	}
	PlyData Hymie::PickMove(const ai::CCheckers::BasicBoard &board, int player)
	{
		PlyData ply_data=this->Max(board,player,1,-MY_INFINITY,MY_INFINITY);
		return ply_data;
	}
	PlyData Hymie::Max(const ai::CCheckers::BasicBoard &board,int player,int depth,double alpha,double beta)
	{
		PlyData ply_data(-MY_INFINITY);
		if(board.HaveWinner() || depth>this->max_depth)
		{
			ply_data.utility=this->Evaluate(board, player);
			return ply_data;
		}
		ai::CCheckers::BasicBoard my_board(board);
		const std::vector<ai::CCheckers::MoveData> & moves=my_board.DetermineLegalMoves(player);
		std::vector<PlyData> best_plys;
		int i;
		if(player==1)
		{
			for(i = 0; i < (int)moves.size(); i++)
			{
				if(moves[i].from_y <= moves[i].to_y)
				{
					ai::CCheckers::BasicBoard tmp_board(board);
					tmp_board.Move(player,moves[i]);
					PlyData tmp_ply_data=this->Min(tmp_board,player,depth+1,alpha,beta);
					if(tmp_ply_data.utility>ply_data.utility)
					{
						ply_data.utility=tmp_ply_data.utility;
						ply_data.move=moves[i];
						ply_data.move_ok=true;
						best_plys.clear();
						best_plys.push_back(ply_data);
						if(ply_data.utility>beta){break;}/* parent node has a better child, so this node will not be chosen */
						if(ply_data.utility>alpha){alpha=ply_data.utility;}
					}
					else if(tmp_ply_data.utility==ply_data.utility)
					{
						PlyData t(-MY_INFINITY);
						t.utility=tmp_ply_data.utility;
						t.move=moves[i];
						t.move_ok=true;
						best_plys.push_back(t);
					}
				}
			}
		}
		else if(player==2)
		{
			for(i = 0; i < (int)moves.size(); i++)
			{
				if(moves[i].from_y >= moves[i].to_y)
				{
					ai::CCheckers::BasicBoard tmp_board(board);
					tmp_board.Move(player,moves[i]);
					PlyData tmp_ply_data=this->Min(tmp_board,player,depth+1,alpha,beta);
					if(tmp_ply_data.utility>ply_data.utility)
					{
						ply_data.utility=tmp_ply_data.utility;
						ply_data.move=moves[i];
						ply_data.move_ok=true;
						best_plys.clear();
						best_plys.push_back(ply_data);
						if(ply_data.utility>beta){break;}
						if(ply_data.utility>alpha){alpha=ply_data.utility;}
					}
					else if(tmp_ply_data.utility==ply_data.utility)
					{
						PlyData t(-MY_INFINITY);
						t.utility=tmp_ply_data.utility;
						t.move=moves[i];
						t.move_ok=true;
						best_plys.push_back(t);
					}
				}
			}
		}
		return best_plys[rand() % best_plys.size()];
	}
	PlyData Hymie::Min(const ai::CCheckers::BasicBoard &board,int player,int depth,double alpha,double beta)
	{
		PlyData ply_data(MY_INFINITY);
		if(board.HaveWinner() || depth>this->max_depth)
		{
			ply_data.utility=this->Evaluate(board, player);
			return ply_data;
		}
		int other_player=(player==1)? 2:1;
		ai::CCheckers::BasicBoard my_board(board);
		const std::vector<ai::CCheckers::MoveData> & moves=my_board.DetermineLegalMoves(other_player);
		std::vector<PlyData> best_plys;
		int i;
		if(maxdash) {return best_plys[0];}
		if(other_player==1)
		{
			for(i=0;i<(int)moves.size();i++)
			{
				if(moves[i].from_y <= moves[i].to_y)
				{
					ai::CCheckers::BasicBoard tmp_board(board);
					tmp_board.Move(other_player,moves[i]);
					PlyData tmp_ply_data=this->Max(tmp_board,player,depth+1,alpha,beta);
					if(tmp_ply_data.utility<ply_data.utility)
					{
						ply_data.utility=tmp_ply_data.utility;
						ply_data.move=moves[i];
						ply_data.move_ok=true;
						best_plys.clear();
						best_plys.push_back(ply_data);
						if(ply_data.utility<alpha){break;}
						if(ply_data.utility<beta){beta=ply_data.utility;}
					}
					else if(tmp_ply_data.utility==ply_data.utility)
					{
						PlyData t(MY_INFINITY);
						t.utility=tmp_ply_data.utility;
						t.move=moves[i];
						t.move_ok=true;
						best_plys.push_back(t);
					}
				}
			}
		}
		else if(other_player==2)
		{
			for(i=0;i<(int)moves.size();i++)
			{
				if(moves[i].from_y >= moves[i].to_y)
				{
					ai::CCheckers::BasicBoard tmp_board(board);
					tmp_board.Move(other_player,moves[i]);
					PlyData tmp_ply_data=this->Max(tmp_board,player,depth+1,alpha,beta);
					if(tmp_ply_data.utility<ply_data.utility)
					{
						ply_data.utility=tmp_ply_data.utility;
						ply_data.move=moves[i];
						ply_data.move_ok=true;
						best_plys.clear();
						best_plys.push_back(ply_data);
						if(ply_data.utility<alpha){break;}
						if(ply_data.utility<beta){beta=ply_data.utility;}
					}
					else if(tmp_ply_data.utility==ply_data.utility)
					{
						PlyData t(MY_INFINITY);
						t.utility=tmp_ply_data.utility;
						t.move=moves[i];
						t.move_ok=true;
						best_plys.push_back(t);
					}
				}
			}
		}
		return best_plys[rand() % best_plys.size()];
	}
	double Hymie::Evaluate(const ai::CCheckers::BasicBoard &board, int player)
	{
		double v = 0.0;
		switch(this->evaluation_method)
		{
		case TT_SCORE_ME:
			v=this->EvaluateScoreMe(board,player);
			break;
		case TT_SCORE_OTHER:
			v=this->EvaluateScoreOther(board,player);
			break;
		case TT_SCORE_DIFF:
			/* fall through */
			default:
			v=this->EvaluateScoreDiff(board,player);
			break;
		case TT_H_1:
			v=this->EvaluateScoreDiff(board,player);
			break;
		case TT_H_2:
			v=this->hCloseToWinningMe(board,player);
			break;
		case TT_H_3:
			v=this->hCloseToWinningOther(board,player);
			break;
		case TT_H_COMBO_3:
			v=1*this->EvaluateScoreDiff(board,player)+-1*this->hCloseToWinningMe(board,player)+1*this->hCloseToWinningOther(board,player);
			break;
		case TT_k13:
			v=this->k13(board,player);
			break;
		}
		return v;
	}
	double Hymie::EvaluateScoreMe(const ai::CCheckers::BasicBoard &board, int player)
	{return board.Forwardness(player);}
	
	double Hymie::EvaluateScoreOther(const ai::CCheckers::BasicBoard &board, int player)
	{
		int other_player=(player==1)? 2:1;
		return board.Forwardness(other_player);
	}
	
	double Hymie::EvaluateScoreDiff(const ai::CCheckers::BasicBoard &board, int player)
	{
		int other_player=(player==1)? 2:1;
		return board.Forwardness(player)-board.Forwardness(other_player);
	}

	double Hymie::hCloseToWinningMe(const ai::CCheckers::BasicBoard &board, int player)
	{
		double d=25-board.Forwardness(player);
		if(d<0){d=0;}
		return d;
	}
	double Hymie::hCloseToWinningOther(const ai::CCheckers::BasicBoard &board, int player)
	{
		int other_player=(player==1)? 2:1;
		double d=25-board.Forwardness(other_player);
		if(d<0){d=0;}
		return d;
	}
	double Hymie::k13(const ai::CCheckers::BasicBoard &board, int player)
	{
		int x,y,d;
		int forwardmod, centermod, lagmod;
		forwardmod=10000;
		centermod=1000;
		lagmod=100;
		d=0;

		int other_player=(player==1)? 2:1;
		ai::CCheckers::BoardData newboard=board.GetBoard();
		
		int selffront=0;
		int selfback=0;
		int opfront=16;
		int opback=16;
		bool first=true;
		
		for(x=0; x<17; x++)
		{
			for(y=0; y<17; y++)
			{
				if(newboard.hole[x][y]==player || newboard.hole[x][y]==other_player)
				{
					if(newboard.hole[x][y]==player && first) {y=selfback;}
					if(newboard.hole[x][y]==player && y>selffront) {selffront=y;}
					if(newboard.hole[x][y]==other_player) {y=opback;}
					if(newboard.hole[x][y]==other_player && y<opfront) {opfront=y;}
				}
				first=false;
			}
		}
		if(selfback>opback){maxdash=true;}
		else {maxdash=false;}
		for(x=0; x<17; x++)
		{
			for(y=0; y<17; y++)
			{
				if(newboard.hole[x][y] == player)
				{
					if(player==1)
					{
						d=d+(board.Forwardness(player)*forwardmod)+(x*centermod)-(board.Forwardness(other_player)*forwardmod);
						if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
						d=d-((selffront-selfback)*lagmod*y);
					}
					else if(player==2)
					{
						d=d+(board.Forwardness(player)*forwardmod)+(x*centermod)-(board.Forwardness(other_player)*forwardmod);
						if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
					}
					return d;
				}
			}
		}
		return d;
	}
}

//did well
/*
						d=board.Forwardness(player)*forwardmod*y;
						
						or
						
						if(y==0) {d=d+(board.Forwardness(player)*forwardmod*0);}
						else if(y==1) {d=d+(board.Forwardness(player)*forwardmod*1);}
						else if(y==2) {d=d+(board.Forwardness(player)*forwardmod*2);}
						else if(y==3) {d=d+(board.Forwardness(player)*forwardmod*3);} 
						else if(y==4) {d=d+(board.Forwardness(player)*forwardmod*4);}
						else if(y==5) {d=d+(board.Forwardness(player)*forwardmod*5);}
						else if(y==6) {d=d+(board.Forwardness(player)*forwardmod*6);}
						else if(y==7) {d=d+(board.Forwardness(player)*forwardmod*7);}
						else if(y==8) {d=d+(board.Forwardness(player)*forwardmod*8);}
						else if(y==9) {d=d+(board.Forwardness(player)*forwardmod*9);}
						else if(y==10) {d=d+(board.Forwardness(player)*forwardmod*10);}
						else if(y==11) {d=d+(board.Forwardness(player)*forwardmod*11);}
						else if(y==12) {d=d+(board.Forwardness(player)*forwardmod*12);}
						else if(y==13) {d=d+(board.Forwardness(player)*forwardmod*13);}
						else if(y==14) {d=d+(board.Forwardness(player)*forwardmod*14);}
						else if(y==15) {d=d+(board.Forwardness(player)*forwardmod*15);}
						else if(y==16) {d=d+(board.Forwardness(player)*forwardmod*16);}
						else if(y==17) {d=d+(board.Forwardness(player)*forwardmod*17);}
						*/

//did ok
/*
						if(y==0) {d=d+(board.Forwardness(player)*forwardmod*0);}
						else if(y==1) {d=d+(board.Forwardness(player)*forwardmod*1);}
						else if(y==2) {d=d+(board.Forwardness(player)*forwardmod*2);}
						else if(y==3) {d=d+(board.Forwardness(player)*forwardmod*3);} 
						else if(y==4 && x>3 && x<8) {d=d+(board.Forwardness(player)*forwardmod*4);}
						else if(y==5 && x>4 && x<8) {d=d+(board.Forwardness(player)*forwardmod*5);}
						else if(y==6 && x>5 && x<8) {d=d+(board.Forwardness(player)*forwardmod*6);}
						else if(y==7 && x>6 && x<8) {d=d+(board.Forwardness(player)*forwardmod*7);}
						else if(y==8 && x>7 && x<8) {d=d+(board.Forwardness(player)*forwardmod*8);}
						else if(y==9 && x>8 && x<8) {d=d+(board.Forwardness(player)*forwardmod*9);}
						else if(y==10 && x>8 && x<8) {d=d+(board.Forwardness(player)*forwardmod*10);}
						else if(y==11 && x>8 && x<8) {d=d+(board.Forwardness(player)*forwardmod*11);}
						else if(y==12 && x>8 && x<9) {d=d+(board.Forwardness(player)*forwardmod*12);}
						else if(y==13 && x>8 && x<10) {d=d+(board.Forwardness(player)*forwardmod*13);}
						else if(y==14 && x>8 && x<11) {d=d+(board.Forwardness(player)*forwardmod*14);}
						else if(y==15 && x>9 && x<12) {d=d+(board.Forwardness(player)*forwardmod*15);}
						else if(y==16 && x>10 && x<13) {d=d+(board.Forwardness(player)*forwardmod*16);}
						*/

						/*if(y==4 && x>3 && x<8) {d=d+(forwardmod*4);}
						else if(y==5 && x>4 && x<8) {d=d+(forwardmod*5);}
						else if(y==6 && x>5 && x<9) {d=d+(forwardmod*6);}
						else if(y==7 && x>6 && x<10) {d=d+(forwardmod*7);}
						else if(y==8 && x>7 && x<11) {d=d+(forwardmod*8);}
						else if(y==9 && x>8 && x<11) {d=d+(forwardmod*9);}
						else if(y==10 && x>8 && x<11) {d=d+(forwardmod*10);}
						else if(y==11 && x>8 && x<12) {d=d+(forwardmod*11);}
						else if(y==12 && x>8 && x<12) {d=d+(forwardmod*12);}
						else if(y==13 && x>8 && x<12) {d=d+(forwardmod*13);}
						else if(y==14 && x>8 && x<12) {d=d+(forwardmod*14);}
						else if(y==15 && x>9 && x<12) {d=d+(forwardmod*15);}
						else if(y==16 && x>10 && x<13) {d=d+(forwardmod*16);}*/
						
//board.Forwardness(player)-board.Forwardness(other_player);
//chose poorly
/* 
score=-3
if(y==1) {d=d+(board.Forwardness(player)*forwardmod*0) - board.Forwardness(other_player);}
else if(y==2) {d=d+(board.Forwardness(player)*forwardmod*1) - board.Forwardness(other_player);}
else if(y==3) {d=d+(board.Forwardness(player)*forwardmod*2) - board.Forwardness(other_player);} 
else if(y==4) {d=d+(board.Forwardness(player)*forwardmod*3) - board.Forwardness(other_player);}
else if(y==5) {d=d+(board.Forwardness(player)*forwardmod*4) - board.Forwardness(other_player);}
else if(y==6) {d=d+(board.Forwardness(player)*forwardmod*5) - board.Forwardness(other_player);}
else if(y==7) {d=d+(board.Forwardness(player)*forwardmod*6) - board.Forwardness(other_player);}
else if(y==8) {d=d+(board.Forwardness(player)*forwardmod*7) - board.Forwardness(other_player);}
else if(y==9) {d=d+(board.Forwardness(player)*forwardmod*8) - board.Forwardness(other_player);}
else if(y==10) {d=d+(board.Forwardness(player)*forwardmod*9) - board.Forwardness(other_player);}
else if(y==11) {d=d+(board.Forwardness(player)*forwardmod*10) - board.Forwardness(other_player);}
else if(y==12) {d=d+(board.Forwardness(player)*forwardmod*11) - board.Forwardness(other_player);}
else if(y==13) {d=d+(board.Forwardness(player)*forwardmod*12) - board.Forwardness(other_player);}
else if(y==14) {d=d+(board.Forwardness(player)*forwardmod*13) - board.Forwardness(other_player);}
else if(y==15) {d=d+(board.Forwardness(player)*forwardmod*14) - board.Forwardness(other_player);}
else if(y==16) {d=d+(board.Forwardness(player)*forwardmod*15) - board.Forwardness(other_player);}
else if(y==17) {d=d+(board.Forwardness(player)*forwardmod*16) - board.Forwardness(other_player);}

if(y==1) {d=d+(board.Forwardness(player)*forwardmod*0) - (board.Forwardness(other_player)*forwardmod*16);}
else if(y==2) {d=d+((board.Forwardness(player)*forwardmod*1) - (board.Forwardness(other_player)*forwardmod*15));}
else if(y==3) {d=d+((board.Forwardness(player)*forwardmod*2) - (board.Forwardness(other_player)*forwardmod*14));} 
else if(y==4) {d=d+((board.Forwardness(player)*forwardmod*3) - (board.Forwardness(other_player)*forwardmod*13));}
else if(y==5) {d=d+((board.Forwardness(player)*forwardmod*4) - (board.Forwardness(other_player)*forwardmod*12));}
else if(y==6) {d=d+((board.Forwardness(player)*forwardmod*5) - (board.Forwardness(other_player)*forwardmod*11));}
else if(y==7) {d=d+((board.Forwardness(player)*forwardmod*6) - (board.Forwardness(other_player)*forwardmod*10));}
else if(y==8) {d=d+((board.Forwardness(player)*forwardmod*7) - (board.Forwardness(other_player)*forwardmod*9));}
else if(y==9) {d=d+((board.Forwardness(player)*forwardmod*8) - (board.Forwardness(other_player)*forwardmod*8));}
else if(y==10) {d=d+((board.Forwardness(player)*forwardmod*9) - (board.Forwardness(other_player)*forwardmod*7));}
else if(y==11) {d=d+((board.Forwardness(player)*forwardmod*10) - (board.Forwardness(other_player)*forwardmod*6));}
else if(y==12) {d=d+((board.Forwardness(player)*forwardmod*11) - (board.Forwardness(other_player)*forwardmod*5));}
else if(y==13) {d=d+((board.Forwardness(player)*forwardmod*12) - (board.Forwardness(other_player)*forwardmod*4));}
else if(y==14) {d=d+((board.Forwardness(player)*forwardmod*13) - (board.Forwardness(other_player)*forwardmod*3));}
else if(y==15) {d=d+((board.Forwardness(player)*forwardmod*14) - (board.Forwardness(other_player)*forwardmod*2));}
else if(y==16) {d=d+((board.Forwardness(player)*forwardmod*15) - (board.Forwardness(other_player)*forwardmod*1));}
else if(y==17) {d=d+((board.Forwardness(player)*forwardmod*16) - (board.Forwardness(other_player)*forwardmod*0));}*/




