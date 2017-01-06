#ifndef _XYENVIRONMENT_H_
#define _XYENVIRONMENT_H_

namespace ai
{
  namespace Agent
  {
    class XYEnvironment : public Environment
    {
      friend class XYEnvironmentDisplay;
    public:
      XYEnvironment();
      XYEnvironment(const RandomNumber &rand_in, 
		    int width_in, int height_in, std::vector<Socket *> *displays_in);
      virtual ~XYEnvironment();
      virtual bool ApplyAction(Agent *agent, Action *action);
      virtual void CalculatePerformance(Agent *agent);
      virtual Location *DefaultLocation() const;
      int GetWidth() const;
      int GetHeight() const;
    protected:
      int width;
      int height;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Environment>(*this);
	ar & width;
	ar & height;
      }
    };
  }
}
#endif /* _XYENVIRONMENT_H_ */
