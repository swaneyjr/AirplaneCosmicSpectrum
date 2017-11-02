// source for PhysicsList

#include "AirplanePhysicsList.hh"

#include "G4VUserPhysicsList.hh"
#include "G4Proton.hh"

AirplanePhysicsList::AirplanePhysicsList()
: G4VUserPhysicsList()
{ }

AirplanePhysicsList::~AirplanePhysicsList()
{ }

void AirplanePhysicsList::ConstructParticle()
{
  G4Proton::ProtonDefinition();
}


void AirplanePhysicsList::ConstructProcess()
{
  AddTransportation();
}
