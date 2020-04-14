#ifndef RAYMARINE_QUANTUM_SPOKE_DATA_H_
#define RAYMARINE_QUANTUM_SPOKE_DATA_H_

#include "message_id.h"

// QUANTUM_SPOKE_PKT_HDR_T
struct QUANTUM_SPOKE_PKT_HDR_T {
    uint16_t SequenceNumber;    // incrementing sequence number, wraps at 65535
    uint8_t  CompressionFormat; // 0- None, 1-RLE, etc.
    uint8_t  SpokesInPacket;    // Number of spokes in this packet 1-64.
};

// QUANTUM_SPOKE_DATA_HDR_T
struct QUANTUM_SPOKE_DATA_HDR_T {
    uint16_t          SamplesPerSpoke; //!< count of samples in each spoke
    uint16_t          SpokesPerScan; //!< count of spokes in each scan
    uint8_t           BitsPerSample; //!< 8 = 8 bits max
    QUANTUM_CHANNEL_T Channel; //!< 0-Default, 1- 2nd Range Dual Range Mode
    uint16_t          InstrumentedRange; //!< sample offset for instrumented range
    uint16_t          Bearing; //!< 0-249 (max spokes per scan)
}; 

// QUANTUM_SPOKE_HEADER_T
struct QUANTUM_SPOKE_HEADER_T {
    QUANTUM_SPOKE_PKT_HDR_T  PktHdr;
    QUANTUM_SPOKE_DATA_HDR_T DataHdr;
    uint16_t                 DataLength; //!< length of spoke data field
};

// QUANTUM_SPOKE_T
struct QUANTUM_SPOKE_T {
    QUANTUM_SPOKE_HEADER_T SpokeHeader;
    uint8_t                SpokeData[1];
};

// QUANTUM_SPOKE_PACKET_T
struct SpokeData_t {
    uint32_t        MessageId;
    QUANTUM_SPOKE_T Spoke;
};

/*
 * Data Compression (Run Length Encoding)
 * Spoke Data is compressed using a Run Length Encoded (RLE) technique. Data is 
 * compressed on byte by byte basis.Whenever a sequence of 4 bytes or more with 
 * the same value is detected, it is replaced by the following sequence of three 
 * bytes, 0x5C (escape character), sequence length, byte value. Whenever the 
 * escape character (0x5C) is encountered in the uncompressed data stream, it is 
 * replaced with the 0x5B character. This gives a similar return level on the 
 * display and ensures that the compressed data can never be larger than the 
 * uncompressed data.
 *
 * For example :
 * The following sequence 
 * 0x00, 0x0F, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0x03, 
 * 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,0x5C, 0x0A
 * Would be encoded
 * 0x00, 0x0F, 0xAA, 0x5C, 0x08, 0xFF, 0xCC, 0x03, 0x00, 0x00, 0x03, 0x5C, 0x06, 
 * 0x00, 0x03,0x5B, 0x0A
*/
// struct SpokeData_t {
//     MESSAGE_TYPE_T         m_MessageCode;
//     QUANTUM_SPOKE_PACKET_T m_SpokePacket;
// };

#endif // RAYMARINE_QUANTUM_SPOKE_DATA_H_
