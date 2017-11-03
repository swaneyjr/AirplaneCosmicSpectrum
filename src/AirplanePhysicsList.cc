// source for PhysicsList

#include "AirplanePhysicsList.hh"

#include "G4EmStandardPhysics.hh"

AirplanePhysicsList::AirplanePhysicsList()
: G4VModularPhysicsList()
{ 
  SetVerboseLevel(1);
  RegisterPhysics(new G4EmStandardPhysics());
}

AirplanePhysicsList::~AirplanePhysicsList()
{ }

