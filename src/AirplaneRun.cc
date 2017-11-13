// source for Run

#include "AirplaneRun.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "g4root.hh"

AirplaneRun::AirplaneRun()
 : G4Run()
{ 
  fCollIDs = std::vector<G4int>();
  fRunMaps = std::vector<G4THitsMap<G4double>>();
	
  G4SDManager* man = G4SDManager::GetSDMpointer();	
  fCollIDs.push_back(man->GetCollectionID("sensor/eProton"));
  //fCollIDs.push_back(man->GetCollectionID("sensor/eNeutron"));
  //fCollIDs.push_back(man->GetCollectionID("sensor/eGamma"));
  //fCollIDs.push_back(man->GetCollectionID("sensor/eBeta"));
  //fCollIDs.push_back(man->GetCollectionID("sensor/eMu"));

  G4cout << "Checking IDs ";
  for(unsigned int i=0; i<fCollIDs.size(); i++) G4cout << i << " ";
  G4cout << "\n";
}

AirplaneRun::~AirplaneRun()
{ }

void AirplaneRun::RecordEvent(const G4Event* anEvent)
{
  G4cout << "Recording event \n";
  G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();
  if (!HCE) return;
  for (unsigned int i=0; i<fCollIDs.size(); i++) {
    G4THitsMap<G4double>* evtMap 
	    = (G4THitsMap<G4double>*)(HCE->GetHC(fCollIDs[i]));
    fRunMaps[i] += *evtMap;
  }
  G4Run::RecordEvent(anEvent);
}

void AirplaneRun::Merge(const G4Run* aRun)
{
  const AirplaneRun* localRun = static_cast<const AirplaneRun*>(aRun);
  for (unsigned int i=0; i<fRunMaps.size(); i++) {
    fRunMaps[i] += localRun->fRunMaps[i];
  }

  G4Run::Merge(aRun);
}

void AirplaneRun::SaveToNtuple() const
{
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  for(unsigned int i=0; i<fRunMaps.size(); i++) {
    std::map<G4int, G4double*>::iterator itr = fRunMaps[i].GetMap()->begin();                             
    for (; itr != (fRunMaps[i].GetMap()->end()); itr++) {
	  
      analysisManager->FillNtupleSColumn(0, "particleName");                                              
      analysisManager->FillNtupleDColumn(1, *(itr->second));
      analysisManager->AddNtupleRow();
    }
  }     
  
}  
