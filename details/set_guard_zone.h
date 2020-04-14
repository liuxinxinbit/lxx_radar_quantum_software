#ifndef RAYMARINE_QUANTUM_SET_GUARD_ZONE_H_
#define RAYMARINE_QUANTUM_SET_GUARD_ZONE_H_

#include "message_id.h"
#include "status.h"

/**
 * Parameters
 * ‘m_StartDistance’ 0-96000 inner edge in nautical miles * 1000 (i.e 0nm to 96nm)
 * ‘m_EndDistance’ 0-96000 outer edge in nautical miles * 1000 (i.e 0nm to 96nm)
 * ‘m_StartAngle’ 0-3599 start angle in degrees * 10 (i.e. 0 to 359.9)
 * ‘m_EndAngle’ 0-3599 end angle in degrees * 10 (i.e. 0 to 359.9)
 * ‘m_StartDistance’ should always be less than ‘m_EndDistance’
 * If m_StartDistance is zero, a sector Guard Zone is created
 * ‘m_StartAngle’ may be less than ‘m_EndAngle’
 * If ‘m_StartAngle’ and ‘m_EndAngle’ are both zero, the Guard Zone will be a full circle
 * ‘ZoneNumber’ 0 .. maxGuardZones (2)
 */

struct SetGuardZone_t {
    MESSAGE_TYPE_T                               m_MessageCode;
    INSTRUMENTS::DISTANCE_0_001_NAUTICAL_MILES_T m_StartDistance;
    INSTRUMENTS::DISTANCE_0_001_NAUTICAL_MILES_T m_EndDistance;
    INSTRUMENTS::ANGLE_0_1_DEG_T                 m_StartAngle;
    INSTRUMENTS::ANGLE_0_1_DEG_T                 m_EndAngle;
    uint8_t                                      m_ZoneNumber;
};

#endif // RAYMARINE_QUANTUM_SET_GUARD_ZONE_H_