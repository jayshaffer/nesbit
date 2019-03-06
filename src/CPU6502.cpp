#include "CPU6502.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "rom.h"
#include <unistd.h>

#define DEBUG

namespace CPU6502{
    uint16_t PC = 0;
    uint8_t A = 0;
    uint8_t X = 0;
    uint8_t Y = 0;
    uint16_t SP = 0;
    bool C_flag = 0;
    bool Z_flag = 0;
    bool I_flag = 0;
    bool D_flag = 0;
    bool B_flag = 0;
    bool V_flag = 0;
    bool N_flag = 0;
    bool INTERRUPT_flag = 0;
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
        INTERRUPT_flag = 0;
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
        void (*const adc_p)(uint8_t m) = adc;
        void (*const and_p)(uint8_t m) = an;
        switch(PC){
            case ADC_I:
                immediate(adc_p);
        }
        PC++;
    }

    bool neg(uint8_t m){
        return (m >> 7) & 0x01;
    }

    void adc(uint8_t m){
        bool isNeg = neg(m); 
        A = m + A + C_flag;
        adj_C(A, isNeg);
        adj_Z(A);
        adj_N(A);
    }

    void an(uint8_t m){
        A = A & m;
        adj_Z(A);
        adj_N(A);
    }

    void asl(uint8_t* m){
        bool isNeg = neg(*m);
        *m = *m << 1;
        adj_C(*m, isNeg);
    }

    void bcc(){

    }

    void bit(){

    }

    void brk(){
        return;
    }

    void clc(){
        C_flag = 0;
    }

    void cli(){
        INTERRUPT_flag = 0;
    }

    void clv(){
        V_flag = 0;
    }

    void cmp(uint8_t m){
        uint8_t result = A - m;
        C_flag = A >= m;
        Z_flag = A == m;
        N_flag = neg(result);
    }

    void cpx(uint8_t m){
        uint8_t result = X - m;
        C_flag = X >= m;
        Z_flag = X == m;
        N_flag = neg(result);
    }

    void cpy(uint8_t m){
        uint8_t result = Y - m;
        C_flag = Y >= m;
        Z_flag = Y == m;
        N_flag = neg(result);
    }

    void dec(uint8_t* m){
        *m-=1; 
        Z_flag = *m == 0;
        N_flag = neg(*m);
    }

    void dex(){
        X-=1;
        Z_flag = X == 0;
        N_flag = neg(X);
    }

    void dey(){
        Y-=1;
        Z_flag = Y == 0;
        N_flag = neg(Y);
    }

    void eor(uint8_t m){
        A = A ^ m;
        Z_flag = A ==0;
        N_flag = neg(A);
    }

    void inc(uint8_t* m){
        *m+=1;
        Z_flag = *m == 0;
        N_flag = neg(*m);
    }

    void inx(){
        X+=1;
        Z_flag = X == 0;
        N_flag = neg(X);
    }

    void iny(){
        Y+=1;
        Z_flag = Y == 0;
        N_flag = neg(Y);
    }

    void jmpA(uint16_t m){
        PC = m;
    }

    void jmpI(uint16_t m){
        PC = read(m);
    }

    void lda(uint8_t m){
        A = m;
        Z_flag = A == 0;
        N_flag = neg(A);
    }

    void ldx(uint8_t m){
        X = m;
        Z_flag = X == 0;
        N_flag = neg(X);
    }

    void ldy(uint8_t m){
        Y = m;
        Z_flag = Y == 0;
        N_flag = neg(Y);
    }

    void lsr(uint8_t* m){
        uint8_t result = *m >> 1;
        C_flag = (*m << 7) == 0;
        Z_flag = result == 0;
        N_flag = neg(result);
        *m = result;
    }
    
    void nop(){
        return;
    }

    void ora(uint8_t m){
        A = A|m;
        Z_flag = A == 0;
        N_flag = neg(A);
    }

    void pha(){
    }

    void php(){
    }

    void pla(){
    }
    
    void plp(){
    }

    void rol(){
    }

    void ror(){
    }

    void adj_N(uint8_t m){
        N_flag = (m >> 7) == 0x01; 
    }

    void adj_Z(uint8_t m){
        Z_flag = m == 0;
    }

    void adj_C(uint8_t m, bool isNeg){
        std::cout << std::hex << (int) (m >> 7) << std::endl;
        C_flag = neg(m) & !isNeg;
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
    
    void immediate(void (*operation)(uint8_t m)){
        operation(++PC);
    }

    void indirect(void (*operation)(uint8_t m)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t indAddress = (first << 8) | second;
        uint8_t m = read(read(indAddress + 1) << 8 | read(indAddress));
        operation(m);
    }

    void indexIndirX(void (*operation)(uint8_t m)){
        uint16_t indAddress = read(++PC) + X; 
        uint16_t m = read(read(indAddress + 1) << 8 | read(indAddress));
        operation(m);
    }

    void indexIndirY(void (*operation)(uint8_t m)){
        uint16_t indAddress = read(++PC) + Y; 
        uint16_t m = read(read(indAddress + 1) << 8 | read(indAddress));
        operation(m);
    }

    void indirIndexX(void (*operation)(uint8_t m)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t indAddress = (first << 8) | second; 
        uint16_t m = read(read(indAddress + 1) << 8 | read(indAddress) + X);
        operation(m);
    }

    void indirIndexY(void (*operation)(uint8_t m)){
        uint8_t first = read(++PC);
        uint8_t second = read(++PC);
        uint16_t indAddress = (first << 8) | second; 
        uint16_t m = read(read(indAddress + 1) << 8 | read(indAddress) + Y);
        operation(m);
    }

}
