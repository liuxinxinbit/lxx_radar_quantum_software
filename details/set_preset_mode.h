#ifndef RAYMARINE_QUANTUM_SET_PRESET_MODE_H_
#define RAYMARINE_QUANTUM_SET_PRESET_MODE_H_

#include "message_id.h"
#include "status.h"

struct SetPresetMode_t {
    MESSAGE_TYPE_T MessageCode;
    QUANTUM_CHANNEL_T Channel; 
    QUANTUM_PRESET_MODE_T Mode;
};

#endif // RAYMARINE_QUANTUM_SET_PRESET_MODE_H_