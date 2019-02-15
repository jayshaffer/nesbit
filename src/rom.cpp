#include <stdint.h>
#include "rom.h"
#include <iostream>

using namespace std;

namespace ROM{
    uint8_t prg[0xA000];
    uint8_t prgRef[2];
    
    uint8_t rd(uint16_t address){
        uint8_t adj = address -= 0x8000;
        std::cout << std::hex << " " << unsigned(adj);
        std::cout << std::hex << " " << prg[adj];
        return prg[adj];
    };

    void fill(char data[], int length){
        for(int i = 0; i < length; i++){
            prg[i] = data[i];
        }
        for(uint16_t i = 0xC000; i < length; i++){
            prg[i] = data[i];
        }
    }
};