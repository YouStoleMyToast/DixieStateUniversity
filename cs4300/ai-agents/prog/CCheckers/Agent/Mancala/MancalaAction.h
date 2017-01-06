#ifndef _MANCALAACTION_H_
#define _MANCALAACTION_H_
namespace ai
{
  namespace Mancala
  {
    class Action : public ai::Agent::Action
    {
    public:
      enum ActionEnum { MOVE = 1, QUIT = 2 };
      virtual bool TextDisplay(std::ostream & os) const;

      /*
       * Set the move coordinates
       */
      bool SetMove(const MoveData &move_in);
      
      /*
       * Retrieve the move coordinates
       */
      const MoveData &GetMove() const;
      
    protected:
      MoveData move;
      
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Action>(*this);
        ar & move;
      }
    };
  }
}
#endif /* _MANCALAACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
