#include "eebpikachu.h"
#include <cstdio>
#include <cstring>

namespace eebp
{

	        /* For more on options look at the files:
		 * ai-lib/include/Agent/Options.h
		 * ai-lib/src/Agent/Options.cpp
		 * al-lib/src/Agent/AgentDriver.cpp
		 */
	        /*
		 * Run with:
		 * ./RunProg ./SA_Test -a s -U 1
		 */
pikachu::pikachu(ai::Agent::Options *opts)
{
  SetName("pikachu");
  std::cout << "The value of the -U option is: " << opts->GetArgInt("user1") << std::endl;
}
pikachu::~pikachu()
{
}

ai::Agent::Action * pikachu::Program(const ai::Agent::Percept * percept)
{
	printf("\nhi\n");
	ai::Scavenger::Action *action = new ai::Scavenger::Action;
	unsigned int i;

	for(i = 0; i < percept->NumAtom(); i++)
	{
		ai::Agent::PerceptAtom a = percept->GetAtom(i);
		std::cout << a.GetName() << ": " << a.GetValue() << std::endl;
	}
		action->SetCode(ai::Scavenger::Action::QUIT);
		return action;
	}    
}
