#include <stdint.h>
#include "rom.h"
#include <iostream>

using namespace std;

namespace ROM{
    uint8_t prg[0x8000];
    
    uint8_t rd(uint16_t address){
        return prg[address];
    };

    void fill(char data[], int length){
        std::cout << length << std::endl;
        for(int i = 0; i < length; i++){
            prg[i] = data[i];
            prg[i + 0x4000] = data[i];
        }
    }
};