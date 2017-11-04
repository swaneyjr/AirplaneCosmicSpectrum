// source for SteppingAction

#include "AirplaneSteppingAction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "g4root.hh"

AirplaneSteppingAction::AirplaneSteppingAction()
 : G4UserSteppingAction()
{ }

AirplaneSteppingAction::~AirplaneSteppingAction()
{ }

void AirplaneSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // make sure we're dealing with protons
  if( aStep->GetTrack()
           ->GetParticleDefinition()
	   ->GetParticleName()
	   != "proton" )

  {
    return;
  }
	
  const G4ThreeVector prePoint = aStep->GetPreStepPoint()->GetPosition();
  const G4ThreeVector postPoint = aStep->GetPostStepPoint()->GetPosition();

  G4double preY = prePoint.getY();
  G4double postY = postPoint.getY();

  if ( (preY > 0 && postY <= 0) || (preY < 0 && postY >= 0) )
  {
    // we crossed the threshold
    G4double preX = prePoint.getX();
    if ( std::fabs(preX/cm) > 177 || std::fabs(preX/cm) < 90)
    {
      return;
    }

    // we are inside the plane, so save the energy
    G4double ke = aStep->GetPreStepPoint()->GetKineticEnergy();
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(analysisManager->GetH1Id("airplane"), ke);
  }



}
