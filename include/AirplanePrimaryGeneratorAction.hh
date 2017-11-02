// header for PrimaryGeneratorAction

#ifndef AirplanePrimaryGeneratorAction_h
#define AirplanePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


class G4ParticleGun;
class G4Event;

class AirplanePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    AirplanePrimaryGeneratorAction();
    ~AirplanePrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);    

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun* fParticleGun;

};

#endif
