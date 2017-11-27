// source for ActionInitialization

#include "AirplaneActionInitialization.hh"

#include "AirplanePrimaryGeneratorAction.hh"
#include "AirplaneRunAction.hh"
#include "AirplaneEventAction.hh"
#include "AirplaneStackingAction.hh"
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
  
  AirplaneTrackingAction* tracking = new AirplaneTrackingAction();
  SetUserAction(tracking);
  SetUserAction(new AirplaneEventAction(tracking));
  SetUserAction(new AirplaneStackingAction(tracking));
  SetUserAction(new AirplaneSteppingAction(tracking));
}
