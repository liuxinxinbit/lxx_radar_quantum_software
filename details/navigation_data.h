#ifndef RAYMARINE_QUANTUM_NAVIGATION_DATA_H_
#define RAYMARINE_QUANTUM_NAVIGATION_DATA_H_

#include "message_id.h"

typedef uint32_t Radians_x10000_t; ///<Valid Range: 0 to (2xPi)*10,000
typedef uint32_t MetersPerSecond_x10_t;
typedef int32_t  Degrees_x10000000;

typedef uint32_t ValidData_t;
const ValidData_t c_ValidData_None = 0x00;
const ValidData_t c_ValidData_Heading = 0x01;
const ValidData_t c_ValidData_Speed = 0x02;
const ValidData_t c_ValidData_HeadingSpeed = c_ValidData_Heading | c_ValidData_Speed;
const ValidData_t c_ValidData_COG = 0x04;
const ValidData_t c_ValidData_SOG = 0x08;
const ValidData_t c_ValidData_COG_SOG = c_ValidData_COG | c_ValidData_SOG;
const ValidData_t c_ValidData_Position = 0x10;
const ValidData_t c_ValidData_AllValid = c_ValidData_HeadingSpeed | c_ValidData_COG_SOG |
                                   c_ValidData_Position;

struct NavigationData_t {
    uint32_t              MessageCode;
    ValidData_t           Validities;
    Radians_x10000_t      HeadingTrue;
    MetersPerSecond_x10_t SpeedThroughWater;
    Radians_x10000_t      COGTrue;
    MetersPerSecond_x10_t SOG;
    Degrees_x10000000     Lattitude_North;
    Degrees_x10000000     Longitude_East;
};

#endif // RAYMARINE_QUANTUM_NAVIGATION_DATA_H_
