// source for SteppingAction

#include "AirplaneSteppingAction.hh"

#include "AirplaneDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VTouchable.hh"
#include "globals.hh"
#include "g4root.hh"

#include <cmath>

AirplaneSteppingAction::AirplaneSteppingAction(AirplaneTrackingAction* trackingAction)
 : G4UserSteppingAction(),
   fScoringVolume(0),
   fTrackingAction(trackingAction)
{ }

AirplaneSteppingAction::~AirplaneSteppingAction()
{ }

void AirplaneSteppingAction::UserSteppingAction(const G4Step* aStep)
{	
  if ( !fScoringVolume ) {
    const AirplaneDetectorConstruction* detectorConstruction
      = static_cast<const AirplaneDetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetSensorVolume();
  }
  
  const G4StepPoint* preStep  = aStep->GetPreStepPoint();
  const G4VTouchable* preTouchable = preStep->GetTouchable();
  const G4VPhysicalVolume* prePhys = preTouchable->GetVolume();
  const G4LogicalVolume* preVolume = prePhys->GetLogicalVolume();


  
  if ( preVolume == fScoringVolume ) {
    // we are inside the sensor, so save energy
    
    if ( !fTrackingAction->AlreadyHit() ) {
      fTrackingAction->SetHit();
      fTrackingAction->SetSensorX(preStep->GetPosition().getX());
    }	    
  
    fTrackingAction->AddEdep(aStep->GetTotalEnergyDeposit());
  }
}

