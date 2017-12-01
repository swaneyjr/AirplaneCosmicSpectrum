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
  

  const G4double world_hxz = 4.0*m;
  const G4double world_hy = 2.0*m;
  const G4double r_outer = 376./2*cm;
  const G4double skin_thickness = 1.*mm;
  const G4double r_inner = r_outer - skin_thickness;
  const G4double sensor_hy = .001*mm;

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
  		  logicWorld, 
  		  false, 
  		  0);

  new G4PVPlacement(0,
                  G4ThreeVector(),
                  logicAirplane,
                  "Airplane",
                  logicWorld,
                  false,
                  0);

  fSensorLV = logicSensor;
    
  return physWorld;
}


