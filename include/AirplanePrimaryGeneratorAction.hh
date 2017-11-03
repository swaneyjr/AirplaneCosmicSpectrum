// header for PrimaryGeneratorAction

#ifndef AirplanePrimaryGeneratorAction_h
#define AirplanePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"


class G4ParticleGun;
class G4Event;

class AirplanePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    AirplanePrimaryGeneratorAction();
    ~AirplanePrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);    

    const G4GeneralParticleSource* GetParticleGun() const { return fParticleGun; }

  private:
    G4GeneralParticleSource* fParticleGun;

};

#endif
