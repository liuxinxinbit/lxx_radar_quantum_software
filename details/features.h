#ifndef RAYMARINE_QUANTUM_FEATURES_H_
#define RAYMARINE_QUANTUM_FEATURES_H_

#include "message_id.h"

// QUANTUM_FEATURES_T
typedef uint32_t QUANTUM_FEATURES_T;
const QUANTUM_FEATURES_T reserved_1                         = 0x0001; 
const QUANTUM_FEATURES_T reserved_2                         = 0x0002;
const QUANTUM_FEATURES_T reserved_3                         = 0x0004;
const QUANTUM_FEATURES_T reserved_4                         = 0x0008;
const QUANTUM_FEATURES_T reserved_5                         = 0x0010;
const QUANTUM_FEATURES_T reserved_6                         = 0x0020;
const QUANTUM_FEATURES_T reserved_7                         = 0x0040;
const QUANTUM_FEATURES_T reserved_8                         = 0x0080;
const QUANTUM_FEATURES_T FEATURE_MARPA_IN_SCANNER           = 0x0100;
const QUANTUM_FEATURES_T reserved_10                        = 0x0200;
const QUANTUM_FEATURES_T reserved_11                        = 0x0400;
const QUANTUM_FEATURES_T FEATURE_NO_DUAL_RANGE_RESTRICTIONS = 0x0800;
const QUANTUM_FEATURES_T FEATURE_QUANTUM_SCANNER            = 0x1000;
const QUANTUM_FEATURES_T reserved_14                        = 0x2000;
const QUANTUM_FEATURES_T reserved_15                        = 0x4000;

struct Features_t {
    MESSAGE_TYPE_T     m_MessageCode;
    QUANTUM_FEATURES_T m_FeatureFlags;
};

#endif // RAYMARINE_QUANTUM_FEATURES_H_
