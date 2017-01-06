#ifndef _WUMPUSACTION_H_
#define _WUMPUSACTION_H_

namespace ai
{
  namespace Agent
  {
    class WumpusAction : public XYAction
    {
    public:
      enum ActionEnum { GRAB = 1, SHOOT, TURN_RIGHT, TURN_LEFT, FORWARD, QUIT, YELL, NOOP };
      virtual bool TextDisplay(std::ostream & os) const;
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYAction>(*this);
      }
    };
  }
}

#endif /* _WUMPUSACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
