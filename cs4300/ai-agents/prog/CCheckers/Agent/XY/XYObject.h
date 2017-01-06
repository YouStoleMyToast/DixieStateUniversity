#ifndef _XYOBJECT_H_
#define _XYOBJECT_H_

namespace ai
{
  namespace Agent
  {
    class XYObject : public Object
    {
    public:
      virtual Percept *GetPercept(const Location *location);
      virtual bool Near(const Location *location, int radius);
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Object>(*this);
      }
    };
  }
}

#endif /* _XYOBJECT_H_ */
