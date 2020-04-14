#ifndef RAYMARINE_QUANTUM_WIRED_ADAPTOR_H_
#define RAYMARINE_QUANTUM_WIRED_ADAPTOR_H_

#include "message_id.h"

struct WiredAdaptor_t {
    uint32_t MessageCode;
    uint32_t MajorVersion;
    uint32_t MinorVersion;
    uint32_t BuildNumber;
    uint32_t InputVoltage_mV;
    uint32_t TimeSinceQuantumLastHeard_ms;
};


#endif // RAYMARINE_QUANTUM_WIRED_ADAPTOR_H_