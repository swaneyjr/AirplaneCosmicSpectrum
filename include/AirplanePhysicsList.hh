// physics list

#ifndef AirplanePhysicsList_h
#define AirplaneDetectorConstruction_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class AirplanePhysicsList : public G4VUserPhysicsList
{
  public:
    AirplanePhysicsList();
    virtual ~AirplanePhysicsList();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

};

#endif
