#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;
#include "Perry.h"
#include "graphics.h"
#include "glut.h"
#include "Maze.h"
#include <gl/GLU.h>

Rat::Rat(void)
{
}

Rat::~Rat(void) 
{
}

void Rat::Initialize(Maze & m)
{
	X=m.GetStartX()+.5;
	Y=-.5;
	Degrees=90;
}
double Rat::GetX()
{
	return X; 
}
double Rat::GetY()
{
	return Y; 
}
double Rat::GetDegrees()
{
	return Degrees;
}
void Rat::Spinleft(double DT)
{
	Degrees += 360*revolutions_per_second*DT;
	if (Degrees >=360.0)
	{
		Degrees-=360;
	}
}

void Rat::Spinright(double DT)
{
	Degrees -= 360*revolutions_per_second*DT;
	if (Degrees <=0)
	{
		Degrees+=360;
	}
}
void Rat::Moveforeward(Maze & m, double DT, bool topview)
{
	//perry dimensions left=.1 right=-.1back=-.42 front=.35
	double radians=Degrees*M_PI/180.0;
	double dx=cos(radians);// for circular original
	double dy=sin(radians);// for circular original
	double nextx=X+dx*cells_per_second*DT*4;
	double nexty=Y+dy*cells_per_second*DT*4;
	/*
	if(topview==true)
	{
		double nextx=X+dx*cells_per_second*DT*2;
		double nexty=Y+dy*cells_per_second*DT*2;
	}
	*/

	//for both next x and next y not safe
	if (m.IsSafe(nextx, nexty, ratwidth, ratlength))
	{
		X=nextx;
		Y=nexty;
	}
	//for next x safe but y not safe
	else if(m.IsSafe(nextx, Y, ratwidth, ratlength))
	{
		X=nextx;
	}
	//for next y safe but x not safe
	else if(m.IsSafe(X, nexty, ratwidth, ratlength))
	{
		Y=nexty;
	}
}
void Rat::DrawFeet(double fx, double fy, double fz, double fradius, double bodybottom, bool moving, bool topview, int num)
{

	static clock_t starttime=clock();//built in function clock() problem default is 17 clicks a second while we need about 100 so we made changes
	static int currentframe=0;
	clock_t currenttime=clock();
	currentframe+=1;
	double up=.08;
	double down=.02;
	int mod1=500;
	int mod2=250;
	if (moving==true)
	{
		//foot 1 is front right
		//foot 2 is front left
		//foot 3 is back left
		//foot 4 is back right
		if(currentframe%mod1>=mod2 && num==1)
		{
			fz=up;
			if(topview==true)
				fy=fy+.1;
		}
		else if(currentframe%mod1>=mod2 && num==2)
		{
			fz=down;
		}
		else if(currentframe%mod1<mod2 && num==3)
		{
			fz=down;
		}
		else if(currentframe%mod1<mod2 && num==4)
		{
			fz=up;
			if(topview==true)
				fy=fy+.1;
		}
		else if(currentframe%mod1<mod2 && num==1)
		{
			fz=down;
		}
		else if(currentframe%mod1<mod2 && num==2)
		{
			fz=up;
			if(topview==true)
				fy=fy-.1;
		}
		else if(currentframe%mod1>=mod2 && num==3)
		{
			fz=up;
			if(topview==true)
				fy=fy-.1;
		}
		else if(currentframe%mod1>=mod2 && num==4)
		{
			fz=down;
		}
	}
	if (moving==false)
	{
		fz=down;
	}

	glBegin(GL_POLYGON);
	glColor3d(.9,.8,.0);
	double fzcurr=fz;
	double fzbottom=fz-.01;
	while(fzcurr>fzbottom)
	{
		for(int i=0; i<32; i++)
		{

			double theta = (double)i/32.0 * 2.0 * 3.1415926;
			fx = fx + fradius * cos(theta);
			fy = fy + fradius * sin(theta);
			glVertex3d(fx, fy, fzcurr);
		}
		fzcurr-=.0002;
	}
	glEnd();

	double lx=fx;
	double ly=0;
	double lz=bodybottom+.01;
	double lradius=fradius/2;
	if(fy>0)
	{
		ly=fy+fradius-.01;
	}
	else if(fy<0)
	{
		ly=fy+fradius+.045;
	}

	glBegin(GL_POLYGON);
	glColor3d(0,.8,.8);
	while(lz>fz)
	{
		for(int i=0; i<32; i++)
		{
			double theta = (double)i/32.0 * 2.0 * 3.1415926;
			lx = lx + lradius * cos(theta);
			ly = ly + lradius * sin(theta);
			glVertex3d(lx, ly, lz);
		}
		lz=lz-.0005;
	}
	glEnd();
}


