#include <stdint.h>
#include "rom.h"

namespace ROM{
    uint8_t mem[0xFFFF - 0x8000];
    
    uint8_t rd(uint8_t address){
        uint8_t adj -= 0x8000; 
    };

    void fill(uint8_t* data[], int length){
        for(uint8_t i = 0; i < length; i++){
            mem[i] = data[i];
        }
    }
}