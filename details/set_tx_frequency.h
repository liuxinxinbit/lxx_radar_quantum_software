#ifndef RAYMARINE_QUANTUM_SET_TX_FREQUENCY_H_
#define RAYMARINE_QUANTUM_SET_TX_FREQUENCY_H_

#include "message_id.h"
#include "status.h"

struct SetTxFrequency_t {
    MESSAGE_TYPE_T    MessageCode;
    QUANTUM_TX_FREQ_T Mode;
};

#endif // RAYMARINE_QUANTUM_SET_TX_FREQUENCY_H_