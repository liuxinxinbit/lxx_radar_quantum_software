#ifndef RAYMARINE_QUANTUM_SET_RADAR_MODE_H_
#define RAYMARINE_QUANTUM_SET_RADAR_MODE_H_

#include "message_id.h"
#include "status.h"

struct SetRadarMode_t {
    MESSAGE_TYPE_T m_MessageCode; //!< Message Id
    QUANTUM_MODE_T m_RadarMode; //!< Requested Mode for Radar
};

#endif // RAYMARINE_QUANTUM_SET_RADAR_MODE_H_