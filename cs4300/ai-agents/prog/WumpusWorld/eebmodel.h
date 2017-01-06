#ifndef _EEBMODEL_H_
#define _EEBMODEL_H_
#include <iostream>
#include <map>

namespace eeb
{
	class Cell
	{
	public:
		Cell();
		~Cell();
		int getx()const;
		int gety()const;
		bool setx(const int &xin);
		bool sety(const int &yin);
		bool display(std::ostream &os)const;
	protected:
		int x,y;
	};
	std::ostream &operator<<(std::ostream &os, const Cell &rhs);
	class Model
	{
	public:
		Model();
		~Model();
		//get
		double getcurx()const;
		double getcury()const;
		double getendx()const;
		double getendy()const;
		//set
		bool setcurx(const double &vin);
		bool setcury(const double &vin);
		bool setendx(const double &vin);
		bool setendy(const double &vin);
		bool display(std::ostream &os)const;
	protected:
		double curx,cury;
		double endx,endy;
	};
	std::ostream &operator<<(std::ostream &os, const Model &rhs);
};
#endif
