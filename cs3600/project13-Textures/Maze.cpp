#pragma once
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "glut.h"
#include "Maze.h"

Maze::Maze()
{
}

void Maze::Drawfloor(double texname)
{
	double floorz=0.0;
	double floorlow=-0.01;
	glColor3d(.1,.5,.3);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texname);
	glBegin(GL_QUADS);

	glTexCoord3d(0,0,0);glVertex3d(0-.05,0-.05,floorz);
	glTexCoord3d(1,0,0);glVertex3d(0-.05,N+.05,floorz);
	glTexCoord3d(1,1,0);glVertex3d(M+.05,N+.05,floorz);
	glTexCoord3d(0,1,0);glVertex3d(M+.05,0-.05,floorz);

	glEnd();
}

void Maze::DrawTree(double x, double y, double texname)
{
	
	double treeradius=.02;
	double theight=2;

	glColor3d(.5,.3,.2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texname);
	glBegin(GL_QUADS);
	double tx=x;
	double ty=y;
	for(int i=0; i<32; i++)
	{
		glTexCoord3d(0,0,0);glVertex3d(tx,ty,0);
		glTexCoord3d(1,0,0);glVertex3d(tx,ty,theight);
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		tx = tx + treeradius * cos(theta);
		ty = ty + treeradius * sin(theta);
		glTexCoord3d(1,1,0);glVertex3d(tx,ty,theight);
		glTexCoord3d(0,1,0);glVertex3d(tx,ty,0);
	}
	glEnd();
}
void Maze::DrawSphere(double x, double y, double z, double radius, double texname)
{
	glPushMatrix();
	glColor3d(.1, .3, .7); 
	GLUquadricObj *sphere = gluNewQuadric();
	gluQuadricTexture(sphere, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texname);
	glTranslated(x+(radius*.2),y+(radius*.2),z);
	glutSolidSphere (radius, 15, 15);
	glDisable(GL_TEXTURE_2D); 
	glEnd();
	glPopMatrix();
}
void Maze::DrawTable(double x, double y, double texname)
{
	double z=-.01;
	double radius=2*x;
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texname);
	glBegin(GL_POLYGON);
	glColor3d(.1,.5,.25);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double cx = x + radius * cos(theta);
		double cy = y + radius * sin(theta);
		glVertex3d(cx, cy, z);
	}
	glEnd();
}
void DrawLine(double i,double j,double x,double y)
{
	glLineWidth((GLfloat)wallwidth);
	glBegin(GL_LINES);
	glColor3d(.5,0,0);

	glVertex3d(i,j,.1);
	glVertex3d(x,y,.1);

	glEnd();

}
void Maze::Cell::Draw2d(double i, double j)
{
	int x1=marginsize+i*cellsize;
	int y1=marginsize+j*cellsize;
	int x2=x1+cellsize;
	int y2=y1+cellsize;
	if(Top)
	{
		DrawLine(x1,y2,x2,y2);
	}
	if(Right)
	{
		DrawLine(x2,y2,x2,y1);
	}
	if(Bottom)
	{
		DrawLine(x2,y1,x1,y1);
	}
	if(Left)
	{
		DrawLine(x1,y1,x1,y2);
	}
}
double wallcount=0;
void Maze::Cell::Draw3d(double i, double j, double texname1, double texname2, double texname3, double texname4)
{
	double walloutlineR=0;
	double walloutlineG=.3;
	double walloutlineB=.3;
	glLineWidth((GLfloat)wallwidth);
	glColor3d(0,.5,.5);

	double po=.051;
	double wallmod=int(wallcount)%10;
	if(Top)
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+1.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+1.05,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+1.05,1);
		glTexCoord3d(0,1,0);glVertex3d(i,j+1.05,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+.95,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+.95,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+.95,1);
		glTexCoord3d(0,1,0);glVertex3d(i,j+.95,1);
		glEnd();
		
		//end
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+1.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i,j+.95,0);
		glTexCoord3d(1,1,0);glVertex3d(i,j+.95,1);
		glTexCoord3d(0,1,0);glVertex3d(i,j+1.05,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+1,j+1.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+.95,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+.95,1);
		glTexCoord3d(0,1,0);glVertex3d(i+1,j+1.05,1);
		glEnd();


		//top
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+1,1);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+1,1);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+.9,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i,j+.9,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+1,1);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+1,1);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+1.1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i,j+1.1,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+.9,1.03);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+.9,1.03);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+1.1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i,j+1.1,1.03);
		glEnd();

		//wanted
		wallcount++;
		if(wallmod==0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);

			glTexCoord3d(0,0,0);glVertex3d(i+.0,j-po+1,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+.5,j-po+1,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+.5,j-po+1,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+.0,j-po+1,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.5,j-po+1,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+1,j-po+1,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+1,j-po+1,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+.5,j-po+1,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.0,j-po+1,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+.5,j-po+1,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+.5,j-po+1,1);
			glTexCoord3d(0,1,0);glVertex3d(i+.0,j-po+1,1);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.5,j-po+1,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+1,j-po+1,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+1,j-po+1,1);
			glTexCoord3d(0,1,0);glVertex3d(i+.5,j-po+1,1);
			glEnd();
		}
	}
	if(Right)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+.95,j,0);
		glTexCoord3d(1,0,0);glVertex3d(i+.95,j+1,0);
		glTexCoord3d(1,1,0);glVertex3d(i+.95,j+1,1);
		glTexCoord3d(0,1,0);glVertex3d(i+.95,j,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+1.05,j,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1.05,j+1,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1.05,j+1,1);
		glTexCoord3d(0,1,0);glVertex3d(i+1.05,j,1);
		glEnd();

		//ends
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+.95,j+1,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1.05,j+1,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1.05,j+1,1);
		glTexCoord3d(0,1,0);glVertex3d(i+.95,j+1,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+.95,j,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1.05,j,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1.05,j,1);
		glTexCoord3d(0,1,0);glVertex3d(i+.95,j,1);
		glEnd();

		//top

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+1,j,1);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+1,1);
		glTexCoord3d(1,1,0);glVertex3d(i+.9,j+1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i+.9,j,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+1,j,1);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+1,1);
		glTexCoord3d(1,1,0);glVertex3d(i+1.1,j+1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i+1.1,j,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+1.1,j,1.03);
		glTexCoord3d(1,0,0);glVertex3d(i+1.1,j+1,1.03);
		glTexCoord3d(1,1,0);glVertex3d(i+.9,j+1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i+.9,j,1.03);
		glEnd();

		//wanted
		wallcount++;
		if(wallmod==0)
		{

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po+.95,j+.0,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+po+.95,j+.5,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+po+.95,j+.5,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+po+.95,j+.0,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po+.95,j+.0,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+po+.95,j+.5,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+po+.95,j+.5,1);
			glTexCoord3d(0,1,0);glVertex3d(i+po+.95,j+.0,1);
			glEnd();


			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po+.95,j+.5,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+po+.95,j+1,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+po+.95,j+1,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+po+.95,j+.5,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po+.95,j+.5,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+po+.95,j+1,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+po+.95,j+1,1);
			glTexCoord3d(0,1,0);glVertex3d(i+po+.95,j+.5,1);
			glEnd();
		}

	}
	if(Bottom)
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+.05,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+.05,1);
		glTexCoord3d(0,1,0);glVertex3d(i,j+.05,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j-.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j-.05,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j-.05,1);
		glTexCoord3d(0,1,0);glVertex3d(i,j-.05,1);
		glEnd();

		//ends
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i,j-.05,0);
		glTexCoord3d(1,1,0);glVertex3d(i,j-.05,1);
		glTexCoord3d(0,1,0);glVertex3d(i,j+.05,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+1,j-.05,0);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+.05,0);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+.05,1);
		glTexCoord3d(0,1,0);glVertex3d(i+1,j-.05,1);
		glEnd();

		//top
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j,1);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j,1);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j+.1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i,j+.1,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j,1);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j,1);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j-.1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i,j-.1,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j+.1,1.03);
		glTexCoord3d(1,0,0);glVertex3d(i+1,j+.1,1.03);
		glTexCoord3d(1,1,0);glVertex3d(i+1,j-.1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i,j-.1,1.03);
		glEnd();

		//wanted
		wallcount++;
		if(wallmod==0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.0,j-po,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+.5,j-po,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+.5,j-po,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+.0,j-po,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.0,j-po,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+.5,j-po,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+.5,j-po,1);
			glTexCoord3d(0,1,0);glVertex3d(i+.0,j-po,1);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.5,j-po,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+1,j-po,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+1,j-po,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+.5,j-po,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+.5,j-po,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+1,j-po,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+1,j-po,1);
			glTexCoord3d(0,1,0);glVertex3d(i+.5,j-po,1);
			glEnd();
		}
	}
	if(Left)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+.05,j,0);
		glTexCoord3d(1,0,0);glVertex3d(i+.05,j+1,0);
		glTexCoord3d(1,1,0);glVertex3d(i+.05,j+1,1);
		glTexCoord3d(0,1,0);glVertex3d(i+.05,j,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i-.05,j,0);
		glTexCoord3d(1,0,0);glVertex3d(i+.05,j,0);
		glTexCoord3d(1,1,0);glVertex3d(i+.05,j,1);
		glTexCoord3d(0,1,0);glVertex3d(i-.05,j,1);
		glEnd();

		//ends
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+.05,j+1,0);
		glTexCoord3d(1,0,0);glVertex3d(i-.05,j+1,0);
		glTexCoord3d(1,1,0);glVertex3d(i-.05,j+1,1);
		glTexCoord3d(0,1,0);glVertex3d(i+.05,j+1,1);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname4);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i-.05,j,0);
		glTexCoord3d(1,0,0);glVertex3d(i-.05,j+1,0);
		glTexCoord3d(1,1,0);glVertex3d(i-.05,j+1,1);
		glTexCoord3d(0,1,0);glVertex3d(i-.05,j,1);
		glEnd();
		//top

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j,1);
		glTexCoord3d(1,0,0);glVertex3d(i,j+1,1);
		glTexCoord3d(1,1,0);glVertex3d(i+.1,j+1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i+.1,j,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i,j,1);
		glTexCoord3d(1,0,0);glVertex3d(i,j+1,1);
		glTexCoord3d(1,1,0);glVertex3d(i-.1,j+1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i-.1,j,1.03);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texname1);
		glBegin(GL_QUADS);
		glTexCoord3d(0,0,0);glVertex3d(i+.1,j,1.03);
		glTexCoord3d(1,0,0);glVertex3d(i+.1,j+1,1.03);
		glTexCoord3d(1,1,0);glVertex3d(i-.1,j+1,1.03);
		glTexCoord3d(0,1,0);glVertex3d(i-.1,j,1.03);
		glEnd();

		//wanted
		wallcount++;
		if(wallmod==0)
		{

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po,j+.0,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+po,j+.5,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+po,j+.5,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+po,j+.0,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po,j+.0,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+po,j+.5,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+po,j+.5,1);
			glTexCoord3d(0,1,0);glVertex3d(i+po,j+.0,1);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po,j+.5,.0);
			glTexCoord3d(1,0,0);glVertex3d(i+po,j+1,.0);
			glTexCoord3d(1,1,0);glVertex3d(i+po,j+1,.5);
			glTexCoord3d(0,1,0);glVertex3d(i+po,j+.5,.5);
			glEnd();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname3);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);
			glTexCoord3d(0,0,0);glVertex3d(i+po,j+.5,.5);
			glTexCoord3d(1,0,0);glVertex3d(i+po,j+1,.5);
			glTexCoord3d(1,1,0);glVertex3d(i+po,j+1,1);
			glTexCoord3d(0,1,0);glVertex3d(i+po,j+.5,1);
			glEnd();
		}
	}
	if(!Bottom && j==0)
	{
		if(i==M-1)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname2);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);

			glTexCoord3d(0,0,0);glVertex3d(i-.25,j-po,.25);
			glTexCoord3d(1,0,0);glVertex3d(i-.75,j-po,.25);
			glTexCoord3d(1,1,0);glVertex3d(i-.75,j-po,.75);
			glTexCoord3d(0,1,0);glVertex3d(i-.25,j-po,.75);

			glEnd();
		}
		else if(i>=0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname2);
			glBegin(GL_QUADS);
			glColor3d(.1,.9,.3);

			glTexCoord3d(0,0,0);glVertex3d(i+1.25,j-po,.25);
			glTexCoord3d(1,0,0);glVertex3d(i+1.75,j-po,.25);
			glTexCoord3d(1,1,0);glVertex3d(i+1.75,j-po,.75);
			glTexCoord3d(0,1,0);glVertex3d(i+1.25,j-po,.75);
			glEnd();
		}
	}
}

