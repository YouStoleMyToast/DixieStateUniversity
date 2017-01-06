#ifndef _EEBSTATE_H_
#define _EEBSTATE_H_
#include <ai_search.h>

namespace eebt
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
		bool setx(const double &xin);
		bool sety(const double &yin);
		bool display(std::ostream &os)const;
	protected:
		double x,y;
	};
	std::ostream &operator<<(std::ostream &os, const State &rhs);
};
#endif
