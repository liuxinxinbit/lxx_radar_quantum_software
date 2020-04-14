#ifndef RAYMARINE_QUANTUM_SET_GUARD_ZONE_ENABLE_H_
#define RAYMARINE_QUANTUM_SET_GUARD_ZONE_ENABLE_H_

#include "message_id.h"

/**
 * Parameters
 * ‘ZoneNumber’ 0 .. maxGuardZones (2)
 * ‘Enable’ true/false
 */

struct SetGuardZoneEnable_t {
    MESSAGE_TYPE_T m_MessageCode;
    uint8_t        ZoneNumber;
    bool           Enable;
};

#endif // RAYMARINE_QUANTUM_SET_GUARD_ZONE_ENABLE_H_