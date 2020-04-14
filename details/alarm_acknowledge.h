#ifndef RAYMARINE_QUANTUM_ALARM_ACKNOWLEDGE_H_
#define RAYMARINE_QUANTUM_ALARM_ACKNOWLEDGE_H_

#include "message_id.h"
#include "alarm_list.h"
/**
 * Parameters
 * ‘Id’ Id of alarm from the Alarm List Message. This parameter can be set to cAlarmIdAll.
 * ‘Type’ Alarm Type, can be set to cAlarmTypeAll 
 * If the Id field is not set to cAlarmIdAll, the Id field specifies a unique alarm and the type field can be ignored.
 * If the Id field is set to cAlarmIdAll, all alarms of the type specified in the Type field are acknowledged.
 * If the Id field is set to cAlarmIdAll and the Type field is set to cAlarmTypeAll, then all alarms are acknowledged.
 */

struct AlarmAcknowledge_t {
    MESSAGE_TYPE_T MessageCode;
    AlarmId_t      Id;
    AlarmType_t    Type;
};

#endif // RAYMARINE_QUANTUM_ALARM_ACKNOWLEDGE_H_