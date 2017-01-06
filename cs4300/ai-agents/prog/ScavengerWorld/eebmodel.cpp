#include "eebmodel.h"
#include <cstring>
#include <cmath>

namespace eeb
{
	static const char *terrainlabels[]={"cliff","mud","plain","rocks","wall","ice","error"};
	Cell::Cell()
	{
		this->x=0.;
		this->y=0.,
		this->z=0.,
		this->terrain[0]=I_OUT_OF_BOUNDS;
		this->terrain[1]=I_OUT_OF_BOUNDS;
		this->terrain[2]=I_OUT_OF_BOUNDS;
		this->terrain[3]=I_OUT_OF_BOUNDS;
		this->visited=false;
		this->looked=false;
		this->examined=false;
	}
	Cell::Cell(const Cell &rhs){*this=rhs;}
	Cell::Cell(const double &x,const double &y,const double &z,const int &north,const int &south,const int &east,const int &west)
		: x(x),y(y),z(z)
	{
		this->terrain[0]=north;
		this->terrain[1]=south;
		this->terrain[2]=east;
		this->terrain[3]=west;
		this->visited=false;
		this->looked=false;
		this->examined=false;
	}
	Cell::Cell(const double &x,const double &y)
		: x(x),y(y)
	{
		this->z=0;
		this->terrain[0]=I_OUT_OF_BOUNDS;
		this->terrain[1]=I_OUT_OF_BOUNDS;
		this->terrain[2]=I_OUT_OF_BOUNDS;
		this->terrain[3]=I_OUT_OF_BOUNDS;
		this->visited=false;
		this->looked=false;
		this->examined=false;
	}
	Cell::~Cell(){}
	Cell &Cell::operator=(const Cell &rhs)
	{
		int i;
		this->x=rhs.x;
		this->y=rhs.y;
		this->z=rhs.z;
		for(i=1+(int)D_MIN;i<(int)D_MAX;i++) {this->terrain[i]=rhs.terrain[i];}
		this->visited=false;
		this->looked=false;
		return *this;
	}
	bool Cell::operator==(const Cell &rhs)const
	{
		double epsilon=0.1;
		double dx=std::fabs(this->x-rhs.x);
		double dy=std::fabs(this->y-rhs.y);
		double dz=std::fabs(this->z-rhs.z);
		bool isame=true;
		int i;
		for(i=1+(int)D_MIN;i<(int)D_MAX;i++){isame &=(this->terrain[i]==rhs.terrain[i]);}
		return (dx<epsilon && dy<epsilon && dz<epsilon && isame);
	}
	
	const Cell Cell::None(){return Cell(0.,0.,0.,I_OUT_OF_BOUNDS,I_OUT_OF_BOUNDS,I_OUT_OF_BOUNDS,I_OUT_OF_BOUNDS);}
	
	
	
	double Cell::getx()const{return this->x;}
	double Cell::gety()const{return this->y;}
	double Cell::getz()const{return this->z;}
	int Cell::getnorth()const{return this->north;}
	int Cell::getsouth()const{return this->south;}
	int Cell::geteast()const{return this->east;}
	int Cell::getwest()const{return this->west;}
	bool Cell::getvisited()const{return this->visited;}
	bool Cell::getlooked()const{return this->looked;}
	bool Cell::setx(const int &xin)
	{
		this->x=xin;
		return true;
	}
	bool Cell::sety(const int &yin)
	{
		this->y=yin;
		return true;
	}
	bool Cell::setz(const int &zin)
	{
		this->z=zin;
		return true;
	}
	bool Cell::setnorth(const int &northin)
	{
		this->north=northin;
		this->terrain[0]=northin;
		return true;
	}
	bool Cell::setsouth(const int &southin)
	{
		this->south=southin;
		this->terrain[1]=southin;
		return true;
	}
	bool Cell::seteast(const int &eastin)
	{
		this->east=eastin;
		this->terrain[2]=eastin;
		return true;
	}
	bool Cell::setwest(const int &westin)
	{
		this->west=westin;
		this->terrain[3]=westin;
		return true;
	}
	bool Cell::setvisited(const bool &vis)
	{
		this->visited=vis;
		return true;
	}
	bool Cell::setlooked(const bool &vis)
	{
		this->looked=vis;
		return true;
	}
	bool Cell::getexamined()const{return this->examined;}
	bool Cell::setexamined(const bool &ex)
	{
		this->examined=ex;
		return true;
	}
	int Cell::GetTerrain(const int &direction)const
	{
		if(direction<=D_MIN||direction>=D_MAX)
		{return I_OUT_OF_BOUNDS;}
		return this->terrain[direction];
	}
	bool Cell::SetTerrain(int dir, int terr)
	{
		this->terrain[dir]=terr;
		return true;
	}
	int Cell::TerrainLabelToEnum(const char *s)
	{
		int i;
		for(i=1+(int)I_MIN;i<(int)I_MAX;i++)
		{
			if(std::strcmp(s,terrainlabels[i])==0) 
			{return i;}
	    }
		return I_OUT_OF_BOUNDS;
	}
	const char *Cell::TerrainEnumToLabel(const int &i)
	{
		if(i<=(int)I_MIN || i>=(int)I_MAX) 
		{return terrainlabels[I_MAX];}
		return terrainlabels[i];
	}
	bool Cell::display(std::ostream &os)const
	{
		int i;
		os<<this->x<<","<<this->y<<","<<this->z<<" ";
		for(i=1+(int)D_MIN;i<(int)D_MAX;i++)
		{
			if(i>1+(int)D_MIN) 
			{os<<",";}
			os<<Cell::TerrainEnumToLabel(this->terrain[i]);
		}
		return true;
	}
	std::ostream &operator<<(std::ostream &os,const Cell &rhs)
	{
		rhs.display(os);
		return os;
	}
	
	
	