void Rat::DrawEye(double eyex, double eyey, double eyez)
{
	//sphere
	double eyeradius=.048;
	glColor3d(1, 1, 1); 
	glTranslated(eyex,eyey,eyez); 
	glutSolidSphere (eyeradius, 32, 32);
	glEnd();
}
void Rat::DrawPupil(double pupilx, double pupily, double pupilz, double pupilradius)
{
	glColor3d(0,0,0);
	glTranslated(pupilx,pupily,pupilz); 
	glutSolidSphere (pupilradius, 32, 32);
	glEnd();
}

void Rat::DrawBill(Maze &m , double DT, bool moving)
{
	//translate the rat
	glPushMatrix();//make copy of matrix to translate //measures to move just the rat
	double x=X;//2.5;
	double y=Y;//.5;
	glTranslated(x,y,0);
	glRotated(Degrees,0,0,1);// first is angle by degrees(0 is right, 90 is up, 180 is left, 270 is down)

	glLineWidth((GLfloat).5);
	//x axis
	double bodyfront=0;
	double bodyback=-0;
	//y axis
	double bodyleft=0.1;
	double bodyright=-0.1;
	//z axis
	double bodytop=0.3;
	double bodybottom=0.1;

	double billlength=0.25;
	double billwidthmodifier=.2;
	//x axis
	double billfront=bodyfront+billlength;
	double billback=bodyfront;

	//y axis
	double billleft=bodyleft-billwidthmodifier;
	double billright=bodyright+billwidthmodifier;

	//z axis
	double billtop=0.1;
	double billbottom=-0.05;

	//bill top
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glEnd();


	//bill bottom
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billfront, billleft, billbottom);
	glVertex3d(billfront, billright, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billfront, billleft,billbottom);
	glVertex3d(billfront, billright, billbottom);
	glEnd();

	//bill left
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();

	//bill Right
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glEnd();
	
	//bill Front
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();
	
	//bill Back
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glEnd();
	glPopMatrix();
}

