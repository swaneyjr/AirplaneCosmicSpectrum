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

    virtual G4Run* GenerateRun();
    
};


#endif
