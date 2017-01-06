
#include <ai_agent.h>

#include "eebjohnny5.h"
#include "eebtron.h"
#include "eebtrimaxion.h"
#include "eebcyrus.h"
#include "eebhymie.h"
#include "RandomPick.h"
#include "Dumbo1.h"
#include "Dumbo2.h"
#include "Smarty.h"
#include "Pikachu.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 'j':
          agent_program = new eebj::Johnny5(opts);
          break;
        case 't':
          agent_program = new eebt::Tron(opts);
          break;
        case 'x':
          agent_program = new eebx::Trimaxion(opts);
          break;
        case 'c':
          agent_program = new eebc::Cyrus(opts);
          break;
        case 'h':
          agent_program = new eebh::Hymie(opts);
          break;
        case 'r':
          agent_program = new ai::Sample::RandomPick();
          break;
        case 'd':
          agent_program = new ai::Sample::Dumbo1();
          break;
        case 'D':
          agent_program = new ai::Sample::Dumbo2();
          break;
        case 's':
          agent_program = new ai::Sample::Smarty(opts);
          break;
        case 'p':
          agent_program = new cgl::Pikachu();
          break;

        default:
          std::cout << "Unknown agent program " << std::endl
                    << "j : Johnny5" << std::endl
                    << "t : Tron" << std::endl
                    << "x : Trimaxion" << std::endl
                    << "c : Cyrus" << std::endl
                    << "h : Hymie" << std::endl
                    << "r : RandomPick" << std::endl
                    << "d : Dumbo1" << std::endl
                    << "D : Dumbo2" << std::endl
                    << "s : Smarty" << std::endl
                    << "p : Pikachu" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
