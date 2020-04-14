#ifndef RAYMARINE_QUANTUM_MARPA_SETUP_INFO_H_
#define RAYMARINE_QUANTUM_MARPA_SETUP_INFO_H_

#include "message_id.h"

/**
 * Parameters
 * The first 4 parameters specify the Marpa setup as enumerated types. The second 4 parameters reflect the first 
 * four parameters in integer format, for historic reasons. Only ‘m_CPASafeZoneMetres’ and ‘m_TCPATimeSecs’ 
 * are used by the scanner, but the other 6 parameters need to be set to valid values.
 * All 8 parameters MUST be set to valid values
 * ‘m_TargetPP’- Unused by Scanner, Set to 0.
 * ‘m_TargetPPSecs’- Unused by scanner set to 30.
 * ‘m_TargetHistory’- Unused by Scanner, Set to 0.
 * ‘m_TargetHistorySecs’- Unused by scanner set to 0.
 * ‘m_CPASafeZone’ – Unused by scanner, set to 0.
 * ‘m_TCPATime’ – Unused by scanner, set to 0.
 *  
 * ‘m_CPASafeZoneMetres’ Specifies the safe distance. The minimum value for this parmeter is 185m(0.1nm) 
 * and the maximum is 3706m (2.0nm)
 */
typedef uint8_t TARGET_PP_T;
typedef uint8_t CPA_SAFE_ZONE_T;
typedef uint8_t TCPA_TIME_T;
typedef uint8_t TARGET_HISTORY_T;

struct SETUP_DATA_T {
    TARGET_PP_T      m_TargetPP;
    CPA_SAFE_ZONE_T  m_CPASafeZone;
    TCPA_TIME_T      m_TCPATime;
    TARGET_HISTORY_T m_TargetHistory;
    uint32_t         m_TargetPPSecs;
    uint32_t         m_CPASafeZoneMetres;
    uint32_t         m_TCPATimeSecs;
    uint32_t         m_TargetHistorySecs;
};

struct MarpaSetupInfo_t {
    MESSAGE_TYPE_T      m_MessageCode;
    SETUP_DATA_T m_SetupData;
};

#endif // RAYMARINE_QUANTUM_MARPA_SETUP_INFO_H_