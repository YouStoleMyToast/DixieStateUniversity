#ifndef _XYAGENT_H_
#define _XYAGENT_H_

namespace ai
{
  namespace Agent
  {
    class XYAgent : public Agent
    {
    public:
      XYAgent();
      XYAgent(Socket * sock_in);
      virtual Percept *GetPercept(const Location *location);
      virtual void TurnRight();
      virtual void TurnLeft();
      virtual void Forward(int width_in, int height_in);
      int     GetDirection();
    protected:
      bool bump;
      int  direction;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Agent>(*this);
	ar & bump;
	ar & direction;
      }
    };
  }
}

#endif /* _XYAGENT_H_ */
