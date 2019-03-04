#include <stdint.h>
#include "rom.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace ROM{
    const int PRG_INC = 16384;
    const int CHR_INC = 8192;
    uint8_t prg[0x8000];
    
    uint8_t rd(uint16_t address){
        return prg[address];
    };

    void load(std::string filepath){
        std::ifstream file(filepath);
        char* data = 0;
        file.seekg(0, ios::end);
        int size = file.tellg();
        file.seekg(0, ios::beg);
        data = new char[size + 1];
        data[size] = '\0';
        file.read(data, size);
        int prgSize = PRG_INC * (int) data[4];
        int chrSize = CHR_INC * (int) data[5];
        fill(data + 16, prgSize);
    }

    void fill(char data[], int length){
        for(int i = 0; i < length; i++){
            prg[i] = data[i];
            prg[i + 0x4000] = data[i];
        }
    }
};