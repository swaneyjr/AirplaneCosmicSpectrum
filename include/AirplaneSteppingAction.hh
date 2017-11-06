// header for SteppingAction

#ifndef AirplaneSteppingAction_h
#define AirplaneSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

class AirplaneSteppingAction : public G4UserSteppingAction
{
  public:
    AirplaneSteppingAction();
    virtual ~AirplaneSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    G4double dEdx(G4double, const G4ParticleDefinition*);
    G4double dEdx_Bethe(G4double, const G4ParticleDefinition*);
};



#endif
