
#include <ai_agent.h>

#include "eebartemis.h"
#include "eebbirgitte.h"
#include "eebtrimaxion.h"
#include "Simpleton.h"
#include "Aristotle.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 'a':
          agent_program = new eeba::Artemis();
          break;
        case 'b':
          agent_program = new eebb::Birgitte();
          break;
        case 't':
          agent_program = new eebt::Trimaxion();
          break;
        case 'S':
          agent_program = new ai::Sample::Simpleton();
          break;
        case 'A':
          agent_program = new ai::Sample::Aristotle();
          break;

        default:
          std::cout << "Unknown agent program " << std::endl
                    << "a : Artemis" << std::endl
                    << "b : Birgitte" << std::endl
                    << "t : Trimaxion" << std::endl
                    << "S : Simpleton" << std::endl
                    << "A : Aristotle" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
