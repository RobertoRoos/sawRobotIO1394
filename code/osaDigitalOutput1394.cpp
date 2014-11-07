/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  Author(s):  Anton Deguet
  Created on: 2014-11-06

  (C) Copyright 2014 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#include <sawRobotIO1394/osaDigitalOutput1394.h>

#include "FirewirePort.h"
#include "AmpIO.h"

using namespace sawRobotIO1394;

osaDigitalOutput1394::osaDigitalOutput1394(const osaDigitalOutput1394Configuration & config):
    mDigitalOutputBits(0x0),
    mValue(false)
{
    this->Configure(config);
}

void osaDigitalOutput1394::Configure(const osaDigitalOutput1394Configuration & config)
{
    // Store configuration
    mConfiguration = config;
    mName = config.Name;
    mBitID = config.BitID;
    mBitMask = 0x1 << mBitID;

    // Set the value
    mValue = false;
}

void osaDigitalOutput1394::SetBoard(AmpIO * board)
{
    if (board == 0) {
        cmnThrow(osaRuntimeError1394(this->Name() + ": invalid board pointer."));
    }
    mBoard = board;
}

void osaDigitalOutput1394::PollState(void)
{
    // Get the new value
    mDigitalOutputBits =  mBoard->GetDigitalOutput();

    // Use masked bit
    mValue = (mDigitalOutputBits & mBitMask);
}

const osaDigitalOutput1394Configuration & osaDigitalOutput1394::Configuration(void) const {
    return mConfiguration;
}

const std::string & osaDigitalOutput1394::Name(void) const {
    return mName;
}

const bool & osaDigitalOutput1394::Value(void) const {
    return mValue;
}
