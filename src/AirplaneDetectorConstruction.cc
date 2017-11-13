// source for DetectorConstruction


#include "AirplaneDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDParticleFilter.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

AirplaneDetectorConstruction::AirplaneDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

AirplaneDetectorConstruction::~AirplaneDetectorConstruction()
{ }

G4VPhysicalVolume* AirplaneDetectorConstruction::Construct()
{	
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Si = nist->FindOrBuildMaterial("G4_Si");
  

  G4double world_hxz = 4.0*m;
  G4double world_hy = 2.0*m;
  G4double r_outer = 376./2*cm;
  G4double r_inner = 354./2*cm;
  G4double sensor_hy = .001*mm;

  G4Box* world = new G4Box("World", world_hxz, world_hy, world_hxz);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(world, world_mat, "World");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,
                     G4ThreeVector(), 
                     logicWorld, 
                     "World",
                     0, 
                     false, 
                     0, 
                     true);

  G4Tubs* airplaneSkin = new G4Tubs("Airplane", r_inner, r_outer, world_hxz, 0.*deg, 360.*deg);

  G4LogicalVolume* logicAirplane = new G4LogicalVolume(airplaneSkin, Al, "AirplaneLV");

  G4Box* sensor = new G4Box("sensorbox", r_inner-sensor_hy, sensor_hy, world_hxz);

  G4LogicalVolume* logicSensor = new G4LogicalVolume(sensor, Si, "sensorLV");

  new G4PVPlacement(0, 
  		  G4ThreeVector(),
  		  logicSensor, 
  		  "sensorphys", 
  		  logicAirplane, 
  		  false, 
  		  0);

  new G4PVPlacement(0,
                  G4ThreeVector(),
                  logicAirplane,
                  "Airplane",
                  logicWorld,
                  false,
                  0);

  fSensorLV = logicAirplane;
    
  return physWorld;
}

/*
void AirplaneDetectorConstruction::ConstructSDandField()
{
 
  // add the camera sensor as a detector
  G4MultiFunctionalDetector* cameraSensor = new G4MultiFunctionalDetector("sensor");
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->AddNewDetector(cameraSensor);
  
  G4SDParticleFilter* protonFilter 
	  = new G4SDParticleFilter("protonFilter", "proton");
  G4SDParticleFilter* neutronFilter
	  = new G4SDParticleFilter("neutronFilter", "neutron");
  G4SDParticleFilter* gammaFilter
	  = new G4SDParticleFilter("gammaFilter", "gamma");
  G4SDParticleFilter* betaFilter
	  = new G4SDParticleFilter("betaFilter");
  G4SDParticleFilter* muFilter
	  = new G4SDParticleFilter("muFilter");

  betaFilter->add("e-");
  betaFilter->add("e+");

  muFilter->add("mu-");
  muFilter->add("mu+");

  G4PSEnergyDeposit* eDep;
  eDep = new G4PSEnergyDeposit("eProton");
  eDep-> SetFilter(protonFilter);
  cameraSensor->RegisterPrimitive(eDep);

  eDep = new G4PSEnergyDeposit("eNeutron");
  eDep-> SetFilter(neutronFilter);
  cameraSensor->RegisterPrimitive(eDep);

  eDep = new G4PSEnergyDeposit("eGamma");
  eDep-> SetFilter(gammaFilter);
  cameraSensor->RegisterPrimitive(eDep);

  eDep = new G4PSEnergyDeposit("eBeta");
  eDep-> SetFilter(betaFilter);
  cameraSensor->RegisterPrimitive(eDep);

  eDep = new G4PSEnergyDeposit("eMu");
  eDep-> SetFilter(muFilter);
  cameraSensor->RegisterPrimitive(eDep);

  fSensorLV->SetSensitiveDetector(cameraSensor);
  
}
*/
