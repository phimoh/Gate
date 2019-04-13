/*----------------------
   Copyright (C): University of Hull

----------------------*/


#include "GateMultTemporalResolutionMessenger.hh"

#include "GateMultTemporalResolution.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"

GateMultTemporalResolutionMessenger::GateMultTemporalResolutionMessenger(GateMultTemporalResolution* itsTemporalResolution)
    : GatePulseProcessorMessenger(itsTemporalResolution)
{
    G4String guidance;
    G4String cmdName1;
    G4String cmdName2;
    G4String cmdName3;

    cmdName1 = GetDirectoryName() + "setMultTimeResolution_1";
    timeResolutionCmd1 = new G4UIcmdWithADoubleAndUnit(cmdName1,this);
    timeResolutionCmd1->SetGuidance("Set the temporal resolution with time unity (for expemple: 1 ns) for pulse-discrimination");
    timeResolutionCmd1->SetUnitCategory("Time");

    cmdName2 = GetDirectoryName() + "setMultTimeResolution_2";
    timeResolutionCmd2 = new G4UIcmdWithADoubleAndUnit(cmdName2,this);
    timeResolutionCmd2->SetGuidance("Set the temporal resolution with time unity (for expemple: 1 ns) for pulse-discrimination");
    timeResolutionCmd2->SetUnitCategory("Time");

    cmdName3 = GetDirectoryName() + "setMultTimeResolution_3";
    timeResolutionCmd3 = new G4UIcmdWithADoubleAndUnit(cmdName3,this);
    timeResolutionCmd3->SetGuidance("Set the temporal resolution with time unity (for expemple: 1 ns) for pulse-discrimination");
    timeResolutionCmd3->SetUnitCategory("Time");

}


GateMultTemporalResolutionMessenger::~GateMultTemporalResolutionMessenger()
{
    delete timeResolutionCmd1;
    delete timeResolutionCmd2;
    delete timeResolutionCmd3;
}


void GateMultTemporalResolutionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if ( command==timeResolutionCmd1 )
    { GetTemporalResolution()->SetTimeResolution(timeResolutionCmd1->GetNewDoubleValue(newValue)); }
    else if(command==timeResolutionCmd2)
    { GetTemporalResolution()->SetTimeResolution(timeResolutionCmd2->GetNewDoubleValue(newValue),2); }
    else if(command ==timeResolutionCmd3)
    { GetTemporalResolution()->SetTimeResolution(timeResolutionCmd3->GetNewDoubleValue(newValue),3); }
    else
        GatePulseProcessorMessenger::SetNewValue(command,newValue);
}
