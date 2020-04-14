#ifndef RAYMARINE_QUANTUM_STAUTS_H_
#define RAYMARINE_QUANTUM_STAUTS_H_

#include "message_id.h"
#include <iostream>
#include <string>

// QUANTUM_MODE_T
typedef uint8_t QUANTUM_MODE_T;
const QUANTUM_MODE_T QUANTUM_MODE_STANDBY         = 0;
const QUANTUM_MODE_T QUANTUM_MODE_TRANSMITTING    = 1; //!< Transmitting Mode
const QUANTUM_MODE_T QUANTUM_MODE_POWER_DOWN      = 3; //!< Powering Down Mode
const QUANTUM_MODE_T QUANTUM_MODE_TIMED_TX        = 4; //!< Timed Transmit Mode
const QUANTUM_MODE_T QUANTUM_MODE_SLEEP           = 5; //!< Rotation has stalled
const QUANTUM_MODE_T QUANTUM_MODE_STALLED         = 7; //!< Self test failed
const QUANTUM_MODE_T QUANTUM_MODE_SELFTEST_FAILED = 10; // QUANTUM_TX_FREQ_T

typedef uint8_t QUANTUM_TX_FREQ_T;
const QUANTUM_TX_FREQ_T QUANTUM_TX_FREQ_NOMINAL = 0;
const QUANTUM_TX_FREQ_T QUANTUM_TX_FREQ_LOW = 1;
const QUANTUM_TX_FREQ_T QUANTUM_TX_FREQ_HIGH = 2;

// QUANTUM_GAIN_MODE_T
typedef uint8_t QUANTUM_GAIN_MODE_T;
const QUANTUM_GAIN_MODE_T QUANTUM_GAIN_MODE_MANUAL = 0;
const QUANTUM_GAIN_MODE_T QUANTUM_GAIN_MODE_AUTO   = 1;

// QUANTUM_COLOUR_GAIN_MODE_T
typedef uint8_t QUANTUM_COLOUR_GAIN_MODE_T;
const QUANTUM_COLOUR_GAIN_MODE_T QUANTUM_COLOUR_GAIN_MODE_MANUAL = 0;
const QUANTUM_COLOUR_GAIN_MODE_T QUANTUM_COLOUR_GAIN_MODE_AUTO   = 1;

// QUANTUM_SEA_MODE_T
typedef uint8_t QUANTUM_SEA_MODE_T;
const QUANTUM_SEA_MODE_T QUANTUM_SEA_MODE_MANUAL = 0;
const QUANTUM_SEA_MODE_T QUANTUM_SEA_MODE_AUTO  = 1;

// QuantumSeaClutterCurve_t
typedef uint8_t QuantumSeaClutterCurve_t;
const QuantumSeaClutterCurve_t cQuantumSeaCurve_R4      = 0;
const QuantumSeaClutterCurve_t cQuantumSeaCurve_R5_5    = 1;
const QuantumSeaClutterCurve_t cQuantumSeaCurve_Default = cQuantumSeaCurve_R5_5;
const QuantumSeaClutterCurve_t cQuantumSeaCurve_Min     = cQuantumSeaCurve_R4;
const QuantumSeaClutterCurve_t cQuantumSeaCurve_Max     = cQuantumSeaCurve_R5_5;

// QUANTUM_RAIN_MODE_T
typedef uint8_t QUANTUM_RAIN_MODE_T;
const QUANTUM_RAIN_MODE_T QUANTUM_RAIN_MODE_OFF    = 0;
const QUANTUM_RAIN_MODE_T QUANTUM_RAIN_MODE_MANUAL = 1;

// QUANTUM_TARGET_EXPANSION_MODE_T
typedef uint8_t QUANTUM_TARGET_EXPANSION_MODE_T;
const QUANTUM_TARGET_EXPANSION_MODE_T QUANTUM_TARGET_EXPANSION_MODE_OFF = 0;
const QUANTUM_TARGET_EXPANSION_MODE_T QUANTUM_TARGET_EXPANSION_MODE_ON  = 1;

// QUANTUM_INTERFERENCE_REJECTION_MODE_T
typedef uint8_t QUANTUM_INTERFERENCE_REJECTION_MODE_T;
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_OFF = 0;
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_ON  = 1;
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_1 = 1;
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_2 = 2;
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_3 = 3;
// QUANTUM_INTERFERENCE_REMarpaTargetStatus_t
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_4 = 4;
const QUANTUM_INTERFERENCE_REJECTION_MODE_T QUANTUM_INTERFERENCE_REJECTION_MODE_5 = 5;

// QUANTUM_SCANNER_SPEED_T
typedef uint8_t QUANTUM_SCANNER_SPEED_T;
const QUANTUM_SCANNER_SPEED_T QUANTUM_SCANNER_SPEED_NORMAL = 0;
const QUANTUM_SCANNER_SPEED_T QUANTUM_SCANNER_SPEED_AUTO = 1;

