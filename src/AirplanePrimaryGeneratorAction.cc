// source for PrimaryGeneratorAction

#include "AirplanePrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

AirplanePrimaryGeneratorAction::AirplanePrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{ 
  fParticleGun = new G4GeneralParticleSource();
}

AirplanePrimaryGeneratorAction::~AirplanePrimaryGeneratorAction()
{
  delete fParticleGun;
}

void AirplanePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

