#ifndef _EEBMODEL_H_
#define _EEBMODEL_H_
#include <iostream>
#include <map>
#include <list>

namespace eeb
{
	/* these values are used for index into an array.* DON'T CHANGE THEM!*/
	enum {I_MIN=-1,I_CLIFF=0,I_MUD=1,I_PLAIN=2,I_ROCKS=3,I_WALL=4,I_ICE=5,I_MAX=6,I_OUT_OF_BOUNDS};
	enum {D_MIN=-1,D_NORTH=0,D_SOUTH=1,D_EAST=2,D_WEST=3,D_MAX=4,D_OUT_OF_BOUNDS};
	
	struct Point
	{
		int x;
		int y;
	};
	
	class Cell
	{
	public:
		Cell();
		Cell(const Cell &rhs);
		Cell(const double &x,const double &y,const double &z, 
			const int &north,const int &south,const int &east,const int &west);
		Cell(const double &x,const double &y);
		~Cell();
		
		
		static const Cell None();
		
		
		Cell &operator=(const Cell &rhs);
		bool operator==(const Cell &rhs)const;
		double getx()const;
		double gety()const;
		double getz()const;
		int getnorth()const;
		int getsouth()const;
		int geteast()const;
		int getwest()const;
		
		bool setx(const int &xin);
		bool sety(const int &yin);
		bool setz(const int &zin);
		bool setnorth(const int &northin);
		bool setsouth(const int &southin);
		bool seteast(const int &eastin);
		bool setwest(const int &westin);
		
		bool getvisited()const;
		bool setvisited(const bool &v);
		
		bool getlooked()const;
		bool setlooked(const bool &v);
		
		bool getexamined()const;
		bool setexamined(const bool &ex);
		
		int GetTerrain(const int &direction)const;
		bool SetTerrain(int dir, int terr);
		static int TerrainLabelToEnum(const char *s);
		static const char *TerrainEnumToLabel(const int &i);
		bool display(std::ostream &os)const;
	  
	protected:
		bool visited;
		bool looked;
		bool examined;
		double x,y,z;/* position of center of cell */
		int north,south,east,west;
		int terrain[4];/* one for each direction */
	};
	std::ostream &operator<<(std::ostream &os, const Cell &rhs);

	class Model
	{
	public:
		Model();
		~Model();
		//get
		double getcharge()const;
		double gethp()const;
		double getcurx()const;
		double getcury()const;
		double getcurz()const;
		double getendx()const;
		double getendy()const;
		double getendz()const;
		//set
		bool setcharge(const double &vin);
		bool sethp(const double &vin);
		bool setcurx(const double &vin);
		bool setcury(const double &vin);
		bool setcurz(const double &vin);
		bool setendx(const double &vin);
		bool setendy(const double &vin);
		bool setendz(const double &vin);

		int getcurnorth()const;
		int getcursouth()const;
		int getcureast()const;
		int getcurwest()const;
		bool setcurnorth(const int &curnorthin);
		bool setcursouth(const int &cursouthin);
		bool setcureast(const int &cureastin);
		bool setcurwest(const int &curwestin);
		
		bool getvisited()const;
		bool setvisited(const bool &v);
		
		bool getlooked()const;
		bool setlooked(const bool &v);
		
		bool getexamined()const;
		bool setexamined(const bool &ex);
		
		bool addcell(const Cell &cell);
		bool addgoal(const Cell &cell);
		Cell getcell(const double &x,const double &y)const;
		Cell getgoal(const double &x,const double &y)const;
		Cell &getcell(const double &x,const double &y);
		Cell &getgoal(const double &x,const double &y);
		bool display(std::ostream &os)const;
		
		bool setlastlooked(int dir);
		int getlastlooked();
		
		std::map<int, Cell> world;
		std::map<int, Cell> goals;
		
		std::list<Point> goalpointlist;
		
		
		int CellToKey(const Cell &cell)const;
		int PositionToKey(const double &x, const double &y)const;
	protected:
		double curx,cury,curz;
		double endx,endy,endz;
		double charge,hp;
		int curnorth,cursouth,cureast,curwest;
		bool visited;
		bool looked;
		bool examined;
		int lastlooked;
	};
	std::ostream &operator<<(std::ostream &os, const Model &rhs);
};
#endif
