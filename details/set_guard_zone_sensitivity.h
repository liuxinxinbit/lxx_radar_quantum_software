#ifndef RAYMARINE_QUANTUM_SET_GUARD_ZONE_SENSITIVITY_H_
#define RAYMARINE_QUANTUM_SET_GUARD_ZONE_SENSITIVITY_H_

#include "message_id.h"

/**
 * The Guard Zone Sensitivity applies to all Guard Zones.
 * The Sensitivity controls the number of samples required in the Guard Zone to 
 * trigger the alarm. Normally between 1 and 51 samples within the Guard Zone 
 * are required
 * 
 * Parameters
 * ‘Sensitivity’ 0-100% 
 *      0% is least sensitive.
 *      100% most sensitive (alarm for any target of any strength)
 */

struct SetGuardZoneSensitivity_t {
    MESSAGE_TYPE_T m_MessageCode;
    uint8_t Sensitivity;
};

#endif // RAYMARINE_QUANTUM_SET_GUARD_ZONE_SENSITIVITY_H_