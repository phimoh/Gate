/*----------------------
   Copyright (C): University of Hull


----------------------*/


#ifndef GateMultTemporalResolution_h
#define GateMultTemporalResolution_h 1

#include "globals.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include "G4ThreeVector.hh"

#include "GateVPulseProcessor.hh"


class GateMultTemporalResolutionMessenger;


/*! \class  GateMultTemporalResolution
    \brief  Pulse-processor modeling a Gaussian blurring on the time of the pulse.
    Mulitple temporal resolution can be applied based on conditions. This class is
    based on the GateTemporalResolution .

    - GateMultTemporalResolution - by n.efthymiou@hull.ac.uk (April 2019)

    \sa GateVPulseProcessor
*/
class GateMultTemporalResolution : public GateVPulseProcessor
{
  public:

    //! Constructs a new temporal resolution attached to a GateDigitizer
    GateMultTemporalResolution(GatePulseProcessorChain* itsChain,
                               const G4String& itsName=theTypeName,
                               G4double itsTimeResolution_1=0.,
                               G4double itsTimeResolution_2=0.,
                               G4double itsTimeResolution_3=0.) ;
    //! Destructor
    virtual ~GateMultTemporalResolution() ;

    //! Returns the time resolution
    G4double GetTimeResolution(G4int indent = 0)
    {
        switch (indent) {
            case 2:
            return m_timeResolution2;
        case 3:
            return m_timeResolution3;
        default:
            return m_timeResolution1;
        }
    }

    //! Set the time resolution
    void SetTimeResolution(G4double val, G4int indent = 0)
    {
        switch (indent) {
            case 2:
            m_timeResolution2 = val;
            break;
        case 3:
            m_timeResolution3 = val;
            break;
        default:
            m_timeResolution1 = val;
            break;
        }

    }

    void SetTimeResolution(const G4ThreeVector& itsResVector)
    {
        m_timeResolution1 = itsResVector.x();
        m_timeResolution2 = itsResVector.y();
        m_timeResolution3 = itsResVector.z();
    }

    //! Implementation of the pure virtual method declared by the base class GateDigitizerComponent
    //! print-out the attributes specific of the timeResolutioner
    virtual void DescribeMyself(size_t indent);

  protected:
    //! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
    //! This methods processes one input-pulse
    //! It is is called by ProcessPulseList() for each of the input pulses
    //! The result of the pulse-processing is incorporated into the output pulse-list
    void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList&  outputPulseList);

  private:
    G4double m_timeResolution1, m_timeResolution2, m_timeResolution3;     	      	      //!< TimeResolution value
    GateMultTemporalResolutionMessenger *m_messenger;    //!< Messenger
   static const G4String& theTypeName;   //!< Default type-name for all blurrings
};


#endif

