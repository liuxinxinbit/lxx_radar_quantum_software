#ifndef RAYMARINE_QUANTUM_REQ_SELF_TEST_RESULTS_H_
#define RAYMARINE_QUANTUM_REQ_SELF_TEST_RESULTS_H_

#include "message_id.h"

/**
 * Sent from the Host System to the Quantum Radar
 */

struct ReqSelfTestResults_t {
    MESSAGE_TYPE_T MessageCode;
};

#endif // RAYMARINE_QUANTUM_REQ_SELF_TEST_RESULTS_H_