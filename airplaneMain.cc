// main source file for AirplaneProtonSpectrum

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "AirplaneDetectorConstruction.hh"
#include "Shielding.hh"
#include "AirplaneActionInitialization.hh"

int main(int argc, char** argv) {

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if(argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4RunManager* runManager = new G4RunManager;

  runManager->SetUserInitialization(new AirplaneDetectorConstruction);
  runManager->SetUserInitialization(new Shielding);
  runManager->SetUserInitialization(new AirplaneActionInitialization);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if(!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    UImanager->ApplyCommand("/control/execute init_gps.mac");
    ui->SessionStart();
    delete ui;
  }
  
  delete visManager;
  delete runManager;

  return 0;
}
