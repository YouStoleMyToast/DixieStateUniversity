#pragma once

//maze class
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include "glut.h"

const int M=5;
const int N=4;
const int cellsize=1;//1;//=orig
const int marginsize=0;
const int wallwidth=3;

class Maze
{
public:
	Maze();
	void Create();
	void CreateRecursive(int i, int j);
	void Drawfloor(double texname);
	void DrawTable(double x, double y, double texname);

	void Draw(double texname1,double texname2, double texname3, double texname4);

	void DrawTree(double x, double y, double texname);
	void DrawSphere(double x, double y, double z, double radius, double texname);
	double GetStartX();
	bool IsSafe(double x, double y, double ratwidth, double ratlength);
	bool topview;

private:
	class Cell
	{
	public:
		Cell()
		{
			this->Top=true;
			this->Right=true;
			this->Bottom=true;
			this->Left=true;
			this->Visited=false;
		}
		void Draw3d(double i, double j, double texname1,double texname2, double texname3, double texname4);
		void Draw2d(double i, double j);

		bool Top, Right, Bottom, Left;
		bool Visited;
	};

	Cell Cells[M][N];
	double startx;
};
