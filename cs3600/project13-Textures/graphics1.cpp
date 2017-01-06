//Writen by Eric Beilmann
//with a lot of help from Professor Bart Stander
//CS 3600
//Spring 2013

// This project shows how to import a .tga file and use it as a texture map.

//load pictures into photoshop
//save as tga file 24 bit and uncompressed

#include <cmath>
#include <cstring>
#include <ctype.h>
#include <conio.h>
#include <iostream>
using namespace std;
#include "graphics.h"
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include "Maze.h"
#include "glut.h"
#include "Perry.h"

// tga image loader code.
#include "tga.h"

// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;

bool leftbuttondown=false;
bool middlebuttondown=false;
bool rightbuttondown=false;
bool topview=false;
bool sideview=true;
bool personview=false;

Maze amazing;
Rat perry;

// Textures
const int num_textures = 6;
static GLuint texName[num_textures];
GLuint tex_2d=0;

gliGenericImage *readTgaImage(char *filename)
{
  FILE *file;
  gliGenericImage *image;

  file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error: could not open \"%s\"\n", filename);
    return NULL;
  }
  image = gliReadTGA(file, filename);
  fclose(file);
  if (image == NULL) {
    printf("Error: could not decode file format of \"%s\"\n", filename);
    return NULL;
  }
  return image;
}

// Generic image loader code.
gliGenericImage *readImage(char *filename)
{
	size_t size = strlen(filename);
	if(toupper(filename[size-3]) == 'T' && toupper(filename[size-2]) == 'G' && toupper(filename[size-1]) == 'A')
	{
		gliGenericImage * result = readTgaImage(filename);
		if(!result)
		{
			cerr << "Error opening " << filename << endl;
			_getch();
			exit(1);
		}
		return result;
	}
	else
	{
		cerr << "Unknown Filetype!\n";
		_getch();
		exit(1);
	}
}

