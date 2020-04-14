#ifndef RAYMARINE_QUANTUM_SET_RANGE_H_
#define RAYMARINE_QUANTUM_SET_RANGE_H_

#include "message_id.h"
#include "status.h"

const uint8_t Range_1_32 = 0;
const uint8_t Range_1_16 = 1;
const uint8_t Range_1_8  = 2;
const uint8_t Range_1_4  = 3;
const uint8_t Range_3_8  = 4;
const uint8_t Range_1_2  = 5;
const uint8_t Range_3_4  = 6;
const uint8_t Range_1    = 7;
const uint8_t Range_3_2  = 8;
const uint8_t Range_2    = 9;
const uint8_t Range_3    = 10;
const uint8_t Range_4    = 11;
const uint8_t Range_6    = 12;
const uint8_t Range_8    = 13;
const uint8_t Range_12   = 14;
const uint8_t Range_16   = 15;
const uint8_t Range_24   = 16;

struct SetRange_t {
    MESSAGE_TYPE_T    m_MessageCode; 
    QUANTUM_CHANNEL_T m_Channel; 
    uint8_t           m_RangeIndex; 
};

#endif // RAYMARINE_QUANTUM_SET_RANGE_H_