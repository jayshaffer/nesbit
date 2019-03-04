#pragma once
#include <stdint.h>

namespace RAM{
    void rd(uint16_t address);
    void wr(uint16_t address, uint8_t value);
}