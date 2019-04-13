/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#ifndef GateMultTemporalResolutionMessenger_h
#define GateMultTemporalResolutionMessenger_h 1

#include "GatePulseProcessorMessenger.hh"

class G4UIcmdWithADoubleAndUnit;

class GateMultTemporalResolution;

class GateMultTemporalResolutionMessenger: public GatePulseProcessorMessenger
{
  public:
    GateMultTemporalResolutionMessenger(GateMultTemporalResolution* itsTemporalResolution);
    virtual ~GateMultTemporalResolutionMessenger();

    inline void SetNewValue(G4UIcommand* aCommand, G4String aString);

    inline GateMultTemporalResolution* GetTemporalResolution()
      { return (GateMultTemporalResolution*) GetPulseProcessor(); }

  private:
    G4UIcmdWithADoubleAndUnit   *timeResolutionCmd1;
    G4UIcmdWithADoubleAndUnit   *timeResolutionCmd2;
    G4UIcmdWithADoubleAndUnit   *timeResolutionCmd3;
};

#endif

