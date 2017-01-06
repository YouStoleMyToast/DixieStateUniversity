#ifndef _XYACTION_H_
#define _XYACTION_H_

namespace ai
{
  namespace Agent
  {
    class XYAction : public Action
    {
    public:
      enum ActionEnum { TURN_RIGHT = 1, TURN_LEFT, FORWARD };
      virtual bool TextDisplay(std::ostream & os) const;
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Action>(*this);
      }
    };
  }
}

#endif /* _XYACTION_H_ */
