#ifndef RAYMARINE_QUANTUM_SET_TIMED_TX_PARAMETERS_H_
#define RAYMARINE_QUANTUM_SET_TIMED_TX_PARAMETERS_H_

#include "message_id.h"

/**
 * Parameter Values
 * - ‘StandbyTime_Mins’ number of minutes to remain in standby mode
 * - ‘TransmitCount_Scans’ number of scans in transmit mode, before returning to 
 *    standby mode
 * 
 * In Standby Mode the ‘StandbyTimeRemainingMins’ and ‘StandbyTimeRemainingSecs’ 
 * fields with the QUANTUM_STATUS_T will count down the time remaining until 
 * transmit mode is entered.
 */

struct SetTimedTxParams_t {
    MESSAGE_TYPE_T MessageCode;
    uint8_t StandbyTime_Mins;
    uint8_t TransmitCount_Scans;
};

#endif // RAYMARINE_QUANTUM_SET_TIMED_TX_PARAMETERS_H_