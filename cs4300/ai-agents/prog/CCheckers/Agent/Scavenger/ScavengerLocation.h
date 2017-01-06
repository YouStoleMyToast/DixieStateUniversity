#ifndef _SCAVENGERLOCATION_H_
#define _SCAVENGERLOCATION_H_

namespace ai
{
  namespace Scavenger
  {
    class Location: public ai::Agent::Location
    {
    public:
      
      Location();
      Location(const Location &rhs);
      Location(double x_in, double y_in, double elevation_in);
      bool Set(double x_in, double y_in, double elevation_in);
      double GetX() const;
      double GetY() const;
      double GetElevation() const;
      
      // the numbers are important as they are used as array indexes
      enum Direction { NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3 };

      Location & operator=(const Location &rhs);
      bool operator==(const Location &rhs) const;
      bool operator<(const Location &rhs) const;
      
      std::string             GetString() const;
    protected:

      double x;
      double y;
      double elevation;
      
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Location>(*this);
        ar & x;
        ar & y;
        ar & elevation;
      }
    };
  }
}

#endif /* _SCAVENGERLOCATION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
