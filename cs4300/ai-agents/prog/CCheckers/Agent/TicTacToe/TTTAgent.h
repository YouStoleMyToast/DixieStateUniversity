#ifndef _TTTAGENT_H_
#define _TTTAGENT_H_
namespace ai
{
  namespace TicTacToe
  {
    class Agent : public ai::Agent::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket * sock_in);
      virtual ~Agent();
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);

      /*
       * set the player's number.  This number should be 1-2
       */
      bool SetPlayerNumber(int n_in);
      
      /*
       * get the player's number.
       */
      int GetPlayerNumber() const;

      /*
       * Duration is used internally by Environment to track the
       * number of seconds the player is using to think.
       */
      void SetDuration(double duration_in);
      double GetDuration() const;
    protected:
      int player_number;
      double duration;
      
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Agent>(*this);
        ar & player_number;
        ar & duration;
      }
    };
  }
}
#endif /* _TTTAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
