#ifndef RAYMARINE_QUANTUM_ALARM_LIST_H_
#define RAYMARINE_QUANTUM_ALARM_LIST_H_

#include "message_id.h"

// 12.1.1 AlarmId_t
typedef uint32_t AlarmId_t;
const AlarmId_t cAlarmIdAll = 0xFFFFFFFF; // ack all alarms of specified type
const AlarmId_t cAlarmMax   = 50;

// 12.1.2 AlarmType_t
typedef uint32_t AlarmType_t;
// ack all alarms of all types
const AlarmType_t cAlarmTypeAll                     = 0xFFFFFFFF;
const AlarmType_t cAlarmTypeGuardZoneTargetEntering = 0;
const AlarmType_t cAlarmTypeMarpaDangerousTarget    = 1;
const AlarmType_t cAlarmTypeMarpaLostTarget         = 2;
const AlarmType_t cAlarmTypeFirst                   = cAlarmTypeGuardZoneTargetEntering;
const AlarmType_t cAlarmTypeLast                    = cAlarmTypeMarpaLostTarget;

// 12.1.3 AlarmStatus_t
typedef uint32_t AlarmStatus_t;
const AlarmStatus_t cAlarmCleared            = 0;
const AlarmStatus_t cAlarmStatusRaised       = 1;
const AlarmStatus_t cAlarmStatusAcknowledged = 2;
const AlarmStatus_t cAlarmStatusFirst        = cAlarmCleared;
const AlarmStatus_t cAlarmStatusLast         = cAlarmStatusAcknowledged;

// 12.1.4 AlarmEntry_t
struct AlarmEntry_t {
    AlarmId_t Id;
    AlarmType_t Type;
    AlarmStatus_t Status;
    uint32_t Value;
};

/**
 * Parameters
 * ‘Count’ - number of Alarms in message (1 .. cAlarmMax). 
 * This will be the number of subsequent AlarmEntry_t structures.
 * ‘Entry’
 * ‘Id’ Incrementing Sequence number (1 .. 0xFFFFFFFE)
 * ‘Type’ see AlarmType_t
 * ‘Status’ see AlarmStatus_t (should always be cAlarmStatusRaised) 
 * ‘Value’ Guard Zone Id, Marpa Target Id
 */

struct AlarmList_t {
    MESSAGE_TYPE_T MessageCode;
    uint32_t Count;
    AlarmEntry_t Entry[cAlarmMax];
};

#endif // RAYMARINE_QUANTUM_ALARM_LIST_H_
