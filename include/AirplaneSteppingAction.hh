// header for SteppingAction

#ifndef AirplaneSteppingAction_h
#define AirplaneSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "AirplaneTrackingAction.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class G4LogicalVolume;

class AirplaneSteppingAction : public G4UserSteppingAction
{
  public:
    AirplaneSteppingAction(AirplaneTrackingAction* trackingAction);
    virtual ~AirplaneSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private: 
    G4LogicalVolume* fScoringVolume;  
    AirplaneTrackingAction* fTrackingAction;
};

#endif