	Model::Model()
		: curx(0.),cury(0.),curz(0.),endx(0.),endy(0.),endz(0.),charge(0.),hp(0.){/* empty */}
	Model::~Model(){/* empty */}
	double Model::getcharge()const{return this->charge;}
	double Model::gethp()const{return this->hp;}
	double Model::getcurx()const{return this->curx;}
	double Model::getcury()const{return this->cury;}
	double Model::getcurz()const{return this->curz;}
	double Model::getendx()const{return this->endx;}
	double Model::getendy()const{return this->endy;}
	double Model::getendz()const{return this->endz;}
	int Model::getcurnorth()const{return this->curnorth;}
	int Model::getcursouth()const{return this->cursouth;}
	int Model::getcureast()const{return this->cureast;}
	int Model::getcurwest()const{return this->curwest;}
	bool Model::setcharge(const double &chargein)
	{
		this->charge=chargein;
		return true;
	}
	bool Model::sethp(const double &hpin)
	{
		this->hp=hpin;
		return true;
	}
	bool Model::setcurx(const double &xin)
	{
		this->curx=xin;
		return true;
	}
	bool Model::setcury(const double &yin)
	{
		this->cury=yin;
		return true;
	}
	bool Model::setcurz(const double &zin)
	{
		this->curz=zin;
		return true;
	}
	bool Model::setendx(const double &xin)
	{
		this->endx=xin;
		return true;
	}
	bool Model::setendy(const double &yin)
	{
		this->endy=yin;
		return true;
	}
	bool Model::setendz(const double &zin)
	{
		this->endz=zin;
		return true;
	}
	bool Model::setcurnorth(const int &curnorthin)
	{
		this->curnorth=curnorthin;
		return true;
	}
	bool Model::setcursouth(const int &cursouthin)
	{
		this->cursouth=cursouthin;
		return true;
	}
	bool Model::setcureast(const int &cureastin)
	{
		this->cureast=cureastin;
		return true;
	}
	bool Model::setcurwest(const int &curwestin)
	{
		this->curwest=curwestin;
		return true;
	}
	bool Model::getvisited()const{return this->visited;}
	bool Model::setvisited(const bool &vis)
	{
		this->visited=vis;
		return true;
	}
	bool Model::getlooked()const{return this->looked;}
	bool Model::setlooked(const bool &vis)
	{
		this->looked=vis;
		return true;
	}
	bool Model::getexamined()const{return this->examined;}
	bool Model::setexamined(const bool &ex)
	{
		this->examined=ex;
		return true;
	}
	int Model::getlastlooked(){return this->lastlooked;}
	bool Model::setlastlooked(int dir)
	{
		this->lastlooked=dir;
		return true;
	}
	bool Model::addcell(const Cell &cell)
	{
		int key = this->CellToKey(cell);
		std::map<int, Cell>::const_iterator it;
		it = this->world.find(key);
		if(it != this->world.end()){return false;}
		this->world[key]=cell;
		return true;
	}
	bool Model::addgoal(const Cell &cell)
	{
		int key=this->CellToKey(cell);
		std::map<int,Cell>::const_iterator it;
		it=this->goals.find(key);
		if(it!=this->goals.end()){return false;}
		this->goals[key]=cell;
		return true;
	}
	Cell &Model::getcell(const double &x,const double &y)
	{
		int key=this->PositionToKey(x,y);
		std::map<int,Cell>::iterator it;
		it=this->world.find(key);
		Cell newcell=Cell();
		if(it==this->world.end())
		{
			std::cout<<"invalid cell"<<std::endl;
			return newcell;
		}
		return it->second;
	}
	Cell &Model::getgoal(const double &x,const double &y)
	{
		int key=this->PositionToKey(x,y);
		std::map<int,Cell>::iterator it;
		it=this->goals.find(key);
		Cell newcell=Cell();
		if(it==this->goals.end()){return newcell;}
		return it->second;
	}
	bool Model::display(std::ostream &os)const
	{
		os<<"Position: "<<this->curx<<","<<this->cury<<","<<this->curz<<std::endl;
		os<<"Charge: "<<this->charge<<" HP: "<<this->hp<<std::endl;
		os<<"Goal: "<<this->endx<<","<<this->endy<<","<<this->endz<<std::endl;
		std::map<int,Cell>::const_iterator it;
		for(it=this->world.begin();it!=this->world.end();it++){os<<it->second<<std::endl;}
		return true;
	}
	int Model::CellToKey(const Cell &cell)const{return this->PositionToKey(cell.getx(),cell.gety());}
	int Model::PositionToKey(const double &xin,const double &yin)const
	{
		int size=1000;
		int offset=100;
		int width=offset*2;
		int x=(xin/size)+offset;
		int y=(yin/size)+offset;
		int key=y*width+x;
		return key;
	}
	std::ostream &operator<<(std::ostream &os,const Model &rhs)
	{
		rhs.display(os);
		return os;
	}
};

