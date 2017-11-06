// source for DetectorConstruction


#include "AirplaneDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
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
  

  G4double world_hxz = 4.0*m;
  G4double world_hy = 2.0*m;
  G4double r_outer = 376./2*cm;
  G4double r_inner = 354./2*cm;

  G4Box* world = new G4Box("World", world_hxz, world_hy, world_hxz);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(world, world_mat, "World");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,
                     G4ThreeVector(), 
                     logicWorld, 
                     "World",
                     0, 
                     false, 
                     0, 
                     false);

  G4Tubs* airplaneSkin = new G4Tubs("Airplane", r_inner, r_outer, world_hxz, 0.*deg, 360.*deg);

  G4LogicalVolume* logicAirplane = new G4LogicalVolume(airplaneSkin, Al, "Airplane");

  new G4PVPlacement(0, 
                    G4ThreeVector(), 
                    logicAirplane, 
                    "Airplane", 
                    logicWorld, 
                    false, 
                    0);

  return physWorld;
}
