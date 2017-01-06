#ifndef _EEBPIKACHU_H_
#define _EEBPIKACHU_H_

#include <ai_scavenger.h>

namespace eebp
{
 class pikachu : public ai::Agent::AgentProgram
 {
 public:
 pikachu(ai::Agent::Options *opts);
 ~pikachu();
 virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
 protected:
 private:
 };
}

#endif /* _EEBPIKACHU_H_ */