// This resets the edges of the texture image to a given "border color".
// You must call this for clamped images that do not take up the whole polygon.
// Otherwise, the texture edges will smear outward across the rest
// of the polygon.
void SetBorder(gliGenericImage * image)
{
	// set a border color.
	unsigned int border_r=50;
	unsigned int border_g=50;
	unsigned int border_b=255;
	int x,y;
	y=0;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	y=1;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	y=image->height-1;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	y=image->height-2;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}

	x=0;
	for(y=0; y<image->height; y++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	x=1;
	for(y=0; y<image->height; y++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	x=image->width-1;
	for(y=0; y<image->height; y++)
	{
		int index = 3*(y*image->width + x);
		image->pixels[ index + 0]=border_r;
		image->pixels[ index + 1]=border_g;
		image->pixels[ index + 2]=border_b;
	}
	x=image->width-2;
	for(y=0; y<image->height; y++)
	{
		int index = 3*(y*image->width + x);
		image->pixels[ index + 0]=border_r;
		image->pixels[ index + 1]=border_g;
		image->pixels[ index + 2]=border_b;
	}
}

//maze code
double getdeltatime()
{
	static clock_t starttime=clock();//built in function clock() problem default is 17 clicks a second while we need about 100 so we made changes
	static int currentframe=0;
	clock_t currenttime=clock();
	currentframe+=1;
	double totaltime=double(currenttime-starttime)/CLOCKS_PER_SEC;//CLOCKS_PER_SEC is a built in function
	if (totaltime==0)//prevents dividing by zero
	{
		totaltime=.0001;
	}
	double framespersecond=(double)currentframe/totaltime;
	double DT=1.0/framespersecond;
	return DT;
}
double field_of_view=50;//orig=60
double aspect_ratio=(double)screen_x/screen_y;
double zNear=2;//orig=2
double zFar=(M+N)*2;//orig=(M+N)*2

//be sure to offset some angles so that all sides have depth
double eyex=-M*.2;//orig=M/4
double eyey=-N*.2;//orig=N/4
double eyez=M*.7;//orig=M
//where the eye will be focused - the center of the maze in this case
double atx=M/2;
double aty=N/2;
double atz=0;
//sets the up direction
double upx=0;
double upy=0;
double upz=1;//orig=1

double povfield_of_view=60;
double povaspect_ratio=(double)screen_x/screen_y;
double povzNear=0.1;
double povzFar=(M+N)*2;





//end maze code(except the staples)
//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	//new
	//double eye[3] = {5, -1, 11}; // pick a nice vantage point.
	//double at[3]  = {5, 3, 0};

	//gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,0,1); // Z is up!

	// Draw quads with texture

	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[0]);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2d(0,0);//anchers botom left corner of image to bottom
	glTexCoord2f(1,0); glVertex2d(10,0);
	glTexCoord2f(1,1); glVertex2d(10,6);
	glTexCoord2f(0,1); glVertex2d(0,6);
	glEnd();
	*/
	//options: you can attach the image to the tile any way you want to a tile
	//originally (0,0)(1,0)(1,1)(0,1) to cover whole tile
	//can smear if use_border is set to false

	//repeat 3 times
	//pass in values to tile 0,0 to 3,0 then set the three picture origins to 0,0 1,0 2,0
	//end new
	double DT=getdeltatime();
	double X=perry.GetX();
	double Y=perry.GetY();
	double Degrees=perry.GetDegrees();

	double theta = (double)Degrees/180.0 * 3.1415926;
	double dx = cos(theta);
	double dy = sin(theta);
	double nextx=X+dx*cells_per_second*DT;
	double nexty=Y+dy*cells_per_second*DT;
	//be sure to offset some angles so that all sides have depth
	double poveyex=perry.GetX();
	double poveyey=perry.GetY();
	double poveyez=.2;
	//where the eye will be focused
	double povatx=nextx;
	double povaty=nexty;
	double povatz=.2;
	//sets the up direction
	double povupx=0;
	double povupy=0;
	double povupz=1;
	//printf("startx %f \n",amazing.GetStartX());
	//printf("perry.GetX() %f \n",perry.GetX());
	//printf("perry.GetY() %f \n",perry.GetY());
	double field_of_view=60;//in degrees//orig=60
	double aspect_ratio=(double)screen_x/screen_y;
	double zNear=2;//tells opengl the min of the depth possible
	double zFar=(M+N)*2;//tells opengl the max of the depth possible//orig =(M+N)*2
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (topview==true)
	{
		gluOrtho2D(-.5, M+.5, -.5, N+.5);//orig just .5
	}
	// Set the projection mode to 3D orthographic, and set the world coordinates:
	else if (sideview==true)
	{
		gluPerspective(field_of_view, aspect_ratio, zNear, zFar);
	}
	else if(personview==true)
	{
		gluPerspective(field_of_view, aspect_ratio, povzNear, zFar);//povfield_of_view, povaspect_ratio, povzNear, povzFar
	}
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	if (sideview==true)
	{
		gluLookAt(eyex,eyey,eyez,atx,aty,atz,upx,upy,upz);//specify the observer/camera/eye
	}
	else if(personview==true)
	{
		gluLookAt(poveyex,poveyey,poveyez,povatx,povaty,povatz,povupx,povupy,povupz);
	}
	if (leftbuttondown)
	{
		perry.Spinleft(DT);
	}
	if (rightbuttondown)
	{
		perry.Spinright(DT);
	}
	if (middlebuttondown)
	{
		perry.Moveforeward(amazing,DT, topview);
	}
	amazing.DrawTable(M,N,tex_2d);
	amazing.Drawfloor(texName[1]);
	amazing.Draw(texName[1],texName[3], texName[4], texName[5]);
	amazing.DrawTree(M+.5,0-.5,texName[2]);
	amazing.DrawSphere(M+.5, 0-.5, 1.9, .7,texName[0]);
	glDisable(GL_TEXTURE_2D);
	if (personview==false)
	{
		perry.Draw(amazing, DT, perry.moving, topview);
	}
	else
	{
		perry.DrawBill(amazing, DT, perry.moving);
	}
	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	if(c==27) // escape character means to quit the program
	{
		exit(0);
	}
	else if(c=='t')
	{
		topview=true;
		amazing.topview=true;
		sideview=false;
		personview=false;
	}
	else if(c=='p')
	{
		topview=false;
		amazing.topview=false;
		sideview=true;
		personview=false;
	}
	else if(c=='r')
	{
		topview=false;
		amazing.topview=false;
		sideview=false;
		personview=true;
	}
	else
	{
		return; // if we don't care, return without glutPostRedisplay()
	}
	glutPostRedisplay();
}

