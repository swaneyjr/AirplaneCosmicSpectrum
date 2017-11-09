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

#include <algorithm>
#include <glob.h>
#include <iostream>
#include <string>

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
  G4String fname = "interactive.root";
  if ( !ui ) {

    // parse data directory finto filename	  
    G4String data_dir = argv[1];

    // should work whether the user inputs spectra/ dir or not
    G4String spectra_dir = "spectra/";
    if (data_dir.substr(0, spectra_dir.size()) == spectra_dir) {
      data_dir.erase(0, spectra_dir.size());
    }
    
    if (data_dir[data_dir.size()-1] == '/') {
      data_dir.erase(data_dir.size()-1, 1);
    }
    
    // set directory as alias so we can grab data from it
    G4String aliasString = "data_dir " + data_dir;
    const char* aliasLine = aliasString.c_str();
    
    UImanager->SetAlias(aliasLine);

    fname = data_dir + ".root";
    std::replace(fname.begin(), fname.end(), '/', '_'); 

  }

  analysisManager->SetHistoDirectoryName("primaries");
  analysisManager->OpenFile(fname);

  analysisManager->CreateNtuple("hits", "Airplane particle hits");
  
  analysisManager->CreateNtupleSColumn("particle");
  analysisManager->CreateNtupleDColumn("beta_gamma");
  analysisManager->CreateNtupleDColumn("dEdx");
  analysisManager->CreateNtupleDColumn("E_primary");
  analysisManager->CreateNtupleDColumn("y_primary");
  analysisManager->CreateNtupleDColumn("hit_x");
  analysisManager->FinishNtuple();


  if( !ui ) {
    // batch mode
    
    G4String pathname = "spectra/" + UImanager->SolveAlias("{data_dir}") + "/*.dat";
    const char* pathc = pathname.c_str();

    glob_t* pglob = new glob_t();
    glob(pathc, 0, nullptr, pglob);
    G4String particle_str = "";
    const G4int n_particles = pglob->gl_pathc;
    std::vector<G4String> particles(n_particles);
    std::vector<G4double> fluxes(n_particles);

    for(G4int p=0; p < n_particles; p++) {
      if ( p > 0 ) {
        particle_str += " ";
      }	      
      G4String ppath = pglob->gl_pathv[p];

      // first find relative particle abundances
      std::ifstream inFile(ppath);
      G4double lastEnergy = 0;
      G4double lastFlux = 0;
      G4String data_pt;
      while (inFile) {
        std::getline(inFile, data_pt);
        if (data_pt != "") {	
	  G4int i = data_pt.index("\t");
	  if( i < 0 ) {
            i = data_pt.index(" ");
	  } 
	  G4double energy = std::stod(data_pt(0,i));
	  G4double flux = std::stod(data_pt(i+1, data_pt.length()-(i+1)));
	  
	  fluxes[p] += (flux+lastFlux)/2 * (energy-lastEnergy);
	  
	  lastEnergy = energy;
	  lastFlux = flux;
	}
      }
      inFile.close();

      // now parse to find particle name
      // get rid of .dat
      ppath.erase(ppath.size()-4, 4);
      // and leading directory
      ppath.erase(0, pathname.size()-5);
      particles[p] = ppath;
      particle_str += ppath;
    }

    // normalize the particle fluxes
    G4double total_flux = 0;
    for(G4int p=0; p<n_particles; p++) {	    
      total_flux += fluxes[p];
    }
    for(G4int p=0; p<n_particles; p++) {
      G4int nBeamOn = (G4int)(10000000*fluxes[p]/total_flux);    
      G4String fluxAlias = particles[p] + "_primaries " + std::to_string(nBeamOn);
      UImanager->SetAlias(fluxAlias.c_str());
    }

    UImanager->Foreach("macros/singleRun.mac", "pname", particle_str.c_str());

    globfree(pglob);

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
