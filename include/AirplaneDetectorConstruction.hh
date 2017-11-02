// header for DetectorConstruction

#ifndef AirplaneDetectorConstruction_h
#define AirplaneDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VLogicalVolume;
class G4VPhysicalVolume;

class AirplaneDetectorConstruction: public G4VUserDetectorConstruction
{
  public:
    AirplaneDetectorConstruction();
    virtual ~AirplaneDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
