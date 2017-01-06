#ifndef _XYENVIRONMENTDISPLAY_H_
#define _XYENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Agent
  {
    class XYEnvironment;
    
    class XYEnvironmentDisplay : public EnvironmentDisplay
    {
    public:
      XYEnvironmentDisplay(Environment *env);
      virtual ~XYEnvironmentDisplay();
      virtual void Redraw(Environment *env);
    protected:
      int spacing;
    private:
    };
  }
}
#endif /* _XYENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
