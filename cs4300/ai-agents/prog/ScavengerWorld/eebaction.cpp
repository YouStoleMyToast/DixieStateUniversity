#include "eebaction.h"
#include <iostream>
#include <cstring>

namespace eeb
{
	static const char *actionlabels[]={"go_north","go_south","go_east","go_west","max","LOOK","RECHARGE","error"};
	Action::Action() : type(A_MIN) {/* empty */}
	Action::Action(const Action &rhs){*this=rhs;}
	Action::~Action() {/* empty */}
	Action &Action::operator=(const Action &rhs)
	{
		this->type=rhs.type;
		return *this;
	}
	bool Action::operator==(const Action &rhs)const{return(this->type==rhs.type);}
	void Action::display()const
	{
		this->display(std::cout);
		std::cout << std::endl;
	}
	bool Action::settype(int typein)
	{
		if(typein>A_MIN && typein<A_OUT_OF_BOUNDS)
		{
			this->type=typein;
			return true;
		}
		return false;
	}
	int Action::gettype()const{return this->type;}
	int Action::LabelToEnum(const char *s)
	{
		int i;
		for(i=1+(int)A_MIN;i<(int)A_OUT_OF_BOUNDS;i++) 
		{
			if(std::strcmp(s, actionlabels[i])==0) 
			{return i;}
		}
		return A_OUT_OF_BOUNDS;
	}
	const char *Action::EnumToLabel(const int &i)
	{
		//if(i<=(int)A_MIN || i>=(int)A_MAX) 
		if(i<=(int)A_MIN || i>=(int)A_OUT_OF_BOUNDS) 
		{return actionlabels[A_MAX];}
		return actionlabels[i];
	}
	bool Action::display(std::ostream &os)const
	{
		os<<Action::EnumToLabel(this->type);{return true;}
	}
	std::ostream &operator<<(std::ostream &os, const Action &rhs)
	{
		rhs.display(os);{return os;}
	}
};
