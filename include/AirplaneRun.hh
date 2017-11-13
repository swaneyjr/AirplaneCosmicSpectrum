// header for Run

#ifndef AirplaneRun_h
#define AirplaneRun_h 1

#include "G4Run.hh"

#include "G4THitsMap.hh"
#include "globals.hh"

class AirplaneRun : public G4Run
{
  public:
    AirplaneRun();
    virtual ~AirplaneRun();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

    void SaveToNtuple() const;

  private:
    std::vector<G4int> fCollIDs;
    std::vector<G4THitsMap<G4double>> fRunMaps;  
};

#endif
