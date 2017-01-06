#include "eebmodel.h"
#include <cstring>
#include <cmath>

namespace eeb
{
	Cell::Cell()
	{
		this->x=1;
		this->y=1,
	}
	Cell::~Cell(){}
	double Cell::getx()const{return this->x;}
	double Cell::gety()const{return this->y;}
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
	bool Cell::display(std::ostream &os)const
	{
		int i;
		os<<this->x<<","<<this->y<<" ";
		return true;
	}
	std::ostream &operator<<(std::ostream &os,const Cell &rhs)
	{
		rhs.display(os);
		return os;
	}
	
	Model::Model()
		: curx(1),cury(1) {/* empty */}
	Model::~Model(){/* empty */}
	double Model::getcharge()const{return this->charge;}
	double Model::gethp()const{return this->hp;}
	double Model::getcurx()const{return this->curx;}
	double Model::getcury()const{return this->cury;}
	double Model::getendx()const{return this->endx;}
	double Model::getendy()const{return this->endy;}
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
	bool Model::display(std::ostream &os)const
	{
		os<<"Position: "<<this->curx<<","<<this->cury<<std::endl;
		os<<"Goal: "<<this->endx<<","<<this->endy<<","<<this->endz<<std::endl;
		std::map<int,Cell>::const_iterator it;
		for(it=this->world.begin();it!=this->world.end();it++){os<<it->second<<std::endl;}
		return true;
	}
	std::ostream &operator<<(std::ostream &os,const Model &rhs)
	{
		rhs.display(os);
		return os;
	}

};
