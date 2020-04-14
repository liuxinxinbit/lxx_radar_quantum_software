#ifndef RAYMARINE_QUANTUM_DIAGNOSTICS_DATA_PACKET_H_
#define RAYMARINE_QUANTUM_DIAGNOSTICS_DATA_PACKET_H_

#include "message_id.h"
#include "request_diagnostics_data.h"

const uint8_t cSerialNumberLength = 8;
const uint8_t cDateTimeStrLength  = 16;

struct ProductionTestData_t {
    uint8_t EMSCode;
    uint8_t ICTPassFailFlag;
    uint8_t EOLPassFailFlag;
    uint8_t FATEPassFailFlag; // PSU only
    uint8_t ICTCount;
    uint8_t EOLCount;
    uint8_t FATECount; // PSU only
    uint8_t PCBSerialNumber[cSerialNumberLength];
    uint8_t TLASerialNumber[cSerialNumberLength];
    uint8_t ICTTimeDate[cDateTimeStrLength];
    uint8_t EOLTimeDate[cDateTimeStrLength];
    uint8_t FATETimeDate[cDateTimeStrLength]; // PSU only
    uint32_t IDacOffset; // Main only
    uint32_t QDacOffset; // Main Only
    int16_t CoeffRajerA11; // IQ impairment co-efficients
    int16_t CoeffRajerA12;
    int16_t CoeffRajerA21;
    int16_t CoeffRajerA22;
};

/**
 * Parameters 
 * ‘RequestType’ - cQuantumDiagReqCrashLog
 * ‘DataLength’ – Length of data field in bytes
 * ‘Data’ – Text field describing crash
 */

static const uint32_t cMaxCrashLogDataSize = 512;

struct CrashLogData_t
{
    MESSAGE_TYPE_T MessageCode;
    QuantumDiagReq_t RequestType;
    uint32_t         DataLength;
    uint8_t          Data[cMaxCrashLogDataSize];
};

struct PsuPowerSupplyStatus_t {
    uint32_t InputVoltage_x10000;
    uint32_t InputCurrent_x10000;
    uint8_t  InputPowerGood;
    uint8_t  MainSupplyPowerGood;
    uint8_t  ADP5050Channel1PowerGood;
    uint8_t  ADP1821PowerGood;
    uint32_t Main12vVoltage_x10000;
    uint32_t Main50vVoltage_x10000;
    uint32_t Main6vVoltage_x10000;
    int32_t  Mainneg8vVoltage_x10000;
    uint32_t MotorCurrent_x10000;
};

struct PsuStatus_t {
    MESSAGE_TYPE_T         MessageCode;
    PsuPowerSupplyStatus_t PsuStatus;
};

struct PsuRotationStats_t {
    uint32_t TimeBetweenSHPs;
    uint32_t MotorPulsesBetweenSHPs;
    uint32_t SHPCount;
    uint32_t InstantaniousMotorCurrent;
    uint8_t  MotorPulsesAsExpected;
    uint8_t  spare1;
    uint8_t  spare2;
    uint8_t  spare3;
};

struct PsuRotationStatsMsg_t {
    MESSAGE_TYPE_T MessageCode;
    PsuRotationStats_t PsuRotationStats;
};

/**
 * Parameters 
 * const uint8_t cBuildStringMaxLength = 32;
 * ‘BuildString’ – Text description of build, null terminated
 * ‘BuildNumber’ – Decimal representation of build number
 */

const uint8_t cBuildStringMaxLength = 32;

struct BuildInfo_t {
    MESSAGE_TYPE_T MessageCode;
    char           BuildString[cBuildStringMaxLength];
    uint16_t       BuildNumber;
};

struct I2CDiagnosticsData_t {
    uint32_t BytesRead;
    uint32_t BytesWritten;
    uint32_t ReadFailures;
    uint32_t WriteFailures;
};

struct CommsDiagnosticsData_t {
    uint32_t TimeOfLastHeartbeat;
    uint32_t TxQueueFullCount;
    uint32_t SocketWriteFailures;
};

struct ShpInfo_t {
    uint32_t TimeBetweenShps;
    uint32_t TimeOfLastShp;
    uint32_t ShpCount;
    uint32_t LastSpokeBeforeShp;
};

struct NiosDiagnosticsData_t {
    uint32_t CurrentTime_ms;
    I2CDiagnosticsData_t I2C;
    CommsDiagnosticsData_t Comms;
    ShpInfo_t ShpInfo;
};

struct DiagnosticsData_t {
    NiosDiagnosticsData_t NiosDiagnosticsData;
    uint32_t TotalTransmitTime_secs; // Total time in transmit mode 
}; // 52 bytes

struct DiagnosticsDataMsg_t {
    MESSAGE_TYPE_T MessageCode;
    DiagnosticsData_t DiagnosticsData;
};

/**
 * Parameters 
 * ‘RequestType’ cQuantumDiagReqMainProdData 
 * ‘ProdTestData’ see 10.4.1 cQuantumDiagReqMainProdData
 */

struct ProdTestData_t {
    MESSAGE_TYPE_T       MessageCode;
    QuantumDiagReq_t     RequestType; //‘RequestType’ cQuantumDiagReqMainProdData 
    ProductionTestData_t ProdTestData;
};

#endif // RAYMARINE_QUANTUM_DIAGNOSTICS_DATA_PACKET_H_