#ifndef _EEBYACTION_H_
#define _EEBYACTION_H_
#include <ai_search.h>

namespace eeby
{
	class Action : public ai::Search::Action
	{
	public:
		/* order and value is importiant */
		enum {A_MIN=-1,A_NORTH=0,A_SOUTH=1,A_EAST=2,A_WEST=3,A_MAX=4,LOOK=5,RECHARGE=6,PICKUP=7,DROP=8,DEPOSIT=9,EXAMINE=10,QUIT=11,L_NORTH=12,L_SOUTH=13,L_EAST=14,L_WEST=15,A_OUT_OF_BOUNDS};
		
		Action();
		Action(const Action &rhs);
		virtual ~Action();
		Action &operator=(const Action &rhs);
		bool operator==(const Action &rhs)const;
		virtual void display()const;
		bool settype(int typein);
		int gettype()const;
		static int LabelToEnum(const char *s);
		static const char *EnumToLabel(const int &i);
		bool display(std::ostream &os)const;
	
	protected:
		int type; /* A_* */
	private:
	};
	std::ostream &operator<<(std::ostream &os, const Action &rhs);
};
#endif
