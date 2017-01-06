#ifndef _WUMPUSWORLDDRIVER_H_
#define _WUMPUSWORLDDRIVER_H_

namespace ai
{
  namespace Agent
  {
    class WumpusWorldDriver : public EnvironmentDriver
    {
    public:
      WumpusWorldDriver(int argc, char **argv, bool init_options = true);
      virtual void Run();
    protected:
    private:
    };
  }
}

#endif /* _WUMPUSWORLDDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
