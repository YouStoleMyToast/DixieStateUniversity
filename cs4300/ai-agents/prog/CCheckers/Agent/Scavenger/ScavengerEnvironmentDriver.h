#ifndef _SCAVENGERENVIRONMENTDRIVER_H_
#define _SCAVENGERENVIRONMENTDRIVER_H_

namespace ai
{
  namespace Scavenger
  {
    class ScavengerEnvironmentDriver : public ai::Agent::EnvironmentDriver
    {
    public:
      ScavengerEnvironmentDriver(int argc, char **argv, bool init_options = true);
      virtual void Run();
    protected:
    private:
    };
  }
}

#endif /* _SCAVENGERENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
