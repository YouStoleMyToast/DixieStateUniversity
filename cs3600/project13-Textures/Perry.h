#pragma once

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "Maze.h"

const double revolutions_per_second=1;//1 is orig
const double cells_per_second=0.4;
const double max_rat_radius=0.317;
const double ratlength=.4;
const double ratwidth=.1;
//perry dimensions left=.1 right=-.1back=-.42 front=.35
class Rat
{
public:
	Rat(void);
	~Rat(void);
	void Spinleft(double DT);
	void Spinright(double DT);
	void Moveforeward(Maze & m,double DT, bool topview);
	void DrawEye(double eyex, double eyey, double eyez);
	void DrawPupil(double pupilex, double pupiley, double pupilez, double pupilradius);
	void DrawFeet(double fx,double fy, double fz, double fradius, double bodybottom, bool moving, bool topview,int num);
	void DrawBill(Maze &m , double DT, bool moving);
	void Draw(Maze & m,double DT, bool moving, bool topview);
	void Initialize(Maze & m);
	bool moving;
	double GetX();
	double GetY();
	double GetDegrees();


private:
	double Degrees;
	double X,Y;
};
