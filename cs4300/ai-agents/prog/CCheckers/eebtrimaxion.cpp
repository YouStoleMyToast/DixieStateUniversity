#include "eebtrimaxion.h"
#include <cstdio>
#include <iostream>
#include <math.h>

namespace eebx
{
	bool maxdash=false;
	const double MY_INFINITY=1.e10;
	PlyData::PlyData(double utility_in):move_ok(false),utility(utility_in) {/*empty*/}
	Trimaxion::Trimaxion(ai::Agent::Options *opts):max_depth(3),evaluation_method(TT_k13)
	{
		if(opts->GetArgInt("user1")>0){this->max_depth=opts->GetArgInt("user1");}
		{
			char buf[128];
			std::sprintf(buf,"Trimaxion (%d)",this->max_depth);
			SetName(buf);
		}
		std::cout<<"Options:"<<std::endl;
		std::cout<<"-U num : maximum search depth (in ply)."<<std::endl;
	}
	Trimaxion::~Trimaxion(){/*empty*/}
	ai::Agent::Action * Trimaxion::Program(const ai::Agent::Percept * percept)
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
		else {action->SetCode(ai::CCheckers::CCheckersAction::QUIT);}
		return action;
	}
	PlyData Trimaxion::PickMove(const ai::CCheckers::BasicBoard &board, int player)
	{
		PlyData ply_data=this->Max(board,player,1,-MY_INFINITY,MY_INFINITY);
		return ply_data;
	}
	PlyData Trimaxion::Max(const ai::CCheckers::BasicBoard &board,int player,int depth,double alpha,double beta)
	{
		PlyData ply_data(-MY_INFINITY);
		if(board.HaveWinner() || depth>this->max_depth)
		{

			ply_data.utility=this->k13(board, player);
			return ply_data;

		}
		ai::CCheckers::BasicBoard my_board(board);
		const std::vector<ai::CCheckers::MoveData> & moves=my_board.DetermineLegalMoves(player);
		std::vector<PlyData> best_plys;
		int i;
		if(player==1)
		{
			for(i=0;i<(int)moves.size();i++)
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
			for(i=0;i<(int)moves.size();i++)
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
	PlyData Trimaxion::Min(const ai::CCheckers::BasicBoard &board,int player,int depth,double alpha,double beta)
	{
		PlyData ply_data(MY_INFINITY);
		if(board.HaveWinner() || depth>this->max_depth)
		{
			ply_data.utility=this->k13(board, player);
			return ply_data;
		}
		int other_player=(player==1)? 2:1;
		ai::CCheckers::BasicBoard my_board(board);
		const std::vector<ai::CCheckers::MoveData> & moves=my_board.DetermineLegalMoves(other_player);
		std::vector<PlyData> best_plys;
		int i;
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
	double Trimaxion::k13(const ai::CCheckers::BasicBoard &board, int player)
	{
		bool yourfirst, otherfirst;
		int x,y,d=0;
		int forwardmod, centermod, lagmod;//1's 1:8,2:17//15's 1:8,2:14//18's 1:8,2:21//2's 1:8,2:21//21's 1:8,2:21//25's 1:8,2:16//3's 1:8,2:16
		int selffront,selfback,opfront,opback;
		int other_player=(player==1)? 2:1;
		ai::CCheckers::BoardData newboard=board.GetBoard();
		if(player==1)
		{
			for(x=0; x<17; x++)
			{
				yourfirst=true;
				otherfirst=true;
				for(y=0; y<17; y++)
				{
					selffront=0;
					selfback=0;
					opfront=16;
					opback=16;
					forwardmod=20000;
					centermod=2000;
					lagmod=200;
					if(newboard.hole[x][y]==player)
					{
						if(newboard.hole[x][y]==player || newboard.hole[x][y]==other_player)
						{
							
							if(newboard.hole[x][y]==player && yourfirst) 
							{
								selfback=y;
								yourfirst=false;
							}
							if(newboard.hole[x][y]==player && y>selffront) {selffront=y;}
							if(newboard.hole[x][y]==other_player) {opback=y;}
							if(newboard.hole[x][y]==other_player && y<opfront) {opfront=y;}
							
							
							if(selfback>opback){maxdash=true;}
							else {maxdash=false;}
							
							
							d=d+(board.Forwardness(player)*forwardmod)+(x*centermod)-(board.Forwardness(other_player)*forwardmod);
							if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
							d=d-((selffront-selfback)*lagmod*y);
							return d;
						}
					}
				}
			}
		}
		else if(player==2)
		{
			for(x=0; x<17; x++)
			{
				yourfirst=true;
				otherfirst=true;
				for(y=0; y<17; y++)
				{
					selffront=16;
					selfback=16;
					opfront=0;
					opback=0;
					forwardmod=20000;
					centermod=2000;
					lagmod=100;
					if(newboard.hole[x][y]==player)
					{
						if(newboard.hole[x][y]==player || newboard.hole[x][y]==other_player)
						{
							if(newboard.hole[x][y]==player && yourfirst) 
							{
								selffront=y;
								yourfirst=false;
							}
							if(newboard.hole[x][y]==player && y<selfback) {selfback=y;}
							
							if(newboard.hole[x][y]==other_player && otherfirst) 
							{
								opback=y;
								otherfirst=false;
							}
							if(newboard.hole[x][y]==other_player && y<opfront) {opfront=y;}
							
							
							if(selfback<opback){maxdash=true;}
							else {maxdash=false;}


							d=d+(board.Forwardness(player)*forwardmod)+(x*centermod)-(board.Forwardness(other_player)*forwardmod);
							if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
							d=d-((selffront-selfback)*lagmod*y);
							return d;
						}
					}
				}
			}
		}
		return d;
	}
}
/*
	12 and 9-trap(other) one
	double Trimaxion::k13(const ai::CCheckers::BasicBoard &board, int player)
	{
		bool yourfirst, otherfirst;
		int x,y,d=0;
		int forwardmod, centermod, lagmod;//1's 1:8,2:17//15's 1:8,2:14//18's 1:8,2:21//2's 1:8,2:21//21's 1:8,2:21//25's 1:8,2:16//3's 1:8,2:16
		int selffront,selfback,opfront,opback;
		int other_player=(player==1)? 2:1;
		ai::CCheckers::BoardData newboard=board.GetBoard();
		if(player==1)
		{
			for(x=0; x<17; x++)
			{
				yourfirst=true;
				otherfirst=true;
				for(y=0; y<17; y++)
				{
					if(newboard.hole[x][y]==player)
					{
						if(newboard.hole[x][y]==player || newboard.hole[x][y]==other_player)
						{
							selffront=0;
							selfback=0;
							opfront=16;
							opback=16;
							forwardmod=20000;
							centermod=2000;
							lagmod=200;
							
							if(newboard.hole[x][y]==player && yourfirst) 
							{
								selfback=y;
								yourfirst=false;
							}
							if(newboard.hole[x][y]==player && y>selffront) {selffront=y;}
							if(newboard.hole[x][y]==other_player) {opback=y;}
							if(newboard.hole[x][y]==other_player && y<opfront) {opfront=y;}
							
							
							if(selfback>opback){maxdash=true;}
							else {maxdash=false;}
							
							
							d=d+(board.Forwardness(player)*forwardmod)+(x*centermod)-(board.Forwardness(other_player)*forwardmod);
							if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
							d=d-((selffront-selfback)*lagmod*y);
							return d;
						}
					}
				}
			}
		}
		else if(player==2)
		{
			for(x=0; x<17; x++)
			{
				yourfirst=true;
				otherfirst=true;
				for(y=0; y<17; y++)
				{
					if(newboard.hole[x][y]==player)
					{
						if(newboard.hole[x][y]==player || newboard.hole[x][y]==other_player)
						{
							selffront=16;
							selfback=16;
							opfront=0;
							opback=0;
							forwardmod=20000;
							centermod=2000;
							lagmod=200;
							
							if(newboard.hole[x][y]==player && yourfirst) 
							{
								selffront=y;
								yourfirst=false;
							}
							if(newboard.hole[x][y]==player && y<selfback) {selfback=y;}
							
							if(newboard.hole[x][y]==other_player && otherfirst) 
							{
								opback=y;
								otherfirst=false;
							}
							if(newboard.hole[x][y]==other_player && y<opfront) {opfront=y;}
							
							
							if(selfback<opback){maxdash=true;}
							else {maxdash=false;}


							d=d+(board.Forwardness(player)*forwardmod)+(x*centermod)-(board.Forwardness(other_player)*forwardmod);
							if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
							d=d-((selffront-selfback)*lagmod*y);
							return d;
						}
					}
				}
			}
		}
		return d;
	}
}*/
