// header for SteppingAction

#ifndef AirplaneSteppingAction_h
#define AirplaneSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

class AirplaneSteppingAction : public G4UserSteppingAction
{
  public:
    AirplaneSteppingAction();
    virtual ~AirplaneSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};



#endif
