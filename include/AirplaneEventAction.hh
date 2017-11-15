// header for EventAction

#ifndef AirplaneEventAction_h
#define AirplaneEventAction_h 1

#include "G4UserEventAction.hh"

#include "AirplaneTrackingAction.hh"
#include "G4Event.hh"

class AirplaneEventAction : public G4UserEventAction
{
  public:
    AirplaneEventAction(AirplaneTrackingAction* tracking);
    virtual ~AirplaneEventAction();

    virtual void BeginOfEventAction(const G4Event*);
  
  private:
    AirplaneTrackingAction* fTracking;
};

#endif
