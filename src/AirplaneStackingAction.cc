// source for StackingAction

#include "AirplaneStackingAction.hh"
#include "G4SystemOfUnits.hh"

AirplaneStackingAction::AirplaneStackingAction(AirplaneTrackingAction* tracking)
 : G4UserStackingAction(),
   fTracking(tracking)
{ }

AirplaneStackingAction::~AirplaneStackingAction()
{ }

G4ClassificationOfNewTrack AirplaneStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{	   
  if (aTrack->GetKineticEnergy() < fTracking->GetEdepThresh()) {
    return fKill;
  }
  return fUrgent; 
}
