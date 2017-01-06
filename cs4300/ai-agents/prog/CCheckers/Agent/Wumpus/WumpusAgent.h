#ifndef _WUMPUSAGENT_H_
#define _WUMPUSAGENT_H_

namespace ai
{
  namespace Agent
  {
    class WumpusAgent : public XYAgent
    {
    public:
      WumpusAgent();
      WumpusAgent(Socket * sock_in);
      virtual Percept *GetPercept(const Location *location);
      virtual void Shoot();
      virtual void Grab();
      virtual void Yell();
      virtual void UnYell();
      int          ArrowCount();
      int          GoldCount();
      bool         GetYellLast();
    protected:
      int arrows;
      int gold;
      int yell_last;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYAgent>(*this);
	ar & arrows;
	ar & gold;
	ar & yell_last;
      }
    };
  }
}

#endif /* _WUMPUSAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
