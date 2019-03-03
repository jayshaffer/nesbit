#include "CPU6502.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "rom.h"
#include <unistd.h>

#define DEBUG

namespace CPU6502{
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
            return ROM::rd((uint16_t) address - 0x8000);
        }
        return NULL;
    }

    void write(uint16_t address, uint8_t value){

    }
    
    void reset(){
        A = 0;
        X = 0;
        Y = 0;
        C_flag = 0;
        Z_flag = 0;
        I_flag = 0;
        D_flag = 0;
        B_flag = 0;
        V_flag = 0;
        N_flag = 0;
        PC = (read(0xFFFD) << 8) | read(0xFFFC);
    }
    
    void power(){
        reset();
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
        void (*const adc_p)(uint16_t address) = adc;
        void (*const and_p)(uint16_t address) = an;
        switch(PC){
            case ADC_I:
                immediate(adc_p);
        }
        PC++;
    }

    void adc(uint16_t address){
        uint8_t m = read(address);
        bool neg = m >> 7 & 0x01;
        uint16_t A = m + A + C_flag;
        adj_C(neg);
        adj_Z();
        adj_N();
    }

    void an(uint16_t address){
        A = A & read(address);
        adj_Z();
        adj_N();
    }

    void asl(uint16_t address){
        A = A << 1;
        adj_C(false);
    }
    
    void adj_N(){
        N_flag = (A >> 7) & 0x01; 
    }

    void adj_Z(){
        Z_flag = A & 0x0000;
    }

    void adj_C(bool neg){
        C_flag = ((A >> 7) & 0x01) & !neg;
    }

    void abs(void (*operation)(uint16_t address)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t address = (first << 8) << second; 
        operation(address);
    }

    void zp(void (*operation)(uint16_t address)){
        uint16_t address = read(++PC); 
        operation(address);
    }

    void zpx(void (*operation)(uint16_t address)){
        uint16_t result = read(++PC) + X;
        operation((uint16_t)(uint8_t) result);
    }

    void zpy(void (*operation)(uint16_t address)){
        uint16_t result = read(++PC) + Y;
        operation((uint16_t)(uint8_t) result);
    }

    void absx(void (*operation)(uint16_t address)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t address = (first << 8) | second;
        operation(address + X);
    }

    void absy(void (*operation)(uint16_t address)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t address = (first << 8) | second;
        operation(address + Y);
    }
    
    void immediate(void (*operation)(uint16_t address)){
        operation(++PC);
    }

    void indirect(void (*operation)(uint16_t address)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t indAddress = (first << 8) | second;
        uint16_t address = read(indAddress + 1) << 8 | read(indAddress);
        operation(address);
    }

    void indexIndirX(void (*operation)(uint16_t address)){
        uint16_t indAddress = read(++PC) + X; 
        uint16_t address = read(indAddress + 1) << 8 | read(indAddress);
        operation(address);
    }

    void indexIndirY(void (*operation)(uint16_t address)){
        uint16_t indAddress = read(++PC) + Y; 
        uint16_t address = read(indAddress + 1) << 8 | read(indAddress);
        operation(address);
    }

    void indirIndexX(void (*operation)(uint16_t address)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t indAddress = (first << 8) | second; 
        uint16_t address = read(indAddress + 1) << 8 | read(indAddress);
        operation(address + X);
    }

    void indirIndexY(void (*operation)(uint16_t address)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t indAddress = (first << 8) | second; 
        uint16_t address = read(indAddress + 1) << 8 | read(indAddress);
        operation(address + Y);
    }

}