bool Maze::IsSafe(double x, double y, double ratwidth, double ratlength)
{
	int cellx=int(x);
	int celly=int(y);
	double offsetx=x-cellx;
	double offsety=y-celly;

	
	//if(cellx<0 || cellx>M-1 || celly<0 || celly>N-1)
	//{
		//return false;
	//}
	//for sides
	//for bottom wall
	if(offsety-ratlength<0 && Cells[cellx][celly].Bottom)
	{
		return false;
	}
	//for top wall
	if(offsety+ratlength>cellsize && Cells[cellx][celly].Top)
	{
		return false;
	}
	//for left wall
	if(offsetx-ratlength<0 && Cells[cellx][celly].Left)
	{
		return false;
	}
	//for right wall
	if(offsetx+ratlength>cellsize && Cells[cellx][celly].Right)
	{
		return false;
	}

	//for corners
	//bottom left corner
	if(offsetx-ratlength<0 && offsety-ratlength<0)//this one was coded by teacher, don't touch.
	{
		return false;
	}
	//bottom right
	if(offsetx+ratlength>cellsize && offsety-ratlength<0)
	{
		return false;
	}
	//top left
	if(offsetx-ratlength<0 && offsety+ratlength>cellsize)
	{
		return false;
	}
	//top right
	if(offsetx+ratlength>cellsize && offsety+ratlength>cellsize)
	{
		return false;
	}
	else
	{
		return true;
	}
}

