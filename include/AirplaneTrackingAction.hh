// header for TrackingAction

#ifndef AirplaneTrackingAction_h
#define AirplaneTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "globals.hh"

class AirplaneTrackingAction : public G4UserTrackingAction
{
  public:
    AirplaneTrackingAction();
    virtual ~AirplaneTrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track* aTrack);

    void AddEdep(G4double edep) { fEdep += edep; }
    void SetBetaGamma(G4double bg) { fBetaGamma = bg; }
    void SetSensorX(G4double x) { fSensorX = x; }
    void SetHit() { fHit = true; }
    G4bool AlreadyHit() { return fHit; }

  private:  
    G4double fEdep;
    G4bool fHit;
    G4double fBetaGamma;
    G4double fSensorX;

};

#endif
