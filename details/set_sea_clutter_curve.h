#ifndef RAYMARINE_QUANTUM_SET_SEA_CLUTTER_CURVE_H_
#define RAYMARINE_QUANTUM_SET_SEA_CLUTTER_CURVE_H_

#include "message_id.h"
#include "status.h"

struct SetClutterCurve_t {
    MESSAGE_TYPE_T           m_MessageCode;
    QUANTUM_CHANNEL_T        m_Channel;
    QuantumSeaClutterCurve_t m_SeaClutterCurve;
};

#endif // RAYMARINE_QUANTUM_SET_SEA_CLUTTER_CURVE_H_