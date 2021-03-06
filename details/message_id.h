#ifndef RAYMARINE_QUANTUM_MESSAGE_ID_H_
#define RAYMARINE_QUANTUM_MESSAGE_ID_H_

#include <cstdint>

typedef uint32_t MESSAGE_TYPE_T;
typedef uint8_t  QUANTUM_CHANNEL_T;

namespace msg_id {

// Unit information message
const MESSAGE_TYPE_T UNIT_INFO_MESSAGE_ID = 0x00000001;
const MESSAGE_TYPE_T NOTHING = 0x00000002;

// Service information message
const uint32_t SERVICE_INFO_MESSAGE_ID = 0x00000000;

// Quantum periodic messages
const MESSAGE_TYPE_T HEARTBEAT  = 0x00280000;
const MESSAGE_TYPE_T ATTRIBUTES = 0x00280001;
const MESSAGE_TYPE_T STATUS     = 0x00280002;
const MESSAGE_TYPE_T RADAR_MODE = 0x00280005;
const MESSAGE_TYPE_T FEATURES   = 0x00280007;
const MESSAGE_TYPE_T NAV_DATA   = 0x00280020;

// Quantum Spoke Data messages
const MESSAGE_TYPE_T SPOKE_DATA = 0x00280003;
// Quantum channel independent control messages
const MESSAGE_TYPE_T SET_RADAR_MODE        = 0x00280010;
const MESSAGE_TYPE_T SET_TIMED_TX_PARAMS   = 0x00280011;
const MESSAGE_TYPE_T SET_BEARING_ALIGNMENT = 0x00280401;
const MESSAGE_TYPE_T SCANNER_COMMAND       = 0x00280404;
const MESSAGE_TYPE_T SET_TX_FREQ           = 0x00280409;

// Quantum channel dependent control messages
const MESSAGE_TYPE_T SET_RANGE                  = 0x00280101;
const MESSAGE_TYPE_T SET_GAIN_MODE              = 0x00280301;
const MESSAGE_TYPE_T SET_GAIN_VALUE             = 0x00280302;
const MESSAGE_TYPE_T SET_COLOUR_GAIN_MODE       = 0x00280303;
const MESSAGE_TYPE_T SET_COLOUR_GAIN_VALUE      = 0x00280304;
const MESSAGE_TYPE_T SET_SEA_MODE               = 0x00280305;
const MESSAGE_TYPE_T SET_SEA_VALUE              = 0x00280306;
const MESSAGE_TYPE_T SET_RAIN_MODE              = 0x0028030B;
const MESSAGE_TYPE_T SET_RAIN_VALUE             = 0x0028030C;
const MESSAGE_TYPE_T SET_TARGET_EXPANSION       = 0x0028030F;
const MESSAGE_TYPE_T SET_INTERFERENCE_REJECTION = 0x00280311;
const MESSAGE_TYPE_T SET_SEA_CLUTTER_CURVE      = 0x00280312;
const MESSAGE_TYPE_T SET_PRESET_MODE            = 0x00280314;
const MESSAGE_TYPE_T SET_PRI_JITTER             = 0x00280315;
const MESSAGE_TYPE_T SET_PROD_TEST_BITS         = 0x00280316;
// Guard Zone Commands
const MESSAGE_TYPE_T SET_GUARD_ZONE                   = 0x00280601;
const MESSAGE_TYPE_T SET_GUARD_ZONE_ALARM_SENSITIVITY = 0x00280602;
const MESSAGE_TYPE_T GUARD_ZONE_ENABLE                = 0x00280603;

// Test, debug and diagnostics messages
const MESSAGE_TYPE_T REQUEST_DIAGS_DATA     = 0x00280807;
const MESSAGE_TYPE_T CRASH_LOG_DATA         = 0x00280808;
const MESSAGE_TYPE_T REQ_SELF_TEST_RESULTS  = 0x00280809;
const MESSAGE_TYPE_T SELF_TEST_RESULTS      = 0x0028080A;
const MESSAGE_TYPE_T PROD_TEST_DATA         = 0x0028080B;
const MESSAGE_TYPE_T PSU_STATUS_PACKET      = 0x0028080C;
const MESSAGE_TYPE_T PSU_ROTATION_STATS     = 0x0028080D;
const MESSAGE_TYPE_T BUILD_INFO_DATA_PACKET = 0x0028080E;
const MESSAGE_TYPE_T DIAGNOSTICS_DATA       = 0x0028080F;
const MESSAGE_TYPE_T ALARM_LIST             = 0x00280B01;
const MESSAGE_TYPE_T ALARM_ACKNOWLEDGE      = 0x00280B02;

// marpa
const MESSAGE_TYPE_T TARGET_STATUS = 0x00288942L;
//Quantum Wired adapter periodic messages
const MESSAGE_TYPE_T WIRED_ADAPTOR_STATUS   = 0x00290000;

// This parameter used throughout the protocol to specify the channel.
const QUANTUM_CHANNEL_T QUANTUM_CHANNEL_DEFAULT = 0;

} // namespace msg_id

namespace INSTRUMENTS {

typedef uint16_t ANGLE_0_1_DEG_T;
typedef uint32_t ANGLE_32BIT_0_1_DEG_T;
typedef int16_t  SIGNED_ANGLE_0_1_DEG_T;
typedef int32_t  SIGNED_ANGLE_32BIT_0_1_DEG_T;
typedef uint16_t ANGLE_0_0001_RAD_T;
typedef uint32_t DISTANCE_0_001_NAUTICAL_MILES_T;
typedef uint16_t SPEED_0_01_METRES_PER_SECOND_T;
typedef uint32_t SPEED_32BIT_0_01_METRES_PER_SECOND_T;
typedef uint32_t LONG_DISTANCE_0_001_METRES_T;
typedef uint32_t DISTANCE_METRES_T;
typedef uint32_t SPEED_32BIT_0_001_METRES_PER_SECOND_T;
typedef int32_t  LONG_LAT_0_0000001_DEG_T;
typedef int32_t  LONG_LAT_0_0001_MIN_T;

struct POSITION_STRUCT_T {
    LONG_LAT_0_0000001_DEG_T Latitude;
    LONG_LAT_0_0000001_DEG_T Longitude;
};

} // namespace INSTRUMENTS

#endif // RAYMARINE_QUANTUM_MESSAGE_ID_H_
