#ifndef RAYMARINE_QUANTUM_SET_BEARING_ALIGNMENT_H_
#define RAYMARINE_QUANTUM_SET_BEARING_ALIGNMENT_H_

#include "message_id.h"

/**
 * Parameters
 * ‘m_BearingAlignment’ degrees times 10 (-1795 to 1800)
 */

struct SetBearingAlignment_t {
    MESSAGE_TYPE_T m_MessageCode;
    int16_t        m_BearingAlignment;
};

#endif // RAYMARINE_QUANTUM_SET_BEARING_ALIGNMENT_H_