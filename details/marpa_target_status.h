#ifndef RAYMARINE_QUANTUM_MARPA_TARGET_STATUS_H_
#define RAYMARINE_QUANTUM_MARPA_TARGET_STATUS_H_

#include "message_id.h"

/**
 * 'm_ID'              Target Id (0-9)
 * 'm_TargetType'      Acquiring, Safe, Dangerous or Lost
 * 'm_AutoAcquisition' True if target has been automatically acquired, else false 
 *                     (auto acquisition is not currently supported)
 * 'm_Valid'           True if target is currently in use, else false
 * 'm_Distance'        Range of target in metres x 1000
 * 'm_Bearing'         Bearing of target relative to SHM, degrees x 10
 * 'm_TrueBearing'     True bearing of target relative to TRUE North, degrees x 10
 * 'm_Speed'           Speed of Target relative to own ship, metres per sec x 1000
 * 'm_Course'          Course of Target relative to own ship, degree x 10
 * 'm_TargetSpeed'     Target True speed, metres per sec x 1000
 * 'm_TargetCourse'    Target True course, degree x 10
 * 'm_ClosestPointOfApproach' Closest point of approach, metres x 1000
 * 'm_TimeToClosestApproach'; Time to Closest Point of Approach, seconds
 * 'm_HeadingAtUpdate' Own ship heading at time target data last updated, degree x 10
 * 'm_TargetGoingTowardsClosestPoint' True if CPA is still to occur, else false
 * 'm_TargetDataValid' True if Target True Speed/Course are valid, else false
 *                      (This parameter will be false if SOG/COG are not available)
 * 'm_DangerAlarmActive' True if Target is in Dangerous state, else false
 */

typedef uint32_t TARGET_TYPE_T;

struct TARGET_DATA_T {
    uint32_t                                           m_ID;
    TARGET_TYPE_T                                      m_TargetType;
    bool                                               m_AutoAcquisition;
    bool                                               m_Valid;
    INSTRUMENTS::LONG_DISTANCE_0_001_METRES_T          m_Distance;
    INSTRUMENTS::ANGLE_32BIT_0_1_DEG_T                 m_Bearing; 
    INSTRUMENTS::ANGLE_32BIT_0_1_DEG_T                 m_TrueBearing;
    INSTRUMENTS::SPEED_32BIT_0_001_METRES_PER_SECOND_T m_Speed;
    INSTRUMENTS::ANGLE_32BIT_0_1_DEG_T                 m_Course;
    INSTRUMENTS::SPEED_32BIT_0_001_METRES_PER_SECOND_T m_TargetSpeed; 
    INSTRUMENTS::ANGLE_32BIT_0_1_DEG_T                 m_TargetCourse; 
    INSTRUMENTS::LONG_DISTANCE_0_001_METRES_T          m_ClosestPointOfApproach; 
    uint32_t                                           m_TimeToClosestApproach; 
    INSTRUMENTS::ANGLE_32BIT_0_1_DEG_T                 m_HeadingAtUpdate; 
    bool                                               m_TargetGoingTowardsClosestPoint;
    bool                                               m_TargetDataValid;
    bool                                               m_DangerAlarmActive;
};

struct MarpaTargetStatus_t {
    MESSAGE_TYPE_T m_MessageCode;
    TARGET_DATA_T  m_TargetData;
};

#endif // RAYMARINE_QUANTUM_MARPA_TARGET_STATUS_H_