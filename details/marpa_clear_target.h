#ifndef RAYMARINE_QUANTUM_MARPA_CLEAR_TARGET_H_
#define RAYMARINE_QUANTUM_MARPA_CLEAR_TARGET_H_

#include "message_id.h"

/**
 * Parameters
 * ‘m_ID’ 0-9 for 10 Marpa targets, 0xFF (0xFFFFFFFF) clears all Marpa targets
 */

struct MarpaClearTarget_t {
    MESSAGE_TYPE_T m_MessageCode;
    uint32_t m_ID;
};

#endif // RAYMARINE_QUANTUM_MARPA_CLEAR_TARGET_H_