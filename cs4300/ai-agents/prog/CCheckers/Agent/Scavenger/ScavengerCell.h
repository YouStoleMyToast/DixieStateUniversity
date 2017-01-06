#ifndef _SCAVENGERCELL_H_
#define _SCAVENGERCELL_H_

namespace ai
{
  namespace Scavenger
  {
    class Object;
    
    class Cell
    {
    public:
      /*
       *
       */
      Cell();
      Cell(Location location_in, unsigned int id_in);
      Cell(const std::string &cell_in);
      
      /*
       * Note that although Cell stores pointers to various data objects,
       * it does not delete any of the pointers.
       *
       * The pointers are not deleted in the destructor, or in the Remove*()
       * methods.
       *
       * The neighbor, obj, and base pointers should be kept in unique lists
       * somewhere else for proper clean up.
       *
       */
      ~Cell();
      
      bool                    SetLocation(const Location & location_in);
      bool                    SetNeighbor(const Location::Direction &which,
                                          Cell * cell_in);
      bool                    SetInterface(const Location::Direction &which,
                                           const CellInterface &iface_in);
      bool                    AddObject(Object *obj_in);
      bool                    RemoveObject(const Object *obj_in);
      bool                    AddBase(Base *base_in);
      bool                    RemoveBase(const Base *base_in);

      bool                    SetVisited(const int i);
      int                     GetVisited() const;
      
      unsigned int            GetId() const;
      ai::Scavenger::Location GetLocation() const;
      unsigned int            GetNeighborId(const Location::Direction &which) const;
      Cell *                  GetNeighbor(const Location::Direction &which) const;
      CellInterface           GetInterface(const Location::Direction &which) const;
      std::vector<Object *> & GetObjects();
      Object *                GetObject(const std::string &object_id_in);
      std::vector<Base *>   & GetBases();
      std::string             GetString() const;
      
      static bool             ParseString(const std::string &str_in,
                                          unsigned int &id_out,
                                          Location &location_out,
                                          unsigned int neighbors_out[4],
                                          CellInterface interfaces_out[4]);
    protected:
      unsigned int          id;
      Location              location;
      unsigned int          neighbor_ids[4];
      Cell *                neighbors[4];
      CellInterface         interfaces[4];
      std::vector<Object *> objs;
      std::vector<Base *>   bases;
      int                   visited;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & id;
        ar & location;
        ar & neighbor_ids;
        ar & neighbors;
        ar & interfaces;
        ar & objs;
        ar & bases;
        ar & visited;
      }
    };
  }
}

BOOST_CLASS_TRACKING(ai::Scavenger::Cell, boost::serialization::track_always)

#endif /* _SCAVENGERCELL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
