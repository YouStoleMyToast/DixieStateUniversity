#ifndef _SCAVENGERACTION_H_
#define _SCAVENGERACTION_H_

namespace ai
{
  namespace Scavenger
  {
    class Location;
    
    class Action: public ai::Agent::Action
    {  
    public:
      Action();
      virtual ~Action();
      
      virtual bool TextDisplay(std::ostream &os) const;
      
      std::string GetObjectId (  );
      bool SetObjectId ( const std::string & object_id_in );

      Location::Direction GetDirection() const;
      bool SetDirection(Location::Direction direction_in);
      
      enum ActionEnum 
        {
          /* Movement actions */
          GO_NORTH,  
          GO_SOUTH,
          GO_EAST,
          GO_WEST,
          /* Look at the horizon in one direction */
          LOOK,
	  
          /* others */
          RECHARGE,
          PICKUP,  /* Attempt to put an object in the bin */
          DROP,    /* Attempt to remove an object from the bin */
          DEPOSIT, /* Attempt to put an object from the bin to the base */
          EXAMINE, /* Examine the details of object */
          QUIT,    /* Stop playing */
          NOOP     /* Do nothing this turn */
        };
      
    protected:
      std::string object_id;
      Location::Direction direction;
      
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Action>(*this);
        ar & object_id;
        ar & direction;
      }
    };
  }
}

#endif /* _SCAVENGERACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
