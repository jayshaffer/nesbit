#include "CPU6502.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

namespace CPU6502{
    uint8_t A = 0x0;
    uint8_t X = 0x0;
    uint8_t Y = 0x0;
    uint16_t PC = 0x0;
    bool C_flag = 0;
    bool Z_flag = 0;
    bool I_flag = 0;
    bool D_flag = 0;
    bool B_flag = 0;
    bool V_flag = 0;
    bool N_flag = 0;

    uint8_t RAM[0x800];

    void read(uint16_t address){

    }

    void write(uint16_t address, uint8_t value){

    }

    void exec(){
        switch(instruction){
            case ROR_ABS: 
                return;
            default:
                std::cout << "Invalid instruction " << std::hex << (int)instruction << std::endl; 
        }
    }

    void ADC_I_OP(){
        uint 
        A=A+;
    }
}
