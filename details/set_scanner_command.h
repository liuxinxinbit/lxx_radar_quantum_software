#ifndef RAYMARINE_QUANTUM_SET_SCANNER_COMMAND_H_
#define RAYMARINE_QUANTUM_SET_SCANNER_COMMAND_H_

#include "message_id.h"

/**
 * ‘Nios Reset’ 
 * Performs software reset of the IF processor (IF board) 
 * 
 * ‘SystemReset’ 
 * Performs Software Reset of entire system (PSU board and IF board) 
 * 
 * ‘ResetFactoryDefaults’
 * Re-Initialises all settings to factory defaults, resets system
 */

typedef uint8_t QuantumScannerCommand_t;
static const QuantumScannerCommand_t cQuantumScannerCommandNone = 0;
static const QuantumScannerCommand_t cQuantumScannerCommandIFReset = 1;
static const QuantumScannerCommand_t cQuantumScannerCommandSystemReset = 2;
static const QuantumScannerCommand_t cQuantumScannerCommandResetFactoryDefaults = 3;

struct SetScannerCommand_t {
    MESSAGE_TYPE_T          m_MessageCode;
    QuantumScannerCommand_t m_ScannerCommand;
};

#endif // RAYMARINE_QUANTUM_SET_SCANNER_COMMAND_H_