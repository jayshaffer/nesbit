
#include "ram.h"

namespace RAM{
    uint8_t MEM[0x800];
    uint8_t rd(uint8_t address){
        return MEM[address];
    };
    void wr(uint16_t address, uint8_t value){
        MEM[address] = value;
    };
}