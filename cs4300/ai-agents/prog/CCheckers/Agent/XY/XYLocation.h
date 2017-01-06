#ifndef _XYLOCATION_H_
#define _XYLOCATION_H_

namespace ai
{
  namespace Agent
  {
    class XYLocation : public Location
    {
    public:
      int GetX() const;
      int GetY() const;
      void Set(int x_in, int y_in);
    protected:
      int x;
      int y;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Location>(*this);
	ar & x;
	ar & y;
      }
    };
  }
}

#endif /* _XYLOCATION_H_ */
