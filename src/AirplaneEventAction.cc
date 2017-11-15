// source for EventAction

#include "AirplaneEventAction.hh"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4UImanager.hh"
#include "globals.hh"
#include "g4root.hh"

AirplaneEventAction::AirplaneEventAction(AirplaneTrackingAction* tracking)
  : G4UserEventAction(),
    fTracking(tracking)	
{ }

AirplaneEventAction::~AirplaneEventAction()
{ }

void AirplaneEventAction::BeginOfEventAction(const G4Event* anEvent)
{
  G4PrimaryParticle* primary = anEvent->GetPrimaryVertex()->GetPrimary();
  fTracking->SetPrimaryParticle(primary);
  G4double ke = primary->GetKineticEnergy();  

  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4String pname = UI->SolveAlias("{pname}");
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(analysisManager->GetH1Id(pname), ke);
}

