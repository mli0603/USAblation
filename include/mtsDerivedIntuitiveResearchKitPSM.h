/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  Author(s):  Max Li
  Created on: 2020-01-24

  (C) Copyright 2017 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#ifndef MTSDERIVEDINTUITIVERESEARCHKITPSM_H
#define MTSDERIVEDINTUITIVERESEARCHKITPSM_H

#include <sawIntuitiveResearchKit/mtsIntuitiveResearchKitPSM.h>
#include <sawConstraintController/mtsVFController.h>

#include <sawConstraintController/mtsVFController.h>
#include <sawConstraintController/mtsVFFollow.h>
#include <sawConstraintController/mtsVFLimitsConstraint.h>
#include <sawConstraintController/mtsVFMesh.h>
#include <sawConstraintController/mtsVFDataBase.h>
#include <sawConstraintController/mtsVFDataJointLimits.h>
#include <sawConstraintController/mtsVFDataMesh.h>

class mtsDerivedIntuitiveResearchKitPSM : public mtsIntuitiveResearchKitPSM
{
    CMN_DECLARE_SERVICES(CMN_DYNAMIC_CREATION_ONEARG, CMN_LOG_ALLOW_DEFAULT);
public:
    typedef mtsIntuitiveResearchKitPSM BaseType;

    mtsDerivedIntuitiveResearchKitPSM(const std::string & componentName, const double periodInSeconds);
    ~mtsDerivedIntuitiveResearchKitPSM(){}

    void Configure(const std::string & CMN_UNUSED(filename));

protected:
    // constraint controller
    mtsVFController *mController;
    mtsVFDataBase mTeleopObjective; // No additional data needed, therefore using mtsVFBase
    mtsVFDataJointLimits mJointLimitsConstraint;
    cisstMesh mMeshFile;
    mtsVFDataMesh mMesh;
    void SetupVF();

    // robot data for constraint controller
    prmKinematicsState mMeasuredKinematics; // follow crtk convention
    prmKinematicsState mGoalKinematics;
    int mNumDof;
    void SetupRobot();

    nmrConstraintOptimizer::STATUS Solve(vctDoubleVec & dq);
    void UpdateOptimizerKinematics();
};


CMN_DECLARE_SERVICES_INSTANTIATION(mtsDerivedIntuitiveResearchKitPSM);

#endif // MTSDERIVEDINTUITIVERESEARCHKITPSM_H