struct QUANTUM_ZONE_T {
    INSTRUMENTS::DISTANCE_0_001_NAUTICAL_MILES_T m_StartDistance;
    INSTRUMENTS::DISTANCE_0_001_NAUTICAL_MILES_T m_EndDistance;
    INSTRUMENTS::ANGLE_0_1_DEG_T                 m_StartAngle;
    INSTRUMENTS::ANGLE_0_1_DEG_T                 m_EndAngle;
    bool                                         m_Enable;
    uint8_t                                      m_Spare[3];
};

struct QUANTUM_BLANK_SECTOR_T {
    INSTRUMENTS::ANGLE_0_1_DEG_T m_StartAngle;
    INSTRUMENTS::ANGLE_0_1_DEG_T m_EndAngle;
    bool                         m_Enable;
    uint8_t                      m_Spare[3];
};

// QUANTUM_PRESET_DATA_T
struct QUANTUM_PRESET_DATA_T {
    QUANTUM_GAIN_MODE_T        GainMode;
    uint8_t                    GainValue;
    QUANTUM_COLOUR_GAIN_MODE_T ColourGainMode;
    uint8_t                    ColourGainValue;
    QUANTUM_SEA_MODE_T         SeaClutterMode;
    uint8_t                    SeaClutterValue;
    QUANTUM_RAIN_MODE_T        RainClutterMode;
    uint8_t                    RainClutterValue;
};

// QUANTUM_PRESET_MODE_T
typedef uint8_t QUANTUM_PRESET_MODE_T;
const QUANTUM_PRESET_MODE_T cPresetModeHarbour   = 0;
const QUANTUM_PRESET_MODE_T cPresetModeCoastal   = 1;
const QUANTUM_PRESET_MODE_T cPresetModeOffshore  = 2;
const QUANTUM_PRESET_MODE_T cPresetModeWeather   = 3;
const QUANTUM_PRESET_MODE_T cPresetModeFirst     = cPresetModeHarbour;
const QUANTUM_PRESET_MODE_T cPresetModeLast      = cPresetModeWeather;
// QuantumMainBangSuppression_t
typedef uint8_t QuantumMainBangSuppression_t;
const QuantumMainBangSuppression_t cQuantumMainBangSuppressionOff = 0;
const QuantumMainBangSuppression_t cQuantumMainBangSuppressionOn  = 1;

// QUANTUM_RANGE_STATUS_T
const uint8_t QUANTUM_PRESET_MODES = 4;

struct QUANTUM_RANGE_STATUS_T {
    uint8_t                         RangeIndex;
    QUANTUM_PRESET_MODE_T           PresetMode;
    QUANTUM_PRESET_DATA_T           PresetData[QUANTUM_PRESET_MODES];
    QUANTUM_TARGET_EXPANSION_MODE_T TargetExpansionMode;
    QuantumSeaClutterCurve_t        SeaCurve;
    uint16_t                        ZeroRange;
    uint8_t                         STCKnee;
    QuantumMainBangSuppression_t    MainBangSuppression;
};

// QUANTUM_STATUS_T
const uint8_t QUANTUM_CHANNELS = 2;
const uint8_t QUANTUM_GUARD_ZONES = 2;
const uint8_t QUANTUM_BLANK_SECTORS = 2;
const uint8_t QUANTUM_MAX_RANGES = 20;
const uint8_t QUANTUM_AUTO_ACQUIRE_ZONES = 2;

struct QUANTUM_STATUS_T {
    QUANTUM_MODE_T                               RadarMode;
    uint8_t                                      Spare;
    uint8_t                                      StandbyTimeRemainingMins;
    uint8_t                                      StandbyTimeRemainingSecs;
    uint8_t                                      StandbyTime_Mins;
    uint8_t                                      TransmitCount_Scans;
    QUANTUM_TX_FREQ_T                            TxFreq;
    uint8_t                                      Unused;
    bool                                         DualRangeMode;
    QUANTUM_SCANNER_SPEED_T                      ScannerSpeed;
    INSTRUMENTS::SIGNED_ANGLE_0_1_DEG_T          BearingAlignment;
    uint8_t                                      GuardZoneSensitivity;
    QUANTUM_INTERFERENCE_REJECTION_MODE_T        InterferenceRejectionMode;
    bool                                         StcEnable;
    bool                                         FtcEnable;
    QUANTUM_RANGE_STATUS_T                       RangeInfo[QUANTUM_CHANNELS];
    QUANTUM_ZONE_T                               GuardZone[QUANTUM_GUARD_ZONES];
    QUANTUM_BLANK_SECTOR_T                       BlankSector[QUANTUM_BLANK_SECTORS];
    INSTRUMENTS::DISTANCE_0_001_NAUTICAL_MILES_T CustomRanges[QUANTUM_MAX_RANGES];
    QUANTUM_ZONE_T                               AutoAcquireZone[QUANTUM_AUTO_ACQUIRE_ZONES];
};

struct Status_t {
    MESSAGE_TYPE_T m_MessageCode;
    QUANTUM_STATUS_T m_Status;
};

#endif // RAYMARINE_QUANTUM_STAUTS_H_
