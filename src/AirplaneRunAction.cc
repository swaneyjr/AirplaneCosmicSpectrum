// source for RunAction

#include "AirplaneRunAction.hh"

#include "AirplaneRun.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"

AirplaneRunAction::AirplaneRunAction()
 : G4UserRunAction()
{ }

AirplaneRunAction::~AirplaneRunAction()
{ }

G4Run* AirplaneRunAction::GenerateRun()
{
  G4cout<< "Particle: " << G4UImanager::GetUIpointer()->SolveAlias("{pname}") << "\n";

  return new G4Run;
}

/*
void AirplaneRunAction::EndOfRunAction(const G4Run* aRun)
{
  const AirplaneRun* theRun = (const AirplaneRun*) aRun;
  theRun->SaveToNtuple();
}
*/
