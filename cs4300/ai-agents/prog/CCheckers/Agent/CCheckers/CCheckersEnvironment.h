#ifndef _CCHECKERSENVIRONMENT_H_
#define _CCHECKERSENVIRONMENT_H_

namespace ai
{
  namespace CCheckers
  {
    class CCheckersEnvironment : public ai::Agent::Environment
    {
      friend class CCheckersEnvironmentDisplay;
    public:
      CCheckersEnvironment();
      CCheckersEnvironment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in);
      virtual ~CCheckersEnvironment();

      /*
       * Apply the move that is returned by an agent
       */
      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);
      
      /*
       * Calculate the agent's score
       */
      virtual void CalculatePerformance(ai::Agent::Agent *agent);

      /*
       * The percept is a copy of the game board
       */
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);

      /*
       * Step applies 1 ply for the current player
       */
      virtual void Step();
      
      /*
       * Run until the game has completed, or n_steps have been reached
       */
      virtual void Run(const int n_steps);

      /*
       * 
       */
      virtual void AddAgent(ai::Agent::Agent *agent);
      
      /*
       * Locations are not used, but must override this 
       * not to be an abstract class
       */
      virtual ai::Agent::Location *DefaultLocation() const;

      /*
       * Get a reference to the game board
       */
      const BasicBoard & GameBoard() const;
      
    protected:
      BasicBoard game_board;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Environment>(*this);
        ar & game_board;
      }
    };
  }
}

#endif /* _CCHECKERSENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
