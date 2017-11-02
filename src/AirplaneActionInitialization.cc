// source for ActionInitialization

#include "AirplaneActionInitialization.hh"

#include "AirplanePrimaryGeneratorAction.hh"

AirplaneActionInitialization::AirplaneActionInitialization()
{ }

AirplaneActionInitialization::~AirplaneActionInitialization()
{ }

void AirplaneActionInitialization::Build() const
{
  SetUserAction(new AirplanePrimaryGeneratorAction());
}
