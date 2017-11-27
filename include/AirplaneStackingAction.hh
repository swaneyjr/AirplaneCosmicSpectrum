// header for StackingAction

#ifndef AirplaneStackingAction_h
#define AirplaneStackingAction_h 1

#include "G4UserStackingAction.hh"

#include "AirplaneTrackingAction.hh"

class AirplaneStackingAction : public G4UserStackingAction
{
  public:
    AirplaneStackingAction(AirplaneTrackingAction*);
    virtual ~AirplaneStackingAction();

    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);

  private:
    AirplaneTrackingAction* fTracking;  

};

#endif
