// source for PrimaryGeneratorAction

#include "AirplanePrimaryGeneratorAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

AirplanePrimaryGeneratorAction::AirplanePrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{ 
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="proton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(100.*MeV);

}

AirplanePrimaryGeneratorAction::~AirplanePrimaryGeneratorAction()
{
  delete fParticleGun;
}

void AirplanePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

