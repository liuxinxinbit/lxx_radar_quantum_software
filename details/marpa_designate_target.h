#ifndef RAYMARINE_QUANTUM_MARPA_DESIGNATE_TARGET_H_
#define RAYMARINE_QUANTUM_MARPA_DESIGNATE_TARGET_H_

#include "message_id.h"

/**
 * Parameters
 * ‘m_Distance’ distance of target to be acquired in metres times 1000.
 * ‘m_bearing’ TRUE bearing of target to be acquired in degrees times 10.
 */

struct MarpaDesignateTarget_t {
    MESSAGE_TYPE_T                            m_MessageCode;
    INSTRUMENTS::LONG_DISTANCE_0_001_METRES_T m_Distance;
    INSTRUMENTS::ANGLE_32BIT_0_1_DEG_T        m_Bearing;
};

#endif // RAYMARINE_QUANTUM_MARPA_DESIGNATE_TARGET_H_