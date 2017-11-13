// source for TrackingAction

#include "AirplaneTrackingAction.hh"

#include "g4root.hh"
#include "G4SystemOfUnits.hh"

AirplaneTrackingAction::AirplaneTrackingAction()
 : G4UserTrackingAction(),
   fEdep(0.),
   fBetaGamma(0.),
   fSensorX(0.)
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
  if ( !fHit ) return;
  const G4ParticleDefinition* particle = aTrack->GetParticleDefinition();  
                                      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleSColumn(0, particle->GetParticleName());
  analysisManager->FillNtupleDColumn(1, fBetaGamma);
  analysisManager->FillNtupleDColumn(2, fEdep/eV);
  analysisManager->FillNtupleDColumn(3, aTrack->GetVertexPosition().getY()/cm);
  analysisManager->FillNtupleDColumn(4, fSensorX/cm);   

  analysisManager->AddNtupleRow();              
}
