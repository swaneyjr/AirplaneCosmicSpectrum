// header for EventAction

#ifndef AirplaneEventAction_h
#define AirplaneEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"

class AirplaneEventAction : public G4UserEventAction
{
  public:
    AirplaneEventAction();
    virtual ~AirplaneEventAction();

    virtual void BeginOfEventAction(const G4Event*);

};

#endif
