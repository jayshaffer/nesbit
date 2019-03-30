#include "CPU6502.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "rom.h"
#include <unistd.h>
#include <stack>

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
    uint8_t stack[0x1FF]; 
    void (*const adc_p)(uint16_t* m) = adc;
    void (*const and_p)(uint16_t* m) = an;
    void (*const ora_p)(uint16_t* m) = ora;
    void (*const asl_p)(uint16_t* m) = asl;
    void (*const jsr_p)(uint16_t* m) = jsr;
    void (*const bit_p)(uint16_t* m) = bit;
    void (*const rol_p)(uint16_t* m) = rol;
    void (*const lsr_p)(uint16_t* m) = lsr;
    void (*const eor_p)(uint16_t* m) = eor;
    void (*const bvc_p)(uint16_t* m) = bvc;
    void (*const ror_p)(uint16_t* m) = ror;
    void (*const bpl_p)(uint16_t* m) = bpl;
    void (*const bmi_p)(uint16_t* m) = bmi;
    void (*const bvs_p)(uint16_t* m) = bvs;
    void (*const bcc_p)(uint16_t* m) = bcc;
    void (*const bcs_p)(uint16_t* m) = bcs;
    void (*const bne_p)(uint16_t* m) = bne;
    void (*const beq_p)(uint16_t* m) = beq;
    void (*const sta_p)(uint16_t* m) = sta;
    void (*const lda_p)(uint16_t* m) = lda;
    void (*const ldx_p)(uint16_t* m) = ldx;
    void (*const cpy_p)(uint16_t* m) = cpy;
    void (*const cmp_p)(uint16_t* m) = cmp;
    void (*const dec_p)(uint16_t* m) = dec;
    void (*const sbc_p)(uint16_t* m) = sbc;
    void (*const cpx_p)(uint16_t* m) = cpx;
    void (*const inc_p)(uint16_t* m) = inc;

    uint8_t* read(uint16_t address){
        uint8_t m;
        uint8_t* m_p;
        if(address < 0x800){
            m = RAM[address];
        }
        else if(address < 0x2000){
            m = RAM[address - 0x800];
        }
        else if(address >= 0x8000){
            m = ROM::rd((uint16_t) address - 0x8000);
        }
        m_p = &m;
        return m_p;
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
        V_flag = 0;
        N_flag = 0;
        std::fill_n(stack, 0x1ff, 0);
        INTERRUPT_flag = 0;
        PC = (*read(0xFFFD) << 8) | *read(0xFFFC);
    }
    
    void power(){
        reset();
        while(true){
            exec();
            usleep(100000);
        }
    }

    void exec(){
        uint8_t instruction = *read(PC);
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
        switch(PC){
            case 0x01:
                indirect(adc_p);
                break;
            case 0x05:
                zp(ora_p);
                break;
            case 0x06:
                zp(asl_p);
                break;
            case 0x08:
                php();
                break;
            case 0x09:
                immediate(ora_p);
                break;
            case 0x10:
                relative(bpl_p);
                break;
            case 0x11:
                indirectY(ora_p);
                break;
            case 0x15:
                zpx(ora_p);
                break;
            case 0x16:
                zpx(asl_p);
                break;
            case 0x18:
                clc();
                break;
            case 0x19:
                absy(ora_p);
                break;
            case 0x1d:
                absx(ora_p);
                break;
            case 0x1e:
                absx(asl_p);
                break;
            case 0x20:
                abs(jsr_p);
                break;
            case 0x21:
                indirectX(and_p);
                break;
            case 0x24:
                abs(bit_p);
                break;
            case 0x25:
                zp(and_p);
                break;
            case 0x26:
                zp(rol_p);
                break;
            case 0x28:
                plp();
                break;
            case 0x29:
                immediate(and_p);
                break;
            case 0x2d:
                abs(and_p);
                break;
            case 0x2e:
                abs(rol_p);
                break;
            case 0x30:
                relative(bmi_p);
                break;
            case 0x31:
                indirectY(and_p);
                break;
            case 0x35:
                zpx(and_p);
                break;
            case 0x36:
                zpx(rol_p);
                break;
            case 0x38:
                sec();
                break;
            case 0x39:
                absy(and_p);
                break;
            case 0x3d:
                absx(and_p);
                break;
            case 0x3e:
                absx(rol_p);
                break;
            case 0x40:
                rti();
                break;
            case 0x41:
                indirectX(eor_p);
                break;
            case 0x45:
                zp(eor_p);
                break;
            case 0x46:
                zp(lsr_p);
                break;
            case 0x48:
                pha();
                break;
            case 0x49:
                immediate(eor_p);
                break;
            case 0x4A:
                break;
            case 0x4c:
                jmpA(instruction);
                break;
            case 0x4d:
                abs(eor_p);
                break;
            case 0x4E:
                abs(lsr_p);
                break;
            case 0x50:
                relative(bvc_p);
                break;
            case 0x51:
                indirectY(eor_p);
                break;
            case 0x55:
                zpx(eor_p);
                break;
            case 0x56:
                zpx(lsr_p);
                break;
            case 0x58:
                cli();
                break;
            case 0x59:
                absy(eor_p);
                break;
            case 0x5d:
                absx(eor_p);
                break;
            case 0x5e:
                absx(lsr_p);
                break;
            case 0x60:
                rts();
                break;
            case 0x61:
                indirectX(adc_p);
                break;
            case 0x65:
                zp(adc_p);
                break;
            case 0x66:
                zp(ror_p);
                break;
            case 0x69:
                pla();
                break;
            case 0x6a:
                break;
            case 0x6c:
                jmpI(instruction);
                break;
            case 0x6d:
                abs(adc_p);
                break;
            case 0x6e:
                abs(ror_p);
                break;
            case 0x70:
                relative(bvs_p);
                break;
            case 0x71:
                indirectY(adc_p);
                break;
            case 0x75:
                zpx(adc_p);
                break;
            case 0x76:
                zpx(ror_p);
                break;
            case 0x78:
                sei();
                break;
            case 0x79:
                absy(adc_p);
                break;
            case 0x7d:
                absx(adc_p);
                break;
            case 0x7e:
                absx(ror_p);
                break;
            case 0x81:
                indirectX(sta_p);
                break;
            case 0x85:
                zp(sta_p);
                break;
            case 0x88:
                dey();
                break;
            case 0x8a:
                txa();
                break;
            case 0x8d:
                abs(sta_p);
                break;
            case 0x90:
                relative(bcc_p);
                break;
            case 0x91:
                indirectY(sta_p);
                break;
            case 0x95:
                zpx(sta_p);
                break;
            case 0x98:
                tya();
                break;
            case 0x99:
                absy(sta_p);
                break;
            case 0x9a:
                txs();
                break;
            case 0x9d:
                absx(sta_p);
                break;
            case 0xa1:
                indirectX(lda_p);
                break;
            case 0xa2:
                immediate(ldx_p);
                break;
            case 0xa5:
                zp(lda_p);
                break;
            case 0xa6:
                zp(ldx_p);
                break;
            case 0xa8:
                tay();
                break;
            case 0xa9:
                immediate(lda_p);
                break;
            case 0xaa:
                tax();
                break;
            case 0xad:
                abs(lda_p);
                break;
            case 0xae: 
                abs(ldx_p);
                break;
            case 0xb0:
                relative(bcs_p);
                break;
            case 0xb1:
                indirectY(lda_p);
                break;
            case 0xb5:
                zpx(lda_p);
                break;
            case 0xb6:
                zpy(ldx_p);
                break;
            case 0xb8:
                clv();
                break;
            case 0xb9:
                absy(lda_p);
                break;
            case 0xba:
                tsx();
                break;
            case 0xbd:
                absx(lda_p);
                break;
            case 0xbe:
                absy(ldx_p);
                break;
            case 0xc0:
                immediate(cpy_p);
                break;
            case 0xc1:
                indirectX(cmp_p);
                break;
            case 0xc4:
                zp(cpy_p);
                break;
            case 0xc5:
                zp(cmp_p);
                break;
            case 0xc6:
                zp(dec_p);
                break;
            case 0xc8:
                iny();
                break;
            case 0xc9:
                immediate(cmp_p);
                break;
            case 0xca:
                dex();
                break;
            case 0xcc:
                abs(cpy_p);
                break;
            case 0xcd:
                abs(cmp_p);
                break;
            case 0xce:
                abs(dec_p);
                break;
            case 0xd0:
                relative(bne_p);
                break;
            case 0xd1:
                indirectY(cmp_p);
                break;
            case 0xd5:
                zpx(cmp_p);
                break;
            case 0xd6:
                zpx(dec_p);
                break;
            case 0xd8:
                cld();
                break;
            case 0xd9:
                absy(cmp_p);
                break;
            case 0xdd:
                absx(cmp_p);
                break;
            case 0xde:
                absx(dec_p);
                break;
            case 0xe0:
                immediate(cpy_p);
                break;
            case 0xe1:
                indirectX(sbc_p);
                break;
            case 0xe4:
                zp(cpx_p);
                break;
            case 0xe5:
                zp(sbc_p);
                break;
            case 0xe6:
                zp(inc_p);
                break;
            case 0xe8:
                inx();
                break;
            case 0xe9:
                immediate(sbc_p);
                break;
            case 0xea:
                nop();
                break;
            case 0xec:
                abs(cpx_p);
                break;
            case 0xed:
                abs(sbc_p);
                break;
            case 0xee:
                abs(inc_p);
                break;
            case 0xf0:
                relative(beq);
                break;
            case 0xf1:
                indirectY(sbc_p);
                break;
            case 0xf5:
                zpx(sbc_p);
                break;
            case 0xf6:
                zpx(inc_p);
                break;
            case 0xf8:
                sed();
                break;
            case 0xf9:
                absy(sbc_p);
                break;
            case 0xfd:
                absx(sbc_p);
                break;
            case 0xfe:
                absx(inc_p);
                break;
            default:
                throw std::invalid_argument( "Invalid instruction received" );
        }
        PC++;
    }

    bool neg(uint8_t m){
        return (m >> 7) & 0x01;
    }

    void adc(uint16_t* m){
        uint16_t sum = *m + A + C_flag;
        C_flag = (sum > 0xFF);
        V_flag = ~(A ^ *m) & (A ^ sum) & 0x80;
        A = (uint8_t) sum;
        adj_Z(A);
        adj_N(A);
    }

    void an(uint16_t* m){
        A = A & *m;
        adj_Z(A);
        adj_N(A);
    }

    void asl(uint16_t* m){
        bool isNeg = neg(*m);
        *m = *m << 1;
        adj_C(*m, isNeg);
    }

    void bcc(uint16_t* m){
        if(C_flag){return;}
        PC += *m; 
    }

    void bcs(uint16_t* m){
        if(!C_flag){return;}
        PC += *m; 
    }

    void beq(uint16_t* m){
        if(!Z_flag){return;}
        PC += *m; 
    }

    void bmi(uint16_t* m){
        if(!N_flag){return;}
        PC += *m;
    }

    void bne(uint16_t* m){
        if(Z_flag){return;}
        PC += *m; 
    }
    
    void bpl(uint16_t* m){
        if(N_flag){return;}
        PC += *m;
    }

    void bvc(uint16_t* m){
        if(V_flag){return;}
        PC += *m;
    }

    void bvs(uint16_t* m){
        if(!V_flag){return;}
        PC += *m;
    }

    void bmi(){
        if(!V_flag){return;}
    }

    void bit(uint16_t* m){
        uint8_t result = A | *m;
        N_flag = ((result >> 7) & 0x01);
        V_flag = ((result >> 6) & 0x01);
        Z_flag = result == 0;
    }

    void brk(){
        stack[SP++] = PC >> 8;
        stack[SP++] = PC << 8;
        php();
        PC = ((*read(0xFFFF) << 8) | *read(0xFFFE));
    }

    void clc(){
        C_flag = 0;
    }

    void cld(){
        D_flag = 0;
    }

    void cli(){
        I_flag = 0;
    }

    void clv(){
        V_flag = 0;
    }

    void cmp(uint16_t* m){
        uint8_t result = A - *m;
        C_flag = A >= *m;
        Z_flag = A == *m;
        N_flag = neg(result);
    }

    void cpx(uint16_t* m){
        uint8_t result = X - *m;
        C_flag = X >= *m;
        Z_flag = X == *m;
        N_flag = neg(result);
    }

    void cpy(uint16_t* m){
        uint8_t result = Y - *m;
        C_flag = Y >= *m;
        Z_flag = Y == *m;
        N_flag = neg(result);
    }

    void dec(uint16_t* m){
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

    void eor(uint16_t* m){
        A = A ^ *m;
        Z_flag = A ==0;
        N_flag = neg(A);
    }

    void inc(uint16_t* m){
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

    void jmpA(uint8_t m){
        PC = m;
    }

    void jmpI(uint8_t m){
        PC = *read(m);
    }

    void lda(uint16_t* m){
        A = *m;
        Z_flag = A == 0;
        N_flag = neg(A);
    }

    void ldx(uint16_t* m){
        X = *m;
        Z_flag = X == 0;
        N_flag = neg(X);
    }

    void ldy(uint16_t* m){
        Y = *m;
        Z_flag = Y == 0;
        N_flag = neg(Y);
    }

    void lsr(uint16_t* m){
        uint8_t result = *m >> 1;
        C_flag = (*m << 7) == 0;
        Z_flag = result == 0;
        N_flag = neg(result);
        *m = result;
    }
    
    void nop(){
        return;
    }

    void ora(uint16_t* m){
        A = A|*m;
        Z_flag = A == 0;
        N_flag = neg(A);
    }

    void pha(){
        stack[SP++] = A;
    }

    void php(){
        uint8_t byte = 0;
        byte = (byte | (N_flag << 7)); 
        byte = (byte | (V_flag << 6)); 
        byte = (byte | (1 << 5));
        byte = (byte | (1 << 4));
        byte = (byte | (D_flag << 3));
        byte = (byte | (I_flag << 2));
        byte = (byte | (Z_flag << 1));
        byte = (byte | (C_flag << 0));
        stack[SP++] = byte;
    }

    void pla(){
        A = stack[--SP];
        Z_flag = A == 0;
        N_flag = neg(A);
    }
    
    void plp(){
        uint8_t flags = stack[--SP];
        N_flag = flags & 0x80;
        V_flag = flags & 0x40;
        D_flag = flags & 0x08;
        I_flag = flags & 0x04;
        Z_flag = flags & 0x02;
        C_flag = flags & 0x01;
    }
    
    void jsr(uint16_t* m){
        stack[SP++] = PC - 1;
        PC = *m;
    }

    void rol(uint16_t* m){
        uint8_t newCarry = (*m >> 7);
        *m = ((*m << 1) | C_flag);
        C_flag = newCarry;
        Z_flag = A == 0; 
        N_flag = neg(*m);
    }

    void ror(uint16_t* m){
        uint8_t newCarry = (*m << 7);
        *m = ((*m >> 1) | (C_flag << 7));
        C_flag = newCarry;
        Z_flag = A == 0; 
        N_flag = neg(*m);
    }

    void adj_N(uint8_t m){
        N_flag = (m >> 7) == 0x01; 
    }

    void rti(){
        plp(); 
        uint8_t PC = stack[--SP];
    }

    void rts(){
       PC = stack[--SP]; 
    }

    void sbc(uint16_t* m){
        uint16_t m_p = ~*m;
        adc(&m_p);
    }

    void sec(){
        C_flag = 1;
    }

    void sed(){
        D_flag = 1;
    }

    void sei(){
        I_flag = 1;
    }

    void sta(uint16_t* m){
        *m = A;
    }

    void stx(uint16_t* m){
        *m = X;
    }

    void sty(uint16_t* m){
        *m = Y;
    }

    void tax(){
        X = A;
        Z_flag = X == 0;
        N_flag = neg(X);
    }

    void tay(){
        Y = A;
        Z_flag = Y == 0;
        N_flag = neg(Y);
    }

    void tsx(){
        X = SP;
    }

    void txa(){
        A = X;
        Z_flag = A == 0;
        N_flag = neg(A);
    }

    void txs(){
        SP = X;
    }

    void tya(){
        A = Y;
        Z_flag = A == 0;
        N_flag = neg(A);
    }

    void adj_Z(uint8_t m){
        Z_flag = m == 0;
    }

    void adj_C(uint8_t m, bool isNeg){
        C_flag = neg(m) & !isNeg;
    }

    void abs(void (*operation)(uint16_t* m)){
        uint8_t first = *read(++PC);
        uint8_t second = *read(++PC);
        uint16_t address = (uint16_t) *read((second << 8) << first); 
        operation(&address);
    }

    void zp(void (*operation)(uint16_t* m)){
        uint16_t m = *read(++PC); 
        operation(&m);
    }

    void zpx(void (*operation)(uint16_t* m)){
        uint16_t m = *read(++PC) + X;
        operation(&m);
    }

    void zpy(void (*operation)(uint16_t* m)){
        uint16_t m = *read(++PC) + Y;
        operation(&m);
    }

    void absx(void (*operation)(uint16_t* address)){
        uint8_t first = *read(++PC);
        uint8_t second = *read(++PC);
        uint16_t address = (uint16_t) *read((second << 8) | first  + X);
        operation(&address);
    }

    void absy(void (*operation)(uint16_t* m)){
        uint8_t first = *read(++PC);
        uint8_t second = *read(++PC);
        uint16_t address = (uint16_t) *read((second << 8) | first  + Y);
        operation(&address);
    }
    
    void immediate(void (*operation)(uint16_t* m)){
        uint16_t m = ++PC;
        operation(&m);
    }

    void indirect(void (*operation)(uint16_t* m)){
        uint8_t first = *read(++PC);
        uint8_t second = *read(++PC);
        uint16_t indAddress = (second << 8) | first;
        uint16_t m = *read(*read(indAddress + 1) << 8 | *read(indAddress));
        operation(&m);
    }

    void indirectX(void (*operation)(uint16_t* m)){
        uint16_t indAddress = *read(++PC) + X; 
        uint16_t m = *read(*read(indAddress + 1) << 8 | *read(indAddress));
        operation(&m);
    }

    void indirectY(void (*operation)(uint16_t* m)){
        uint8_t first = *read(++PC);
        uint8_t second = *read(++PC);
        uint16_t indAddress = (second << 8) | first; 
        uint16_t m = *read(*read(indAddress + 1) << 8 | *read(indAddress) + Y);
        operation(&m);
    }

    void relative(void (*operation)(uint16_t* m)){
        PC += 2;
        uint16_t address = PC;
        if(address & 0x80){address = ~(address) + 1;}
        operation(&address);
    }

}
