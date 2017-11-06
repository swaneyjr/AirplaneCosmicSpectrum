// source for SteppingAction

#include "AirplaneSteppingAction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "g4root.hh"

#include <cmath>

AirplaneSteppingAction::AirplaneSteppingAction()
 : G4UserSteppingAction()
{ }

AirplaneSteppingAction::~AirplaneSteppingAction()
{ }

void AirplaneSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	
  const G4ThreeVector prePoint = aStep->GetPreStepPoint()->GetPosition();
  const G4ThreeVector postPoint = aStep->GetPostStepPoint()->GetPosition();

  G4double preY = prePoint.getY();
  G4double postY = postPoint.getY();

  if ( (preY > 0 && postY <= 0) || (preY < 0 && postY >= 0) )
  {
    // we crossed the threshold
    G4double preX = prePoint.getX();
    if ( std::fabs(preX/cm) > 177)
    {
      return;
    }
    
    // we are inside the plane, so save the energy
    G4Track* track = aStep->GetTrack();
    const G4ParticleDefinition* particle = track->GetParticleDefinition();

    const G4double velocity = track->GetVelocity();
    const G4double beta = velocity/CLHEP::c_light;
    G4double beta_gamma = 1./std::sqrt(1./(beta*beta) - 1);

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->FillNtupleSColumn(0, particle->GetParticleName());
    analysisManager->FillNtupleDColumn(1, beta_gamma);
    analysisManager->FillNtupleDColumn(2, dEdx(beta, particle)/MeV*g/cm2);
    analysisManager->FillNtupleDColumn(3, track->GetVertexKineticEnergy()/MeV);
    analysisManager->FillNtupleDColumn(4, track->GetVertexPosition().getY()/cm);
    analysisManager->FillNtupleDColumn(5, preX/cm);
    
    analysisManager->AddNtupleRow();
  }



}

G4double AirplaneSteppingAction::dEdx(const G4double beta, const G4ParticleDefinition* p)
{
  if(p->GetPDGCharge() == 0)
  {
    if(p->GetParticleName()=="gamma")
    {
      // TODO	    
      return 0;
    } 
    else 
    {
      // neutrons and neutrinos
      return 0;
    }
  }
  else if(p->GetParticleName()=="e-" || p->GetParticleName() == "e+")
  {
    // TODO
    return 0;
  }
  else
  {
    // charged heavy particles
    return dEdx_Bethe(beta, p);
  }
}

G4double AirplaneSteppingAction::dEdx_Bethe(const G4double beta, const G4ParticleDefinition* p)
{
  const G4double beta_gamma_sq = 1./(1./(beta*beta)-1);
  const G4double z = p->GetPDGCharge()/eplus;
  const G4double K=.307075*MeV/mole*cm2;
  const G4double Z=14;
  const G4double A=28.085*g/mole;
  const G4double E_rest_e=0.511*MeV;
  const G4double mass_ratio = E_rest_e/(p->GetPDGMass()*CLHEP::c_light*CLHEP::c_light);
  const G4double W_max=2*E_rest_e*beta_gamma_sq/(1+2*mass_ratio/std::sqrt(1-beta*beta) + mass_ratio*mass_ratio);
  const G4double I=173*eV;

  return K*z*z*Z/A/(beta*beta)*(0.5*std::log(2*E_rest_e*beta_gamma_sq*W_max/(I*I))-(beta*beta));
}