double Maze::GetStartX()
{
	return startx;
}
void Maze::Create()
{
	CreateRecursive(0,0);

	//knock out a random bottom wall
	int starti=rand()%M;
	int startj=0;
	Cells[starti][startj].Bottom=false;
	startx=starti;

	//knock out a random top wall
	starti=rand()%M;
	startj=N-1;
	Cells[starti][startj].Top=false;
}

void Maze::Draw(double texname1,double texname2, double texname3, double texname4)
{
	for (int i=0;i<M;i++)
	{
		for (int j=0;j<N;j++)
		{
			if (topview==true)
			{
				Cells[i][j].Draw2d(i,j);
			}
			else
			{	
				Cells[i][j].Draw3d(i,j,texname1,texname2, texname3, texname4);
			}
		}
	}
}

void Maze::CreateRecursive(int i,int j)
{
	Cells[i][j].Visited=true;
	//sets cell as true
	while (true)
	{
		//see which neighbor cells are an option
		int Nexti[4];
		int Nextj[4];
		int NextCount=0;

		//check if we can go up
		if(j<N-1 && !Cells[i][j+1].Visited)
		{
			Nexti[NextCount]=i;
			Nextj[NextCount]=j+1;
			NextCount++;
		}

		//check if we can go down
		if(j>0 && !Cells[i][j-1].Visited)
		{
			Nexti[NextCount]=i;
			Nextj[NextCount]=j-1;
			NextCount++;
		}

		//check if we can go right
		if(i<M-1 && !Cells[i+1][j].Visited)
		{
			Nexti[NextCount]=i+1;
			Nextj[NextCount]=j;
			NextCount++;
		}

		//check if we can go left
		if(i>0 && !Cells[i-1][j].Visited)
		{
			Nexti[NextCount]=i-1;
			Nextj[NextCount]=j;
			NextCount++;
		}

		if(NextCount==0)
		{
			return;
		}
		int r = rand()% NextCount;

		//Knocks Out Walls
		int x=Nexti[r];
		int y=Nextj[r];
		//move down
		if (y==j-1)
		{
			Cells[i][j].Bottom=false;
			Cells[x][y].Top=false;
		}
		//move right
		if (x==i+1)
		{
			Cells[i][j].Right=false;
			Cells[x][y].Left=false;
		}
		//move up
		if (y==j+1)
		{
			Cells[i][j].Top=false;
			Cells[x][y].Bottom=false;
		}
		//move left
		if (x==i-1)
		{
			Cells[i][j].Left=false;
			Cells[x][y].Right=false;
		}
		CreateRecursive(x,y);
	}
}
