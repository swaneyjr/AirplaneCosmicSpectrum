// source for EventAction

#include "AirplaneEventAction.hh"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4UImanager.hh"
#include "globals.hh"
#include "g4root.hh"

AirplaneEventAction::AirplaneEventAction()
  : G4UserEventAction()
{ }

AirplaneEventAction::~AirplaneEventAction()
{ }

void AirplaneEventAction::BeginOfEventAction(const G4Event* anEvent)
{
  G4PrimaryVertex* primaryVertex = anEvent->GetPrimaryVertex();
  G4PrimaryParticle* primary = primaryVertex->GetPrimary();
  G4double ke = primary->GetKineticEnergy();  

  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4String pname = UI->SolveAlias("{pname}");
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(analysisManager->GetH1Id(pname), ke);
}

