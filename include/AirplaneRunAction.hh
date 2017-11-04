// header for RunAction

#ifndef AirplaneRunAction_h
#define AirplaneRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"

class AirplaneRunAction : public G4UserRunAction
{
  public:
    AirplaneRunAction();
    virtual ~AirplaneRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

};


#endif
