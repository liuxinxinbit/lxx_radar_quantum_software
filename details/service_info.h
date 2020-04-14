#ifndef RAYMARINE_QUANTUM_SERVICE_INFO_H_
#define RAYMARINE_QUANTUM_SERVICE_INFO_H_

#include "message_id.h"

typedef uint32_t SERVICE_ID_T;
const SERVICE_ID_T SERVICE_ID_QUANTUM_RADAR    = 0x2B;
const SERVICE_ID_T SERVICE_ID_QUANTUM_RADAR_W3 = 0x29;
const uint8_t MAX_SYS_MESSAGE_DATA_SIZE = 50;

struct SERVICE_INFO_HEADER_T {
    uint32_t nNodeID;
    SERVICE_ID_T nServiceID;
    uint16_t OriginalTransportType;
    uint16_t nTimeout;
    uint16_t nInstance;
    uint16_t nDataLength;
};

struct SERVICE_INFO_DATA_T {
    uint32_t nDataIPAddress;
    uint16_t nDataPort;
    uint32_t nControlIPAddress;
    uint16_t nControlPort;
};

struct ServiceInfo_t {
    MESSAGE_TYPE_T        MessageID;
    SERVICE_INFO_HEADER_T Header;
    SERVICE_INFO_DATA_T   Data;
};

#endif // RAYMARINE_QUANTUM_SERVICE_INFO_H_