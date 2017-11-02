// header for ActionInitialization

#ifndef AirplaneActionInitialization_h
#define AirplaneActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class AirplaneActionInitialization: public G4VUserActionInitialization
{
  public:
    AirplaneActionInitialization();
    virtual ~AirplaneActionInitialization();

    virtual void Build() const;
};

#endif
