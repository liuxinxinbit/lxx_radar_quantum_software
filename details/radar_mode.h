#ifndef RAYMARINE_QUANTUM_RADAR_MODE_H_
#define RAYMARINE_QUANTUM_RADAR_MODE_H_

#include "message_id.h"
#include "status.h"

struct RadarMode_t {
    MESSAGE_TYPE_T MessageCode;
    QUANTUM_MODE_T RadarMode;
};

#endif // RAYMARINE_QUANTUM_RADAR_MODE_H_