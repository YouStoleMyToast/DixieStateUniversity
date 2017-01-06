#ifndef _EEBACTION_H_
#define _EEBACTION_H_
#include <ai_search.h>

namespace eebt
{
	class Action : public ai::Search::Action
	{
	public:
		enum {A_MIN=-1,FORWARD=0,TURN_RIGHT=1,TURN_LEFT=2,GRAB=3,SHOOT=4,QUIT=5,NOOP=6,A_OUT_OF_BOUNDS};
		Action();
		Action(const Action &rhs);
		virtual ~Action();
		Action &operator=(const Action &rhs);
		bool operator==(const Action &rhs)const;
		virtual void display()const;
		//bool settype(int typein);
		//int gettype()const;
		static int LabelToEnum(const char *s);
		static const char *EnumToLabel(const int &i);
		bool display(std::ostream &os)const;
	
	protected:
		int type;
	private:
	};
	std::ostream &operator<<(std::ostream &os, const Action &rhs);
};
#endif
