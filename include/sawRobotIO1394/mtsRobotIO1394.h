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

#ifndef _mtsRobotIO1394_h
#define _mtsRobotIO1394_h

#include <ostream>
#include <iostream>
#include <vector>

#include <cisstMultiTask/mtsTaskPeriodic.h>

class FirewirePort;
class AmpIO;

namespace sawRobotIO1394 {
    class osaIO1394Port;
    class mtsIO1394Robot;
    class mtsIO1394DigitalInput;
}

class mtsRobotIO1394 : public mtsTaskPeriodic {

    CMN_DECLARE_SERVICES(CMN_DYNAMIC_CREATION_ONEARG, CMN_LOG_ALLOW_DEFAULT);
public:
    enum { MAX_BOARDS = 16 };

protected:

    class RobotInternal;
    class DigitalInInternal;

    std::ostream * MessageStream;             // Stream provided to the low level boards for messages, redirected to cmnLogger

    sawRobotIO1394::osaIO1394Port * io1394_port_;
    std::vector<sawRobotIO1394::mtsIO1394Robot*> robots_;
    std::vector<sawRobotIO1394::mtsIO1394DigitalInput*> digital_inputs_;

    ///////////// Public Class Methods ///////////////////////////
public:
    // Constructor & Destructor
    mtsRobotIO1394(const std::string & name, double period, int port_num);
    mtsRobotIO1394(const mtsTaskPeriodicConstructorArg & arg); // TODO: add port_num
    virtual ~mtsRobotIO1394();

    void Init(int port_num);

    void Configure(const std::string & filename);
    bool SetUpRobot(sawRobotIO1394::mtsIO1394Robot * robot);
    bool SetUpDigitalIn(sawRobotIO1394::mtsIO1394DigitalInput * digital_in);
    void Startup(void);
    void Run(void);
    void TriggerEvents(void);
    void Cleanup(void);
    void GetNumberOfDigitalInputs(int & placeHolder) const;

protected:

    void GetNumberOfBoards(int & placeHolder) const;
    void GetNumberOfRobots(int & placeHolder) const;

    void GetNumberOfActuatorPerRobot(vctIntVec & placeHolder) const;
    void GetName(std::string & placeHolder) const;


    ////////////// Private Class Methods /////////////////////////////
private:
    // Make uncopyable
    mtsRobotIO1394(const mtsRobotIO1394 &);
    mtsRobotIO1394 &operator=(const mtsRobotIO1394 &);
};

CMN_DECLARE_SERVICES_INSTANTIATION(mtsRobotIO1394);

#endif // _mtsRobotIO1394_h