void Rat::Draw(Maze & m, double DT, bool moving, bool topview)
{
	//translate the rat
	glPushMatrix();//make copy of matrix to translate //measures to move just the rat
	double x=X;//2.5;
	double y=Y;//.5;
	glTranslated(x,y,0);
	glRotated(Degrees,0,0,1);// first is angle by degrees(0 is right, 90 is up, 180 is left, 270 is down)

	glLineWidth((GLfloat).5);

	//perry dimensions left=.1 right=-.1back=-.40 front=.37

	//x axis
	double bodyfront=0.24;
	double bodyback=-0.20;
	//y axis
	double bodyleft=0.1;
	double bodyright=-0.1;
	//z axis
	double bodytop=0.3;
	double bodybottom=0.1;


	//feet
	//x axis
	double frontx=0.15;
	double backx=-0.15;
	//y axis
	double lefty=.04;
	double righty=-.15;
	//z axis
	double ground=.01;

	double fradius=.01;

	DrawFeet(frontx,righty,ground,fradius, bodybottom, moving,topview, 1);
	DrawFeet(frontx,lefty,ground,fradius, bodybottom, moving,topview, 2);
	DrawFeet(backx,lefty,ground,fradius, bodybottom, moving,topview, 3);
	DrawFeet(backx,righty,ground,fradius, bodybottom, moving,topview, 4);

	//body top
	glColor3d(0,.8,.8);
	glBegin(GL_QUADS);
	glVertex3d(bodyback, bodyright, bodytop);
	glVertex3d(bodyback, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyright, bodytop);
	glEnd();

	glColor3d(0,0.6,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(bodyback, bodyright, bodytop);
	glVertex3d(bodyback, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyright, bodytop);
	glEnd();

	//body bottom
	glColor3d(0,.8,.8);
	glBegin(GL_QUADS);
	glVertex3d(bodyback, bodyright, bodybottom);
	glVertex3d(bodyback, bodyleft, bodybottom);
	glVertex3d(bodyfront, bodyleft, bodybottom);
	glVertex3d(bodyfront, bodyright, bodybottom);
	glEnd();

	glColor3d(0,0.6,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(bodyback, bodyright, bodybottom);
	glVertex3d(bodyback, bodyleft, bodybottom);
	glVertex3d(bodyfront, bodyleft, bodybottom);
	glVertex3d(bodyfront, bodyright, bodybottom);
	glEnd();

	//body left
	glColor3d(0,.8,.8);
	glBegin(GL_QUADS);
	glVertex3d(bodyback, bodyleft, bodybottom);
	glVertex3d(bodyback, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyleft, bodybottom);
	glEnd();

	glColor3d(0,0.6,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(bodyback, bodyleft, bodybottom);
	glVertex3d(bodyback, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyleft, bodybottom);
	glEnd();

	//body Right
	glColor3d(0,.8,.8);
	glBegin(GL_QUADS);
	glVertex3d(bodyback, bodyright, bodybottom);
	glVertex3d(bodyback, bodyright, bodytop);
	glVertex3d(bodyfront, bodyright, bodytop);
	glVertex3d(bodyfront, bodyright, bodybottom);
	glEnd();

	glColor3d(0,0.6,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(bodyback, bodyright, bodybottom);
	glVertex3d(bodyback, bodyright, bodytop);
	glVertex3d(bodyfront, bodyright, bodytop);
	glVertex3d(bodyfront, bodyright, bodybottom);
	glEnd();
	
	//body Front
	glColor3d(0,.8,.8);
	glBegin(GL_QUADS);
	glVertex3d(bodyfront, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyright, bodytop);
	glVertex3d(bodyfront, bodyright, bodybottom);
	glVertex3d(bodyfront, bodyleft, bodybottom);
	glEnd();

	glColor3d(0,0.6,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(bodyfront, bodyleft, bodytop);
	glVertex3d(bodyfront, bodyright, bodytop);
	glVertex3d(bodyfront, bodyright, bodybottom);
	glVertex3d(bodyfront, bodyleft, bodybottom);
	glEnd();
	
	//body Back
	glColor3d(0,.8,.8);
	glBegin(GL_QUADS);
	glVertex3d(bodyback, bodyleft, bodytop);
	glVertex3d(bodyback, bodyright, bodytop);
	glVertex3d(bodyback, bodyright, bodybottom);
	glVertex3d(bodyback, bodyleft, bodybottom);
	glEnd();

	glColor3d(0,0.6,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(bodyback, bodyleft, bodytop);
	glVertex3d(bodyback, bodyright, bodytop);
	glVertex3d(bodyback, bodyright, bodybottom);
	glVertex3d(bodyback, bodyleft, bodybottom);
	glEnd();

	//////////////////bill//////////////////

	/*
	//x axis
	double bodyfront=0.22;
	double bodyback=-0.22;
	//y axis
	double bodyleft=0.1;
	double bodyright=-0.1;
	//z axis
	double bodytop=0.3;
	double bodybottom=0.1;
	*/

	double billlength=0.13;
	double billwidthmodifier=.01;
	//x axis
	double billfront=bodyfront+billlength;
	double billback=bodyfront;

	//y axis
	double billleft=bodyleft-billwidthmodifier;
	double billright=bodyright+billwidthmodifier;

	//z axis
	double billtop=0.15;
	double billbottom=0.1;


	//bill top
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glEnd();


	//bill bottom
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billfront, billleft, billbottom);
	glVertex3d(billfront, billright, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billfront, billleft,billbottom);
	glVertex3d(billfront, billright, billbottom);
	glEnd();

	//bill left
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billleft, billbottom);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();

	//bill Right
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glEnd();
	
	//bill Front
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billfront, billleft, billtop);
	glVertex3d(billfront, billright, billtop);
	glVertex3d(billfront, billright, billbottom);
	glVertex3d(billfront, billleft, billbottom);
	glEnd();
	
	//bill Back
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(billback, billleft, billtop);
	glVertex3d(billback, billright, billtop);
	glVertex3d(billback, billright, billbottom);
	glVertex3d(billback, billleft, billbottom);
	glEnd();

	/*
	//x axis
	double bodyfront=0.22;
	double bodyback=-0.22;
	//y axis
	double bodyleft=0.1;
	double bodyright=-0.1;
	//z axis
	double bodytop=0.3;
	double bodybottom=0.1;
	*/
	double taillength=0.2;
	double tailwidthmodifier=0.18;
	double tailthickness=.02;
	//tail
	//x axis
	double tailfront=bodyback;
	double tailback=bodyback-taillength;
	//y axis
	double tailleft=bodyleft-tailwidthmodifier;
	double tailright=bodyright+tailwidthmodifier;
	//z axis
	double tailtop=bodybottom+tailthickness;
	double tailbottom=bodybottom;
	double tailhighendmodifyer=.05;
	double taillowendmodifyer=-.05;

	//tail top
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(tailback, tailright, tailtop+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailtop+taillowendmodifyer);
	glVertex3d(tailfront, tailleft, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailtop+tailhighendmodifyer);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(tailback, tailright, tailtop+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailtop+taillowendmodifyer);
	glVertex3d(tailfront, tailleft, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailtop+tailhighendmodifyer);
	glEnd();


	//tail bottom
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(tailback, tailright, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailbottom+taillowendmodifyer);
	glVertex3d(tailfront, tailleft, tailbottom+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailbottom+tailhighendmodifyer);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(tailback, tailright, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailbottom+taillowendmodifyer);
	glVertex3d(tailfront, tailleft, tailbottom+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailbottom+tailhighendmodifyer);
	glEnd();

	//tail left
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(tailback, tailleft, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailtop+taillowendmodifyer);
	glVertex3d(tailfront, tailleft, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailleft, tailbottom+tailhighendmodifyer);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(tailback, tailleft, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailtop+taillowendmodifyer);
	glVertex3d(tailfront, tailleft, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailleft, tailbottom+tailhighendmodifyer);
	glEnd();

	//tail Right
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(tailback, tailright, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailright, tailtop+taillowendmodifyer);
	glVertex3d(tailfront, tailright, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailbottom+tailhighendmodifyer);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(tailback, tailright, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailright, tailtop+taillowendmodifyer);
	glVertex3d(tailfront, tailright, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailbottom+tailhighendmodifyer);
	glEnd();
	
	//tail Front
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(tailfront, tailleft, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailbottom+tailhighendmodifyer);
	glVertex3d(tailfront, tailleft, tailbottom+tailhighendmodifyer);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(tailfront, tailleft, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailtop+tailhighendmodifyer);
	glVertex3d(tailfront, tailright, tailbottom+tailhighendmodifyer);
	glVertex3d(tailfront, tailleft, tailbottom+tailhighendmodifyer);
	glEnd();
	
	//tail Back
	glColor3d(.9,.8,.0);
	glBegin(GL_QUADS);
	glVertex3d(tailback, tailleft, tailtop+taillowendmodifyer);
	glVertex3d(tailback, tailright, tailtop+taillowendmodifyer);
	glVertex3d(tailback, tailright, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailbottom+taillowendmodifyer);
	glEnd();

	glColor3d(.7,.6,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(tailback, tailleft, tailtop+taillowendmodifyer);
	glVertex3d(tailback, tailright, tailtop+taillowendmodifyer);
	glVertex3d(tailback, tailright, tailbottom+taillowendmodifyer);
	glVertex3d(tailback, tailleft, tailbottom+taillowendmodifyer);
	glEnd();

	/*
	//x axis
	double bodyfront=0.22;
	double bodyback=-0.22;
	//y axis
	double bodyleft=0.1;
	double bodyright=-0.1;
	//z axis
	double bodytop=0.3;
	double bodybottom=0.1;
	*/

	//eyes
	double eyex=0.22;
	double eyelefty=.07;
	double eyerighty=-.14;
	double eyez=.28;
	DrawEye(eyex, eyelefty, eyez);
	DrawEye(0, eyerighty, 0);


	//pupiles

	double pupilrightx=0.032;//foreward
	double pupilrighty=-0.0;//side
	double pupilrightz=0.016;//height
	double pupilradiusright=.021;

	double pupilleftx=-0.0;//foreward
	double pupillefty=0.14;//side
	double pupilleftz=0.004;//height
	double pupilradiusleft=.021;

	DrawPupil(pupilrightx, pupilrighty, pupilrightz, pupilradiusright);
	DrawPupil(pupilleftx, pupillefty, pupilleftz, pupilradiusleft);

	glPopMatrix();
}
