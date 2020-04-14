#ifndef RAYMARINE_QUANTUM_SET_INTERFERENCE_REJECTION_H_
#define RAYMARINE_QUANTUM_SET_INTERFERENCE_REJECTION_H_

#include "message_id.h"
#include "status.h"

struct SetInterferenceRejection_t {
    MESSAGE_TYPE_T                        m_MessageCode;
    QUANTUM_INTERFERENCE_REJECTION_MODE_T m_Mode;
};

#endif // RAYMARINE_QUANTUM_SET_INTERFERENCE_REJECTION_H_