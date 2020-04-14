#ifndef RAYMARINE_QUANTUM_ATTRIBUTES_H_
#define RAYMARINE_QUANTUM_ATTRIBUTES_H_

#include "message_id.h"

const uint8_t cQuantumSerialNumberSize = 16;
const uint8_t cMacAddressSize          = 6;

// Power Down Code
typedef uint8_t PowerDownCode_t;
const PowerDownCode_t cPowerDownCodeNoReason            = 0;
const PowerDownCode_t cPowerDownCodeUserRequest         = 255;
const PowerDownCode_t cPowerDownCodeNoComms             = 254;
const PowerDownCode_t cPowerDownCodePowerFail           = 253;
const PowerDownCode_t cPowerDownCodeAssert              = 252;
const PowerDownCode_t cPowerDownCodeThreadStackLow      = 251;
const PowerDownCode_t cPowerDownCodeThreadTimeout       = 250;
const PowerDownCode_t cPowerDownCodeThreadStackOverflow = 249;

// Status Code
typedef uint8_t StatusCode_t;
static const StatusCode_t cStatusRunningOK                      = 1;
static const StatusCode_t cStatusPADriversError                 = 255;
static const StatusCode_t cStatusSelfTestFailed                 = 254;
static const StatusCode_t cStatusScannerStalled                 = 252;
static const StatusCode_t cStatusWiFiDisconnectNoHeartbeat      = 251;
static const StatusCode_t cStatusWiFiDisconnectLossOfConnection = 250;

// Quantum Roation State
typedef uint8_t QUANTUM_ROTATION_STATE_T;
const QUANTUM_ROTATION_STATE_T QUANTUM_ROTATION_STATE_OFF = 0;
const QUANTUM_ROTATION_STATE_T QUANTUM_ROTATION_STATE_ON = 1;

// Quantum Transmit State
typedef uint8_t QUANTUM_TRANSMIT_STATE_T;
const QUANTUM_TRANSMIT_STATE_T QUANTUM_TRANSMIT_STATE_OFF = 0;
const QUANTUM_TRANSMIT_STATE_T QUANTUM_TRANSMIT_STATE_ON = 1;

// Quantum Prod Test Bits
typedef uint8_t QUANTUM_PROD_TEST_BITS_T;
const QUANTUM_PROD_TEST_BITS_T QUANTUM_PROD_TEST_INT_SHP = 1;
const QUANTUM_PROD_TEST_BITS_T QUANTUM_PROD_TEST_INT_PRI = 2;
const QUANTUM_PROD_TEST_BITS_T QUANTUM_PROD_TEST_PRE_CORR_AVG = 4;
const QUANTUM_PROD_TEST_BITS_T QUANTUM_PROD_TEST_MAX_VALUE =
                                                QUANTUM_PROD_TEST_INT_SHP +
                                                QUANTUM_PROD_TEST_INT_PRI +
                                                QUANTUM_PROD_TEST_PRE_CORR_AVG;

struct QUANTUM_ATTRIBUTES_T {
    uint8_t                  SerialNumber[cQuantumSerialNumberSize];
    uint32_t                 IpAddress;
    uint8_t                  MacAddress[cMacAddressSize];
    uint8_t                  SoftwareVersionMajor;
    uint8_t                  SoftwareVersionMinor;
    uint8_t                  UpdMgrVersionMajor;
    uint8_t                  UpdMgrVersionMinor;
    uint8_t                  BootVersionMajor;
    uint8_t                  BootVersionMinor;
    uint8_t                  FpgaVersionMajor;
    uint8_t                  FpgaVersionMinor;
    uint8_t                  PsuAppVersionMajor;
    uint8_t                  PsuAppVersionMinor;
    uint8_t                  PsuUpdMgrVersionMajor;
    uint8_t                  PsuUpdMgrVersionMinor;
    uint8_t                  PsuBootVersionMajor;
    uint8_t                  PsuBootVersionMinor;
    uint8_t                  WiFiVersionMajor;
    uint8_t                  WiFiVersionMinor;
    uint16_t                 CurrentSignalStrength;
    StatusCode_t             StatusCode;
    PowerDownCode_t          PowerDownCode;
    QUANTUM_ROTATION_STATE_T RotationState;
    QUANTUM_TRANSMIT_STATE_T TransmitState;
    uint16_t                 AzimuthZeroOffset;
    int16_t                  CpuTemp_degCx10;
    uint8_t                  CpuFree;
    QUANTUM_PROD_TEST_BITS_T ProdTestBits;
    bool                     PriJitter;
    uint8_t                  DiagnosticsData[9];
};

struct Attributes_t {
    MESSAGE_TYPE_T m_MessageCode;
    QUANTUM_ATTRIBUTES_T m_Attributes;
};

#endif // RAYMARINE_QUANTUM_ATTRIBUTES_H_