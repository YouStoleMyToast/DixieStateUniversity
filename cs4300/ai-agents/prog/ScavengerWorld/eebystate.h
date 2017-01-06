#ifndef _EEBYSTATE_H_
#define _EEBYSTATE_H_
#include <ai_search.h>

namespace eeby
{
	class State : public ai::Search::State
	{
	public:
		State();
		State(const State &rhs);
		virtual ~State();
		State &operator=(const State &rhs);
		bool operator==(const State &rhs)const;
		virtual void Display()const;
		virtual bool IsEqual(const ai::Search::State * const state_in)const;
	
		double getx()const;
		double gety()const;
		double getz()const;
		double getcharge()const;
		double gethp()const;
	
		bool setx(const double &xin);
		bool sety(const double &yin);
		bool setz(const double &zin);
		bool setcharge(const double &charge);
		bool sethp(const double &hp);
	
		bool display(std::ostream &os)const;
	protected:
		double x,y,z; 
		double charge;
		double hp;
	};
	std::ostream &operator<<(std::ostream &os, const State &rhs);
};
#endif
