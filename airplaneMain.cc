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
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  G4UIExecutive* ui = 0;

  // set default values
  
  UImanager->SetAlias("alt 0");
  UImanager->SetAlias("shield 1");
  UImanager->SetAlias("t 3600");


  if(argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  } else {
    G4String prefix = "--";
    for (G4int argi=1; argi < argc; argi++) {
      G4String arg = G4String(argv[argi]);
      if (!arg.compare(0, prefix.length(), prefix)) {
        G4String var = arg.substr(prefix.length());
	G4String val = G4String(argv[++argi]);
	UImanager->SetAlias((var+" "+val).c_str());
      }
    }
  }

  G4RunManager* runManager = new G4RunManager;

  runManager->SetVerboseLevel(0);
  runManager->SetUserInitialization(new AirplaneDetectorConstruction);
  runManager->SetUserInitialization(new QGSP_BERT);
  runManager->SetUserInitialization(new AirplaneActionInitialization);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  // set up particle source
  G4double half_x = 4656*.00112/2*mm;
  G4double half_y = 4.0*m;
  G4double source_area = 4*half_x*half_y;

  G4String aliasX = "half_x_m " + std::to_string(half_x/m);
  G4String aliasY = "half_y_m " + std::to_string(half_y/m);
  UImanager->SetAlias(aliasX.c_str());
  UImanager->SetAlias(aliasY.c_str());
  UImanager->ExecuteMacroFile("macros/init_gps.mac");

  // make analysis files
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4String fname = "interactive.root";
  if ( !ui ) {

    fname = "alt" + UImanager->SolveAlias("{alt}")
      + "_shield" + UImanager->SolveAlias("{shield}")
      + "_t" + UImanager->SolveAlias("{t}") + ".root";

  }

  analysisManager->SetHistoDirectoryName("primaries");
  analysisManager->OpenFile(fname);

  analysisManager->CreateNtuple("hits", "Airplane particle hits");
  
  analysisManager->CreateNtupleSColumn("particle");
  analysisManager->CreateNtupleDColumn("Eparticle");
  analysisManager->CreateNtupleSColumn("primary");
  analysisManager->CreateNtupleDColumn("Eprimary");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->CreateNtupleDColumn("xVertex");
  analysisManager->CreateNtupleDColumn("yVertex");
  analysisManager->CreateNtupleDColumn("xSensor");
  analysisManager->FinishNtuple();


  if( !ui ) {
    // batch mode
    
    G4String pathname = "spectra/" + UImanager->SolveAlias("{alt}") + "/*.dat";
    G4double run_time = std::stod(UImanager->SolveAlias("{t}"))*s;
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
	  G4double energy = std::stod(data_pt(0,i)) * MeV;
	  G4double flux = std::stod(data_pt(i+1, data_pt.length()-(i+1)))
		  / (MeV * s * cm2);
	  
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
    for(G4int p=0; p<n_particles; p++) {
      G4int nBeamOn = (G4int)(fluxes[p]*source_area*run_time);    
      G4String fluxAlias = particles[p] + "_primaries " + std::to_string(nBeamOn);
      UImanager->SetAlias(fluxAlias.c_str());
    }

    UImanager->Foreach("macros/singleRun.mac", "pname", particle_str.c_str());

    globfree(pglob);

  } else {
    // interactive mode
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
