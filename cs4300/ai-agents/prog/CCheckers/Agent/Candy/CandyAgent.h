#ifndef _CANDYAGENT_H_
#define _CANDYAGENT_H_

namespace ai
{
  namespace Candy
  {
    class Agent: public ai::Agent::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket *sock_in);
      
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);

      bool Predict (const int &flavor_prediction, const double &probability_prediction);
      bool PredictMixedBag (const Action * const action);
      bool Quit ( );
      bool Noop ( );

      double GetTotalError() const;
      double GetSmallestError() const;
      int    GetNumberOfPredictions() const;

    protected:
      double total_error;
      double smallest_error;
      int    number_of_predictions;
      
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Agent>(*this);
        ar & total_error;
        ar & smallest_error;
        ar & number_of_predictions;
      }
    };
  }
}

#endif /* _CANDYAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
