#ifndef _WUMPUSWORLDDISPLAY_H_
#define _WUMPUSWORLDDISPLAY_H_

namespace ai
{
  namespace Agent
  {
    class WumpusWorld;
    
    class WumpusWorldDisplay : public XYEnvironmentDisplay
    {
    public:
      WumpusWorldDisplay(Environment *env, int width_in, int height_in);
      virtual ~WumpusWorldDisplay();
      virtual void Redraw(Environment *env);
    protected:
    private:
    };
  }
}

#endif /* _WUMPUSWORLDDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
