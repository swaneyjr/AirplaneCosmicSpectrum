// main source file for AirplaneProtonSpectrum

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "AirplaneDetectorConstruction.hh"
#include "QGSP_BERT.hh"
#include "AirplaneActionInitialization.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"
#include "globals.hh"

int main(int argc, char** argv) {

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if(argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4RunManager* runManager = new G4RunManager;

  runManager->SetUserInitialization(new AirplaneDetectorConstruction);
  runManager->SetUserInitialization(new QGSP_BERT);
  runManager->SetUserInitialization(new AirplaneActionInitialization);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  UImanager->ExecuteMacroFile("macros/init_gps.mac");
  
  // make analysis files
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4String fname = "cosmics.root";
  if (argc == 2) {
    G4String basename = argv[1];  
    fname = basename + ".root";	  
  } else if (argc > 2) {
    fname = argv[2];
  }
  analysisManager->OpenFile(fname);

  analysisManager->CreateNtuple("hits", "Airplane particle hits");
  
  analysisManager->CreateNtupleSColumn("particle");
  analysisManager->CreateNtupleDColumn("beta_gamma");
  analysisManager->CreateNtupleDColumn("dEdx");
  analysisManager->CreateNtupleDColumn("E_primary");
  analysisManager->CreateNtupleDColumn("y_primary");
  analysisManager->CreateNtupleDColumn("hit_x");
  analysisManager->FinishNtuple();

  if(!ui) {
    // batch mode
    
    G4String data_dir = argv[1];

    // should work whether the user inputs spectra/ dir or not
    G4String spectra_dir = "spectra/";
    if (data_dir.substr(0, spectra_dir.size()) == spectra_dir) {
      data_dir.erase(0, spectra_dir.size());
    }

    if (data_dir[data_dir.size()-1] != '/') {
      data_dir += '/';
    }

    // set directory as alias so we can grab data from it
    G4String aliasString = "data_dir " + data_dir;
    const char* aliasLine = aliasString.c_str();

    UImanager->SetAlias(aliasLine);
    UImanager->Foreach("macros/forEachSpectrum.mac", "pname", "proton neutron mu+ mu- e+ e- gamma alpha");

  } else {
    // interactive mode
    UImanager->SetAlias("data_dir ground/");
    UImanager->SetAlias("pname mu-");
    UImanager->ExecuteMacroFile("macros/singleRun.mac");
    UImanager->ExecuteMacroFile("macros/init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  analysisManager->Write();
  analysisManager->CloseFile();

  delete analysisManager;
  delete visManager;
  delete runManager;

  return 0;
}
