/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#ifndef GateReadout_h
#define GateReadout_h 1

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"

#include "GateVPulseProcessor.hh"
#include "GateVSystem.hh"
#include "GateArrayComponent.hh"
#include "GateVBlurringLaw.hh"
#include "GateInverseSquareBlurringLaw.hh"

#define READOUT_POLICY_WINNER 0
#define READOUT_POLICY_CENTROID 1
#define READOUT_POLICY_PLASTIC 2

class GateReadoutMessenger;
class GateOutputVolumeID;

/*! \class  GateReadout
    \brief  Pulse-processor modelling a simple PMT readout (maximum energy wins) of a crystal-block

    - GateReadout - by Daniel.Strul@iphe.unil.ch

    - The readout is parameterised by its 'depth': pulses will be summed up if their volume IDs
      are identical up to this depth. For instance, the default depth is 1: this means that
      pulses will be considered as taking place in a same block if the first two figures
      of their volume IDs are identical

      \sa GateVPulseProcessor
*/
class GateReadout : public GateVPulseProcessor
{
  public:

    //! Constructs a new readout attached to a GateDigitizer
    GateReadout(GatePulseProcessorChain* itsChain,const G4String& itsName) ;

    //! Destructor
    virtual ~GateReadout() ;

    //! Implementation of the pure virtual method declared by the base class GateClockDependent
    //! print-out the attributes specific of the readout
    virtual void DescribeMyself(size_t indent);

    //! Returns the depth of the readout
    inline G4int GetDepth() const  	      	{ return m_depth; }

    //! Set the depth of the readout
    inline void  SetDepth(G4int aDepth)         { m_depth = aDepth; }

    inline void SetEnergy(G4double aEnergy) {m_energy = aEnergy;}

    //! Set the policy of the readout
    void SetPolicy(const G4String& aPolicy);

    //! Set the policy of the readout
    inline void SetLayerName(const G4String& a_layerName) {m_layerName = a_layerName;}

    inline void SetEnergyResolutionCrystal(G4double aEnergyRes) {m_energy_res_crystal = aEnergyRes;}

    inline void SetEnergyReferenceCrystal(G4double aEnergyRes) {m_energy_ref_crystal = aEnergyRes;}

    inline void SetEnergyResolutionPlstc(G4double aEnergyRes) {m_energy_res_plstc = aEnergyRes;}

    inline void SetEnergyReferencePlstc(G4double aEnergyRes) {m_energy_ref_plstc = aEnergyRes;}


  protected:
    //! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
    //! This methods processes one input-pulse
    //! It is is called by ProcessPulseList() for each of the input pulses
    //! The result of the pulse-processing is incorporated into the output pulse-list
    void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList);
    //! Overload the virtual (not pure) method of GateVPulseProcessor
    GatePulseList* ProcessPulseList(const GatePulseList* inputPulseList);

  private:
    //! The default is the one parameter that defines how a readout works:
    //! pulses will be summed up if their volume IDs are identical up to this depth.
    //! For instance, the default depth is 1: this means that pulses will be considered as
    //! taking place in a same block if the first two figures of their volume IDs are identical
    G4int m_depth;

    //! S. Stute: add an option to choose the policy of the readout (using two define integers; see the beginning of this file)
    G4int m_policy;
    GateVSystem* m_system;
    G4int m_nbCrystalsX;
    G4int m_nbCrystalsY;
    G4int m_nbCrystalsZ;
    G4int m_nbCrystalsXY;
    G4int m_systemDepth;
    G4int m_crystalDepth;
    G4String m_layerName;
    G4double m_energy;
    G4double m_energy_res_crystal;
    G4double m_energy_res_plstc;
    G4double m_energy_ref_crystal;
    G4double m_energy_ref_plstc;
    GateArrayComponent* m_crystalComponent;
    GateVBlurringLaw* m_blurringLaw;

    GateReadoutMessenger *m_messenger;	  //!< Messenger for this readout
};


#endif
