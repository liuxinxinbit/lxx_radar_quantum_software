#ifndef RAYMARINE_QUANTUM_REQUEST_DIAGS_DATA_H_
#define RAYMARINE_QUANTUM_REQUEST_DIAGS_DATA_H_

#include "message_id.h"

// QuantumDiagReq_t
typedef uint32_t QuantumDiagReq_t;
const QuantumDiagReq_t cQuantumDiagReqInvalid           = 0;
const QuantumDiagReq_t cQuantumDiagReqMainProdData      = 1;
const QuantumDiagReq_t cQuantumDiagReqCrashLog          = 2;
const QuantumDiagReq_t cQuantumDiagReqPsuProdData       = 3;
const QuantumDiagReq_t cQuantumDiagReqPsuStatus         = 4;
const QuantumDiagReq_t cQuantumDiagReqPsuRotationStatus = 5;
const QuantumDiagReq_t cQuantumDiagReqPsuCrashLog       = 6;
const QuantumDiagReq_t cQuantumDiagReqBuildInfo         = 7;
const QuantumDiagReq_t cQuantumDiagReqDiagData          = 8;

struct RequestDiagnosticsData_t {
    MESSAGE_TYPE_T m_MessageCode;
    QuantumDiagReq_t m_RequestType;
};

#endif // RAYMARINE_QUANTUM_REQUEST_DIAGS_DATA_H_