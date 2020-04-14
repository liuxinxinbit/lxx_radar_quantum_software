#ifndef RAYMARINE_QUANTUM_SET_SEA_MODE_H_
#define RAYMARINE_QUANTUM_SET_SEA_MODE_H_

#include "message_id.h"
#include "status.h"

struct SetSeaMode_t {
    MESSAGE_TYPE_T     m_MessageCode;
    QUANTUM_CHANNEL_T  m_Channel;
    QUANTUM_SEA_MODE_T m_Mode;
};

#endif // RAYMARINE_QUANTUM_SET_SEA_MODE_H_