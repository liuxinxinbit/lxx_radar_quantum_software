#ifndef BLUEPRINT_UTILS_RLE_H_
#define BLUEPRINT_UTILS_RLE_H_

#include <vector>
#include <cstdint>
#include <string.h>

/**
 *  declare
 */

inline std::size_t          RLE_DecodeSize(const uint8_t* data, std::size_t size);
inline std::vector<uint8_t> RLE_Decoding(const uint8_t* data, std::size_t size);
inline std::vector<uint8_t> RLE_Encoding(const uint8_t* data, std::size_t size);

inline std::size_t          RLE_DecodeSize(const std::vector<uint8_t>& data);
inline std::vector<uint8_t> RLE_Decoding(const std::vector<uint8_t>& data);
inline std::vector<uint8_t> RLE_Encoding(const std::vector<uint8_t>& data);

/**
 *  implement
 */
inline std::size_t RLE_DecodeSize(const uint8_t* data, std::size_t size) {
    std::vector<uint8_t> tmp(data, data + size);
    return RLE_DecodeSize(tmp);
}

inline std::vector<uint8_t> RLE_Decoding(const uint8_t* data, std::size_t size){
    std::vector<uint8_t> tmp(data, data + size);
    return RLE_Decoding(tmp);
}

inline std::vector<uint8_t> RLE_Encoding(const uint8_t* data, std::size_t size){
    std::vector<uint8_t> tmp(data, data + size);
    return RLE_Encoding(tmp);
}

inline std::size_t RLE_DecodeSize(const std::vector<uint8_t>& data) {
    std::size_t len = 0;
    int32_t     i = 0;
    while (i < data.size()) {
        if (data[i] == 0x5C) {
            len += data[i + 1];
            i += 3;
        } else {
            ++len;
            ++i;
        }
    }
    return len;
}

inline std::vector<uint8_t> RLE_Decoding(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> decode(RLE_DecodeSize(data));
    int i     = 0;
    int index = 0;
    while (i < data.size()) {
        if (data[i] == 0x5C) {
            memset(decode.data() + index, data[i + 2], data[i + 1]);
            index += data[i + 1];
            i += 3;
        } else {
            if (data[i] == 0x5B) {
                decode[index] = 0x5C;
                ++index;
            } else {
                decode[index] = data[i];
                ++index;
            }
            ++i;
        }
    }
    return std::move(decode);
}

inline std::vector<uint8_t> RLE_Encoding(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> encode(data);
    std::size_t data_size = data.size();
    if (data_size == 1) return encode;
    uint8_t last = data[0]; // last data
    uint8_t curr = 0;       // current data
    int32_t rlen = 1;       // run length
    int32_t alen = 0;       // all length
    for (int32_t i = 1; i <data_size; ++i) {
        curr = data[i];
        if (curr == last) {
            ++rlen;
        } else {
            if (rlen == 1) {
                if (last == 0x5C) {
                    encode[alen++] = 0x5B;
                } else {
                    encode[alen++] = last;
                }
            } else if (rlen < 4) {
                for (int i = 0; i < rlen; ++i) encode[alen++] = last;
                rlen = 1;
            } else {
                encode[alen++] = 0x5C;
                encode[alen++] = rlen;
                encode[alen++] = last;
                rlen = 1;
            }
            last = curr;
        }
    }
    if (rlen == 1) {
        encode[alen++] = last;
    } else {
        encode[alen++] = 0x5C;
        encode[alen++] = rlen;
        encode[alen++] = last;
    }
    return std::move(
                std::vector<uint8_t>(encode.cbegin(), encode.cbegin() + alen));
}

#endif // BLUEPRINT_UTILS_RLE_H_
