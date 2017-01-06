#ifndef _WUMPUSWORLD_H_
#define _WUMPUSWORLD_H_

namespace ai
{
  namespace Agent
  {
    class WumpusWorld : public XYEnvironment
    {
      friend class WumpusWorldDisplay;
    public:
      WumpusWorld();
      WumpusWorld(const RandomNumber &rand_in,
		  int width, int height, int nirvana,
		  int drwho,
		  std::vector<Socket *> *displays_in);
      virtual ~WumpusWorld();
      virtual bool ApplyAction(Agent *agent, Action *action);
      virtual void CalculatePerformance(Agent *agent);
      virtual Percept *GetPercept(Agent *agent);
      virtual void AddAgent(Agent *agent_in);
      
    protected:
      bool InPit(Agent *agent_in);
      bool EatenByWumpus(Agent *agent_in);
      
      bool GrabGold(XYLocation *xy_loc);
      void ShootArrow(XYLocation *xy_loc, int direction);
      
      void Visit(int x, int y);
      bool IsVisited(int x, int y) const;
    private:
      //bool *visited;
      std::vector<bool> visited;
      int nirvana;
      int drwho;
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYEnvironment>(*this);
	ar & visited;
	ar & nirvana;
	ar & drwho;
      }
    };
  }
}

#endif /* _WUMPUSWORLD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
