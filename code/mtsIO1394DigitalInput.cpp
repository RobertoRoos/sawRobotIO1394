/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s):  Zihan Chen, Peter Kazanzides
  Created on: 2011-06-10

  (C) Copyright 2011-2013 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#include <cisstMultiTask/mtsInterfaceProvided.h>
#include <cisstMultiTask/mtsStateTable.h>
#include <cisstParameterTypes/prmEventButton.h>

#include "mtsIO1394DigitalInput.h"

using namespace sawRobotIO1394;


mtsIO1394DigitalInput::mtsIO1394DigitalInput(const cmnGenericObject & owner,
                                             const osaIO1394::DigitalInputConfiguration & config):
    osaIO1394DigitalInput(config),
    OwnerServices(owner.Services())
{
}

void mtsIO1394DigitalInput::SetupStateTable(mtsStateTable & stateTable)
{
    stateTable.AddData(Value_, Name_ + "Value");
}

void mtsIO1394DigitalInput::SetupProvidedInterface(mtsInterfaceProvided * prov, mtsStateTable & stateTable)
{
    prov->AddCommandReadState(stateTable, this->Value_, "GetButton");
    prov->AddEventWrite(this->Button, "Button", prmEventButton());
}

void mtsIO1394DigitalInput::TriggerEvents(void)
{
    prmEventButton pressed = prmEventButton::PRESSED,
        released = prmEventButton::RELEASED;

    // Send appropriate events if the value changed in the last update

    // Check if value has changed
    if (Value_ != PreviousValue_) {
        // Check if the value is equal to the value when the digital input is considered pressed
        if (Value_ == PressedValue_) {
            // Emit a press event
            if (TriggerPress_) {
                Button(pressed);
            }
        } else {
            // Emit a release event
            if (TriggerRelease_) {
                Button(released);
            }
        }
    }
}
