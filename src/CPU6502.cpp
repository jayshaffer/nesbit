#include "CPU6502.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "rom.h"
#include <unistd.h>

#define DEBUG

namespace CPU6502{
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint16_t PC = 0;
    uint16_t SP;
    bool C_flag = 0;
    bool Z_flag = 0;
    bool I_flag = 0;
    bool D_flag = 0;
    bool B_flag = 0;
    bool V_flag = 0;
    bool N_flag = 0;

    uint8_t RAM[0x800];

    uint8_t read(uint16_t address){
        if(address < 0x800){
            return RAM[address];
        }
        else if(address < 0x2000){
            return RAM[address - 0x800];
        }
        else if(address >= 0x8000){
            return ROM::rd(address - 0x8000);
        }
        return NULL;
    }

    void write(uint16_t address, uint8_t value){

    }
    
    void reset(){
        A = 0;
        X = 0;
        Y = 0;
        PC = (read(0xFFFD) << 8) | read(0xFFFC);
        while(true){
            exec();
            usleep(100000);
        }
    }

    void exec(){
        uint8_t instruction = read(PC);
        #ifdef DEBUG
            std::cout << std::hex << unsigned(instruction) << "  "; 
            std::cout << std::hex << "A:" << "0x" << A << " ";
            std::cout << std::hex << "X:" << "0x" << X << " ";
            std::cout << std::hex << "Y:" << "0x" << Y << " ";
            std::cout << std::hex << "P:" << "0x" << PC << " ";
            std::cout << std::hex << "SP:" << "0x" << SP << " ";
            std::cout << std::hex << "PPU:" << "0x" << 0;
            std::cout << std::endl;
        #endif
        
        // switch(instruction){
        //     case ADC_I:
        //         ADC_I_OP();
        //         break;
        //     case ADC_ZP:
        //         ADC_ZP_OP();
        //         break;

        // }
        PC++;
    }

    void ADC_I_OP(){
    }

    void ADC_ZP_OP(){
        
    }

    void ADC_ZP_X_OP(){

    }
}
