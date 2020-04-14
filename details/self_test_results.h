#ifndef RAYMARINE_QUANTUM_SELF_TEST_RESULTS_H_
#define RAYMARINE_QUANTUM_SELF_TEST_RESULTS_H_

#include "message_id.h"
#include "status.h"

typedef int8_t SelfTestState_t;
const SelfTestState_t cSelfTestNotRun = -1;
const SelfTestState_t cSelfTestFail   = 0;
const SelfTestState_t cSelfTestPass   = 1;

typedef uint8_t SelfTestIndex_t;
const SelfTestIndex_t cPowerupSelfTestGpio            = 0;
const SelfTestIndex_t cPowerupSelfTestAD9963          = 1;
const SelfTestIndex_t cPowerupSelfTestADF4159         = 2;
const SelfTestIndex_t cPowerupSelfTestDspBlock        = 3;
const SelfTestIndex_t cPowerupSelfTestFpga            = 4;
const SelfTestIndex_t cPowerupSelfTestI2C             = 5;
const SelfTestIndex_t cPowerupSelfTestUart            = 6;
const SelfTestIndex_t cPowerupSelfTestWiFi            = 7;
const SelfTestIndex_t cPowerupSelfTestLast            = cPowerupSelfTestWiFi;
const SelfTestIndex_t cRuntimeSelfTestWiFiSpi         = 0;
const SelfTestIndex_t cRuntimeSelfTestAD9963DataLines = 1;
const SelfTestIndex_t cRuntimeSelfTestPsuComms        = 2;
const SelfTestIndex_t cRuntimeSelfTestLimiterDetect   = 3;
const SelfTestIndex_t cRuntimeSelfTestPowerDetect     = 4;
const SelfTestIndex_t cRunTimeSelfTestPALimits        = 5;
const SelfTestIndex_t cRunTimeSelfTestPsuVoltages     = 6;

const SelfTestIndex_t cPowerupSelfTestResultsSize     = 9;
const SelfTestIndex_t cRuntimeSelfTestResultsSize     = 7;

/**
 * 'MainEnableInitialState' 
 * If True, then software has (re)started not from a cold start. Post will not 
 * have been run.
 */
struct PsuPowerOnSelfTestResults_t {
    bool PowerInGood;
    bool StandbyCurrentGood;
    bool MainBoardConnected;
    bool MainEEPROMConnectionGood;
    bool MainSupplyOnVoltagesGood;
    bool MainSupplyOnCurrentGood;
    bool MainEnableInitialState;
    bool POSTRun;
};

struct QUANTUM_SELF_TEST_T {
    SelfTestState_t PowerupSelfTestResults[cPowerupSelfTestResultsSize];
    SelfTestState_t RuntimeSelfTestResults[cRuntimeSelfTestResultsSize];
    PsuPowerOnSelfTestResults_t PsuSelfTestResults;
};

struct SelfTestResultsMsg_t
{
    MESSAGE_TYPE_T MessageCode;
    QUANTUM_SELF_TEST_T SelfTestResults;
};


#endif // RAYMARINE_QUANTUM_SELF_TEST_RESULTS_H_