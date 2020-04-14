#ifndef RAYMARINE_QUANTUM_SET_TARGET_EXPANSION_H_
#define RAYMARINE_QUANTUM_SET_TARGET_EXPANSION_H_

#include "message_id.h"
#include "status.h"

struct SetTargetExpansion {
    MESSAGE_TYPE_T                  m_MessageCode;
    QUANTUM_CHANNEL_T               m_Channel;
    QUANTUM_TARGET_EXPANSION_MODE_T m_Mode;
};

#endif // RAYMARINE_QUANTUM_SET_TARGET_EXPANSION_H_