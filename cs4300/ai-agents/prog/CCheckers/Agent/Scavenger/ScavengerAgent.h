#ifndef _SCAVENGERAGENT_H_
#define _SCAVENGERAGENT_H_

namespace ai
{
  namespace Scavenger
  {
    class Cell;
    class Base;
    
    class Agent: public ai::Agent::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket *sock_in);
      void Initialize();
      
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);

      bool Move (const Cell &from, const CellInterface &iface, const Cell &to, int time_step_in);
      bool Look( const std::string &look_in, int time_step_in );
      bool Recharge ( int time_step_in );
      bool Pickup ( ai::Scavenger::Object * object, int time_step_in );
      bool Drop ( ai::Scavenger::Object * object, int time_step_in );
      bool Deposit ( ai::Scavenger::Object * object, int time_step_in );
      bool Examine( const std::string &examine_in, int time_step_in );
      bool Quit ( int time_step_in );
      std::vector<ai::Scavenger::Object *> & GetHopper (  );
      ai::Scavenger::Object * GetObject(const std::string &object_id_in);

      void TakeDamage( double hit_points_lost );
      void DrainCharge( double charge_lost );

      void SetBase( Base *base_ptr_in );
      Base * GetBase( );
      int  GetQuitTimeStep() const;
      int  GetLastTimeStep() const;

      double GetCharge() const;
      double GetHitPoints() const;
      int    GetNumVisitedCells() const;

      void   SetIndex( int index_in );
      int    GetIndex() const;
    protected:
      double charge;
      double hit_points;
      std::vector<ai::Scavenger::Object *> hopper;
      std::map<Location, int>              visited_cells;

      Base * base_ptr;

      /* for looking at horizon interfaces */
      bool        have_look;
      std::string look;

      /* for examining at objects */
      bool        have_examine;
      std::string examine;

      /* for learning feedback on object value */
      bool        have_deposit;
      std::string deposit_string;
      
      /* The time step when the agent decided to stop */
      int quit_time_step; 

      /* The last time step when the agent executed a command */
      int last_time_step; 

      /* Agent's uniq index */
      int    index;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Agent>(*this);
        ar & charge;
        ar & hit_points;
        ar & hopper;
        ar & visited_cells;
        ar & base_ptr;
        ar & have_look;
        ar & look;
        ar & have_examine;
        ar & examine;
        ar & have_deposit;
        ar & deposit_string;
        ar & quit_time_step;
        ar & last_time_step;
      }
    };
  }
}

#endif /* _SCAVENGERAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
