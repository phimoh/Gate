 
/*----------------------
   Copyright (C): University of Hull

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#include "GateMultTemporalResolution.hh"

#include "G4UnitsTable.hh"

#include "GateMultTemporalResolutionMessenger.hh"
#include "GateTools.hh"

#include "Randomize.hh"
#include "GateConstants.hh"


GateMultTemporalResolution::GateMultTemporalResolution(GatePulseProcessorChain* itsChain,
                                                       const G4String& itsName,
                                                       G4double itsTimeResolution_1,
                                                       G4double itsTimeResolution_2,
                                                       G4double itsTimeResolution_3)
  : GateVPulseProcessor(itsChain, itsName),
    m_timeResolution1(itsTimeResolution_1),
    m_timeResolution2(itsTimeResolution_2),
    m_timeResolution3(itsTimeResolution_3)
{
  m_messenger = new GateMultTemporalResolutionMessenger(this);
}




GateMultTemporalResolution::~GateMultTemporalResolution()
{
  delete m_messenger;
}



void GateMultTemporalResolution::ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList)
{
  if(m_timeResolution1 < 0 || m_timeResolution2 < 0 || m_timeResolution3 < 0) {
    G4cerr << 	Gateendl << "[GateTemporalResolution::ProcessOnePulse]:\n"
           <<   "Sorry, but the resolutions (" << GetTimeResolution(1) << ", " << GetTimeResolution(2) << ", " << GetTimeResolution(3) << ") are invalid\n";
    G4Exception( "GateTemporalResolution::ProcessOnePulse", "ProcessOnePulse", FatalException,
            "You must choose temporal resolutions >= 0 /gate/digitizer/Singles/Singles/timeResolution/setTimeResolution TIME_1 TIME_2 TIME_3"
            "\n or disable the temporal resolution using:\n\t/gate/digitizer/Singles/Singles/timeResolution/disable\n");
  }
  else {
    if (!inputPulse) {
      if (nVerboseLevel>1)
    G4cout << "[GateTemporalResolution::ProcessOnePulse]: input pulse was null -> nothing to do\n\n";
      return;
    }

    if (inputPulse)
      {
    GatePulse* outputPulse = new GatePulse(*inputPulse);
    // set the new time by a Gaussian shot of mean: old time, and of sigma: m_timeResolution/2.35
    G4double sigma =  m_timeResolution1 / GateConstants::fwhm_to_sigma;
    outputPulse->SetTime(G4RandGauss::shoot(inputPulse->GetTime(), sigma));
    outputPulseList.push_back(outputPulse);

    if (nVerboseLevel>1)
      {
        G4cout << "Pulse real time: \n"
           << G4BestUnit(inputPulse->GetTime(),"Time") << Gateendl
           << "Pulse new time: \n"
           << G4BestUnit(outputPulse->GetTime(),"Time") << Gateendl
           << "Difference (real - new time): \n"
           << G4BestUnit(inputPulse->GetTime() - outputPulse->GetTime(),"Time")
           << Gateendl << Gateendl ;

      }
      }
  }
}


void GateMultTemporalResolution::DescribeMyself(size_t indent)
{
//  G4cout << GateTools::Indent(indent) << "Temporal resolutions: " << G4BestUnit(m_timeResolution,"Time") << Gateendl;
}
