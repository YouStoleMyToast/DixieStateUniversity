#include "eebstate.h"
#include <iostream>
#include <cmath>

namespace eeb
{
	State::State(){/*empty*/}
	State::State(const State &rhs){*this=rhs;}
	State::~State(){/*empty*/}
	State &State::operator=(const State &rhs)
	{
		this->x=rhs.x;
		this->y=rhs.y;
		this->z=rhs.z;
		this->charge=rhs.charge;
		this->hp=rhs.hp;
		return *this;
	}
	bool State::operator==(const State &rhs)const
	{ /* only compare based on grid position for now */
		double epsilon=0.1;
		double dx=std::fabs(this->x-rhs.x);
		double dy=std::fabs(this->y-rhs.y);
		return (dx<epsilon && dy<epsilon);
	}
	void State::Display()const
	{
		this->display(std::cout);
		std::cout<<std::endl;
	}
	bool State::IsEqual(const ai::Search::State * const state_in)const
	{
		const State * const state=dynamic_cast<const State * const>(state_in);
		return (*this)==(*state);
	}
	double State::getx()const {return this->x;}
	double State::gety()const {return this->y;}
	double State::getz()const {return this->z;}
	double State::getcharge()const {return this->charge;}
	double State::gethp()const {return this->hp;}
	bool State::setx(const double &xin)
	{
		this->x=xin;
		return true;
	}
	bool State::sety(const double &yin)
	{
		this->y=yin;
		return true;
	}
	bool State::setz(const double &zin)
	{
		this->z=zin;
		return true;
	}
	bool State::setcharge(const double &chargein)
	{
		this->charge=chargein;
		return true;
	}
	bool State::sethp(const double &hpin)
	{
		this->hp=hpin;
		return true;
	}
	bool State::display(std::ostream &os)const
	{
		os<<"Pos: "<<this->x<<","<<this->y<<","<<this->z<<" "<<"Chg: "<<this->charge<<" "<<"HP: "<<this->hp;
		return true;
	}
	std::ostream &operator<<(std::ostream &os, const State &rhs)
	{
		rhs.display(os);
		return os;
	}
};
