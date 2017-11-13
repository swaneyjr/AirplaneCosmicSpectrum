// source for ActionInitialization

#include "AirplaneActionInitialization.hh"

#include "AirplanePrimaryGeneratorAction.hh"
#include "AirplaneRunAction.hh"
#include "AirplaneEventAction.hh"
#include "AirplaneTrackingAction.hh"
#include "AirplaneSteppingAction.hh"

AirplaneActionInitialization::AirplaneActionInitialization()
{ }

AirplaneActionInitialization::~AirplaneActionInitialization()
{ }

void AirplaneActionInitialization::Build() const
{
  SetUserAction(new AirplanePrimaryGeneratorAction());
  SetUserAction(new AirplaneRunAction());
  SetUserAction(new AirplaneEventAction());
  
  AirplaneTrackingAction* tracking = new AirplaneTrackingAction();
  SetUserAction(tracking);
  SetUserAction(new AirplaneSteppingAction(tracking));
}
