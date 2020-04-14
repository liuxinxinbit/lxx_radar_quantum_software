#ifndef RAYMARINE_QUANTUM_SET_RAIN_VALUE_H_
#define RAYMARINE_QUANTUM_SET_RAIN_VALUE_H_

#include "message_id.h"
#include "status.h"

struct SetRainValue_t {
    MESSAGE_TYPE_T m_MessageCode;
    QUANTUM_CHANNEL_T m_Channel;
    uint8_t m_Value; // 0-100%
};

#endif // RAYMARINE_QUANTUM_SET_RAIN_VALUE_H_