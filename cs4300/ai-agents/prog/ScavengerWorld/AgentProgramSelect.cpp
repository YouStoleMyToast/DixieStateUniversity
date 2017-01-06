
#include <ai_agent.h>

#include "Snorlax.h"
#include "Manual.h"
#include "eebpikachu.h"
#include "eebgyarados.h"
#include "eebglados.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 'S':
          agent_program = new ai::Sample::Snorlax(opts);
          break;
        case 'm':
          agent_program = new ai::Sample::Manual();
          break;
        case 'p':
          agent_program = new eebp::pikachu(opts);
          break;
        case 'y':
          agent_program = new eeby::Gyarados(opts);
          break;
        case 'g':
          agent_program = new eeb::Glados(opts);
          break;

        default:
          std::cout << "Unknown agent program " << std::endl
                    << "S : Snorlax" << std::endl
                    << "m : Manual" << std::endl
                    << "p : pikachu" << std::endl
                    << "y : Gyarados" << std::endl
                    << "g : Glados" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