//in 2d
void setOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-.5, M+.5, -.5, N+.5);//orig just .5
	glMatrixMode(GL_MODELVIEW);
}
void setPerspectiveProjection(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (double) w/(double) h;
	double zFar=(M+N)*2;
	gluPerspective( 
	/* field of view in degree */ 60,//original 38.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ 2,//original 1 
	/* Z far */ zFar);//original 1000
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	if (topview==true && sideview==false)
	{
		setOrthographicProjection();
	}

	// Set the projection mode to 3D orthographic, and set the world coordinates:
	else if (sideview==true && topview==false)
	{
		setPerspectiveProjection(w, h);
	}
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		leftbuttondown=true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		leftbuttondown=false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
		middlebuttondown=true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
		middlebuttondown=false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
	{
		rightbuttondown=true;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
	{
		rightbuttondown=false;
	}
	if (rightbuttondown==true || middlebuttondown==true || leftbuttondown==true)
	{
		perry.moving=true;
	}
	else if (rightbuttondown==false && middlebuttondown==false && leftbuttondown==false)
	{
		perry.moving=false;
	}
	glutPostRedisplay();
}

// Return true if h is a perfect power of 2 (up to 4096)
bool PowerOf2(int h)
{
	if(h!= 2 && h!=4 && h!=8 && h!=16 && h!=32 && h!=64 && h!=128 && 
				h!=256 && h!=512 && h!=1024 && h!=2048 && h!=4096)
		return false;
	else
		return true;
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	amazing.Create();
	perry.Initialize(amazing);

	gliGenericImage *image[num_textures];//array of 4 pointers to the image format
	int n=0;

	//at least three pictures used for assignment
	//image[n++] = readImage("fruit.tga");//dynamicly allocates memmory for pictures
	//image[n++] = readImage("sky.tga");
	//image[n++] = readImage("cookies.tga");
	//image[n++] = readImage("Seattle.tga");
	image[n++] = readImage("grass.tga");
	image[n++] = readImage("stonefloor.tga");
	image[n++] = readImage("treebark2.tga");
	image[n++] = readImage("mm.tga");
	image[n++] = readImage("doofwanted.tga");
	image[n++] = readImage("brick2.tga");

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	if(n!=num_textures)
	{
		printf("Error: Wrong number of textures\n");
		_getch();
		exit(1);;
	}

	glGenTextures(num_textures, texName);//makes sure numbers for pictures are not being used before assigning them

	for(int i=0; i<num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);//gets texture number i all following only affect this picture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//different options(decal, modulate, and blend)
		int repeats = false;
		int needs_border = false; // Needed if clamping and not filling the whole polygon. For images that don't take up whole sqare
		if(repeats)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//wrapping in s and t direction set to repeat
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		}
		if(needs_border)
		{
			// set a border.
			SetBorder(image[i]);//overwrites edge pixels
		}

		bool mipmaps = false;
		if(!PowerOf2(image[i]->height) || !PowerOf2(image[i]->width))
		{
			// WARNING: Images that do not have width and height as 
			// powers of 2 MUST use mipmaps.
			mipmaps = true; 
		}

		if (mipmaps) //multi-dimensional image map: will create images of varriouse sizes(bit dimensions 2^x)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, image[i]->components,
					image[i]->width, image[i]->height,
					image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					//GL_LINEAR_MIPMAP_LINEAR);//does both mimap and linear
					GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					//GL_LINEAR);
					GL_NEAREST);
		} 
		else 
		{
			//non-mimaps
			//example 400x400 picture on a 10 pixel section of screen
			//revers transfer: divide each picture edge by ten then use pixel at location of intersect
			//another way: average of values in aan area

			//small image to large screen area: add to each pixel surrounding pixels that average colors of surrounding pixels
			glTexImage2D(GL_TEXTURE_2D, 0, image[i]->components,
					image[i]->width, image[i]->height, 0,
					image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//linear option is better looking but not fastest
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
}


int main(int argc, char **argv)
{
	srand(time(0));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("Textures Demo");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0,0,0); // forground color
	glClearColor(.1, .7, .9, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
