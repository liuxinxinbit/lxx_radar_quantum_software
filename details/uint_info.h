#ifndef RAYMARINE_QUANTUM_UNIT_INFO_H_
#define RAYMARINE_QUANTUM_UNIT_INFO_H_

#include "message_id.h"

const uint8_t UNIT_INFO_NAME_SIZE   = 32;

typedef uint32_t UNIT_TYPE_T;

const UNIT_TYPE_T LNET_UNIT_TYPE_FLIR_QUANTUM_RADOME = 95;
const UNIT_TYPE_T LNET_UNIT_TYPE_QUANTUM_RADOME_W3 = 77;

struct UnitInfo_t {
    MESSAGE_TYPE_T MessageID;
    UNIT_TYPE_T    UnitType;
    uint32_t       NodeID;                    // Encoded Serial Number
    uint32_t       SoftwareVersion;
    uint32_t       IPAddress;
    char           Name[UNIT_INFO_NAME_SIZE]; // 32 bytes maximum
    uint16_t       DataLength;                // Data field is max 80 bytes
    uint16_t       MFDOptions;
};



#endif // RAYMARINE_QUANTUM_UNIT_INFO_H_
