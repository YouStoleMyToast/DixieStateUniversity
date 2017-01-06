#include "eebjohnny5.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>

namespace eebj
{
	const double MY_INFINITY=1.e10;
	int myfront1=0;
	int myfront2=17;
	int myback1=0;
	int myback2=17;
	
	int opfront1=0;
	int opfront2=17;
	int opback1=0;
	int opback2=17;
	
	int newdepth=3;
	int yatnewdepth=8;
	PlyData::PlyData(double utility_in):move_ok(false),utility(utility_in) {/*empty*/}
	Johnny5::Johnny5(ai::Agent::Options *opts):max_depth(3),evaluation_method(TT_k13)
	{
		//std::srand(std::time(0));
		if(opts->GetArgInt("user1")>0){this->max_depth=opts->GetArgInt("user1");}
		{
			char buf[128];
			std::sprintf(buf,"Johnny5");
			SetName(buf);
		}
		std::cout<<"Options:"<<std::endl;
		std::cout<<"-U num : maximum search depth (in ply)."<<std::endl;
	}
	Johnny5::~Johnny5(){/*empty*/}
	ai::Agent::Action * Johnny5::Program(const ai::Agent::Percept * percept)
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
	PlyData Johnny5::PickMove(const ai::CCheckers::BasicBoard &board, int player)
	{
		if(myfront1<yatnewdepth && player==1){this->max_depth=3;}
		else if(myfront1>=yatnewdepth && player==1){this->max_depth=newdepth;}
		if(myfront2>yatnewdepth && player==2){this->max_depth=3;}
		else if(myfront2<=yatnewdepth && player==2){this->max_depth=newdepth;}
		
		PlyData ply_data=this->Max(board,player,1,-MY_INFINITY,MY_INFINITY);
		return ply_data;
	}
	bool sortmoves1(ai::CCheckers::MoveData i, ai::CCheckers::MoveData j)
	{
		int x,y;
		x=(i.to_y - i.from_y);
		y=(j.to_y - j.from_y);
		return x>y;
	}
	bool sortmoves2(ai::CCheckers::MoveData i, ai::CCheckers::MoveData j)
	{
		int x,y;
		x=-(i.to_y - i.from_y);
		y=-(j.to_y - j.from_y);
		return x>y;
	}
	PlyData Johnny5::Max(const ai::CCheckers::BasicBoard &board,int player,int depth,double alpha,double beta)
	{
		PlyData ply_data(-MY_INFINITY);
		
		if(board.HaveWinner() || depth>this->max_depth)
		{		
			ply_data.utility=this->k13(board, player);
			return ply_data;
		}
		ai::CCheckers::BasicBoard my_board(board);
		std::vector<ai::CCheckers::MoveData> moves=my_board.DetermineLegalMoves(player);
		std::vector<PlyData> best_plys;
		int i;

		//if(player==1) {std::sort(moves.begin(),moves.end(),sortmoves1);}
		//else if(player==2) {std::sort(moves.begin(),moves.end(),sortmoves2);}
		if(player==1)
		{
			for(i=0;i<(int)moves.size();i++)
			{
				if(moves[i].from_y <= (moves[i].to_y))// && (moves[i].to_x < (moves[i].to_y + 5)))// && (moves[i].to_x > (moves[i].to_y - 5)))
				{
				
					if(myfront1 < moves[i].to_y) {myfront1=moves[i].to_y;}
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
		else if(player==2)
		{
			for(i=0;i<(int)moves.size();i++)
			{
				if(moves[i].from_y >= moves[i].to_y)
				{
					if(myfront2 < moves[i].to_y) {myfront2=moves[i].to_y;}
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
		return best_plys[std::rand() % best_plys.size()];
	}
	PlyData Johnny5::Min(const ai::CCheckers::BasicBoard &board,int player,int depth,double alpha,double beta)
	{
		PlyData ply_data(MY_INFINITY);
		if(board.HaveWinner() || depth>this->max_depth)
		{
			ply_data.utility=this->k13(board, player);
			return ply_data;
		}
		int other_player=(player==1)? 2:1;
		ai::CCheckers::BasicBoard my_board(board);
		std::vector<ai::CCheckers::MoveData> moves=my_board.DetermineLegalMoves(other_player);
		std::vector<PlyData> best_plys;
		int i;
		
		//if(player==1) {std::sort(moves.begin(),moves.end(),sortmoves1);}
		//else if(player==2) {std::sort(moves.begin(),moves.end(),sortmoves2);}
		
		if(other_player==1)
		{
			for(i=0;i<(int)moves.size();i++)
			{
				if(moves[i].from_y <= moves[i].to_y)
				{
					if(myfront1 < moves[i].to_y) {myfront1=moves[i].to_y;}
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
					if(myfront2 < moves[i].to_y) {myfront2=moves[i].to_y;}
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
		return best_plys[std::rand() % best_plys.size()];
	}
	bool first;
	double Johnny5::k13(const ai::CCheckers::BasicBoard &board, int player)
	{
		int x,y,d=0;
		int forwardmod, centermod,opforwardmod, opcentermod;
		int other_player=(player==1)? 2:1;
		ai::CCheckers::BoardData newboard=board.GetBoard();

		//int rangestarty;
		//int rangeendy=17;
		// 1 (bottom)
		//{{4, 0}, {4, 1},{5, 1}, {4, 2},{5, 2},{6, 2}, {4, 3},{5, 3},{6, 3},{7, 3}},
		// 2 (top)
		//{{12, 16}, {11, 15},{12, 15}, {10, 14},{11, 14},{12, 14}, { 9, 13},{10, 13},{11, 13},{12, 13}}
		/*if(player==1)
		{
			if(newboard.hole[12][16]==player) {rangeendy=16;}
			if(newboard.hole[11][15]==player && newboard.hole[12][15]==player) {rangeendy=15;}
			if(newboard.hole[10][14]==player && newboard.hole[11][14]==player && newboard.hole[12][14]==player) {rangeendy=14;}
			if(newboard.hole[9][13]==player && newboard.hole[10][13]==player && newboard.hole[11][13]==player && newboard.hole[12][13]==player) {rangeendy=13;}
		}*/
		first=true;
		for(x=0; x<17; x++)
		{
			for(y=0; y<17; y++)
			{
				if(newboard.hole[x][y]==player)
				{
					if(player==1)
					{
						/*
						forwardmod=200;
						centermod=20;
						opforwardmod=200;
						opcentermod=20;
						if(board.Forwardness(player)<board.Forwardness(other_player)){break;}
						else if(board.Forwardness(player)>=board.Forwardness(other_player))
						{
							if(y>11){d=d+((board.Forwardness(player)*forwardmod)-(board.Forwardness(other_player)*opforwardmod));}
							else
							{
								d=d+((board.Forwardness(player)*forwardmod)+(x*centermod))-((board.Forwardness(other_player)*opforwardmod));
								if(x>(y-3) && x<(y+3)) {d=d+(centermod*y*2);}
								if(x>(y-2) && x<(y+2)) {d=d+(centermod*y*1);}
								if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
							}
							return d;
						}*/
						
						/*
						if(newboard.hole[12][16]==player) {break;}
						if(newboard.hole[12][16]==player 
							&& newboard.hole[11][15]==player 
							&& newboard.hole[12][15]==player) 
							{break;}
						if(newboard.hole[12][16]==player 
							&& newboard.hole[11][15]==player 
							&& newboard.hole[12][15]==player 
							&& newboard.hole[10][14]==player 
							&& newboard.hole[11][14]==player 
							&& newboard.hole[12][14]==player) 
							{break;}
						if(newboard.hole[12][16]==player 
							&& newboard.hole[11][15]==player 
							&& newboard.hole[12][15]==player 
							&& newboard.hole[10][14]==player 
							&& newboard.hole[11][14]==player 
							&& newboard.hole[12][14]==player
						
							&& (newboard.hole[9][13]==player 
							|| newboard.hole[10][13]==player 
							|| newboard.hole[11][13]==player 
							|| newboard.hole[12][13]==player)) 
							{break;}*/
						
						if(first==true)
						{
							myback1=y;
							first=false;
						}
						forwardmod=200;
						centermod=20;
						opforwardmod=200;
						opcentermod=20;
						if(board.Forwardness(player)<board.Forwardness(other_player)){break;}
						else if(board.Forwardness(player)>=board.Forwardness(other_player))
						{
							d=d+((board.Forwardness(player)*forwardmod)+(x*centermod))-((board.Forwardness(other_player)*opforwardmod));
							if(x>(y-3) && x<(y+3)) {d=d+(centermod*y*2);}
							if(x>(y-2) && x<(y+2)) {d=d+(centermod*y*1);}
							if(x>(y-1) && x<(y+1)) {d=d+(centermod*y);}
							
							//if((myfront1-myback1)>8){d=d-(myfront1-myback1)*y;}
						}
						return d;
						
					}
					else
					{
						/*
						forwardmod=200;
						centermod=20;
						opforwardmod=200;
						opcentermod=20;
						if(board.Forwardness(player)<board.Forwardness(other_player)){break;}
						else if(board.Forwardness(player)>=board.Forwardness(other_player))
						{
							if(y<5){d=d+((board.Forwardness(player)*forwardmod)-(board.Forwardness(other_player)*opforwardmod));}
							else
							{
								d=d+((board.Forwardness(player)*forwardmod)+(x*centermod))-((board.Forwardness(other_player)*opforwardmod));
								if(x>(y-1) && x<(y+1)) {d=d-(centermod*y);}
							}
							return d;
						}*/
						myback2=y;
						forwardmod=200;
						centermod=20;
						opforwardmod=200;
						opcentermod=20;
						if(board.Forwardness(player)<board.Forwardness(other_player)){break;}
						else if(board.Forwardness(player)>=board.Forwardness(other_player))
						{
							d=d+((board.Forwardness(player)*forwardmod)+(x*centermod))-((board.Forwardness(other_player)*opforwardmod));
							if(x>(y-1) && x<(y+1)) {d=d-(centermod*y);}
							
							//if((myback2-myfront2)>8){d=d-(myback2-myfront2)*(17-y);}
						}
						return d;
					}
				}
			}
		}
		return d;
	}
}





