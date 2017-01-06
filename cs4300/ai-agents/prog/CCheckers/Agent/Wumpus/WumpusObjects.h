#ifndef _WUMPUSOBJECTS_H_
#define _WUMPUSOBJECTS_H_

namespace ai
{
  namespace Agent
  {
    class WumpusGoldObject : public XYObject
    {
    public:
      WumpusGoldObject();
      virtual Percept *GetPercept(const Location *location);
      virtual bool Near(const Location *location, int distance);
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYObject>(*this);
      }
    };
    class WumpusPitObject : public XYObject
    {
    public:
      WumpusPitObject();
      virtual Percept *GetPercept(const Location *location);
      virtual bool Near(const Location *location, int distance);
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYObject>(*this);
      }
    };
    class WumpusWumpusObject : public XYObject
    {
    public:
      WumpusWumpusObject();
      virtual Percept *GetPercept(const Location *location);
      virtual bool Near(const Location *location, int distance);
      virtual void Kill();
      virtual bool IsAlive() const;
    protected:
      bool alive;
      bool scream;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYObject>(*this);
	ar & alive;
	ar & scream;
      }
    };
    
    class WumpusTardisObject : public XYObject
    {
    public:
      WumpusTardisObject();
      virtual Percept *GetPercept(const Location *location);
      virtual bool Near(const Location *location, int distance);
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<XYObject>(*this);
      }
    };
  }
}

#endif /* _WUMPUSOBJECTS_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
