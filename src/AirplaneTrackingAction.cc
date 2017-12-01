// source for TrackingAction

#include "AirplaneTrackingAction.hh"

#include "AirplaneDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "g4root.hh"
#include "G4SystemOfUnits.hh"

AirplaneTrackingAction::AirplaneTrackingAction()
 : G4UserTrackingAction(),
   fPrimary(""),
   fEprimary(0.),
   fEdep(0.),
   fScoringVolume(0),	
   fSensorX(0.),
   fEdepThresh(1.1*eV)
{ }

AirplaneTrackingAction::~AirplaneTrackingAction()
{ }

void AirplaneTrackingAction::PreUserTrackingAction(const G4Track*)
{
  fEdep = 0.;
  fHit = false;

  if ( !fScoringVolume ) {
    const AirplaneDetectorConstruction* detectorConstruction
      = static_cast<const AirplaneDetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetSensorVolume();
  }

}

void AirplaneTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{   	
  if ( !fHit || fEdep < fEdepThresh) return;
  const G4ParticleDefinition* particle = aTrack->GetParticleDefinition();
  const G4ThreeVector vertex = aTrack->GetVertexPosition();

  G4String name;
  if (aTrack->GetLogicalVolumeAtVertex() == fScoringVolume) {
    name = "delta";	  
  } else {
    name = particle->GetParticleName();
  }
                                      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleSColumn(0, name);
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
