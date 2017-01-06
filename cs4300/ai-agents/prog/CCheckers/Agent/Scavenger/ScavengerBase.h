#ifndef _SCAVENGERBASE_H_
#define _SCAVENGERBASE_H_

namespace ai
{
  namespace Scavenger
  {
    class Base: public ai::Agent::Object
    {
    public:
      Base();
      Base(Agent *agent_in, Cell *cell_in);

      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);
      
      bool      SetAgent(Agent *agent_in);
      bool      SetCell(Cell *cell_in);
      Agent    *GetAgent() const;
      Cell     *GetCell() const;

      bool AddObject ( ai::Scavenger::Object *obj_in );
      std::vector<ai::Scavenger::Object *> & GetHopper (  );
      ai::Scavenger::Object * GetObject(const std::string &object_id_in);
      
      std::string GetString() const;
      static bool ParseString(const std::string &base_in,
                              unsigned int &cell_id_out);

      double GetHopperValue(const unsigned int skip_object_count, const unsigned int max_object_count) const;
    protected:
      Agent    * agent;
      Cell     * cell;
      
      std::vector<ai::Scavenger::Object *> hopper;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Object>(*this);
        ar & agent;
        ar & cell;
        ar & hopper;
      }
    };
  }
}

#endif /* _SCAVENGERBASE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
