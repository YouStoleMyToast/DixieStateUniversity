#ifndef _DISPLAYDRIVER_H_
#define _DISPLAYDRIVER_H_

namespace ai
{
  namespace Agent
  {
    class DisplayDriver
    {
    public:
      DisplayDriver(int argc, char **argv);
      void EnvironmentDisplaySelect(Environment * env);
      void Run();
    protected:
      EnvironmentDisplay * mEnvironmentDisplay;
      Options mOptions;
      Socket mSocket;
    private:
    };
  }
}

#endif /* _DISPLAYDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
