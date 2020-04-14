#ifndef RAYMARINE_QUANTUM_HEARTBEAT_H_
#define RAYMARINE_QUANTUM_HEARTBEAT_H_

#include "message_id.h"
#include <stdio.h>

struct Heartbeat_t {
    MESSAGE_TYPE_T MessageCode;
    char HeartbeatText[8];
};



#endif // RAYMARINE_QUANTUM_HEARTBEAT_H_
