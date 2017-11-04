// source for RunAction

#include "AirplaneRunAction.hh"
#include "g4root.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

AirplaneRunAction::AirplaneRunAction()
 : G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
}

AirplaneRunAction::~AirplaneRunAction()
{
  delete G4AnalysisManager::Instance();
}

void AirplaneRunAction::BeginOfRunAction(const G4Run* /*aRun*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("airplane.root");

  analysisManager->CreateH1("primary", "Primary Proton Spectrum", 100, 0, 10*GeV);
  analysisManager->CreateH1("airplane", "Airplane Proton Spectrum", 100, 0, 10*GeV);
}

void AirplaneRunAction::EndOfRunAction(const G4Run* /*aRun*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
