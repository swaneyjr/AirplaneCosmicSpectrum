// source for TrackingAction

#include "AirplaneTrackingAction.hh"

#include "g4root.hh"
#include "G4SystemOfUnits.hh"

AirplaneTrackingAction::AirplaneTrackingAction()
 : G4UserTrackingAction(),
   fPrimary(""),
   fEprimary(0.),
   fEdep(0.),
   fSensorX(0.),
   fEdepThresh(1.1*eV)
{ }

AirplaneTrackingAction::~AirplaneTrackingAction()
{ }

void AirplaneTrackingAction::PreUserTrackingAction(const G4Track*)
{
  fEdep = 0.;
  fHit = false;
}

void AirplaneTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{   	
  if ( !fHit || fEdep < fEdepThresh) return;
  const G4ParticleDefinition* particle = aTrack->GetParticleDefinition();
  const G4ThreeVector vertex = aTrack->GetVertexPosition();  
                                      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleSColumn(0, particle->GetParticleName());
  analysisManager->FillNtupleDColumn(1, aTrack->GetVertexKineticEnergy()/MeV);
  analysisManager->FillNtupleSColumn(2, fPrimary);
  analysisManager->FillNtupleDColumn(3, fEprimary/MeV);
  analysisManager->FillNtupleDColumn(4, fEdep/MeV);
  analysisManager->FillNtupleDColumn(5, vertex.getX()/cm);
  analysisManager->FillNtupleDColumn(6, vertex.getY()/cm);
  analysisManager->FillNtupleDColumn(7, fSensorX/cm);   

  analysisManager->AddNtupleRow();              
}

void AirplaneTrackingAction::SetPrimaryParticle(G4PrimaryParticle* primary)
{ 
  fPrimary = primary->GetParticleDefinition()->GetParticleName();     	
  fEprimary = primary->GetKineticEnergy();
}
