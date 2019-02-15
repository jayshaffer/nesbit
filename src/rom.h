#include <stdint.h>

namespace ROM{
    uint8_t rd(uint16_t address);
    void fill(char data[], int length);
}