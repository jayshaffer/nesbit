
#pragma once
#include <stdint.h>

namespace CPU6502{
    const int CARRY_FLAG_BIT = 0;
    const int ZERO_FLAG_BIT = 1;
    const int INTERRUPT_FLAG_BIT = 2;
    const int DECIMAL_FLAG_BIT = 3;
    const int BRK_FLAG_BIT = 4;
    const int EMPTY_FLAG_BIT = 5;
    const int OVERFLOW_FLAG_BIT = 6;
    const int SIGN_FLAG_BIT = 7;   

    //ADC Add With Carry
    const uint8_t ADC_I = 0x69;
    const uint8_t ADC_ZP = 0x65;
    const uint8_t ADC_ZP_X = 0x75;
    const uint8_t ADC_ABS = 0x6D;
    const uint8_t ADC_ABS_X = 0x7D;
    const uint8_t ADC_ABS_Y = 0x79;
    const uint8_t ADC_IND_X = 0x61;
    const uint8_t ADC_IND_Y = 0x71;

    //AND bitwise AND
    const uint8_t AND_I = 0x29;
    const uint8_t AND_ZP = 0x25;
    const uint8_t AND_ZP_X = 0x35;
    const uint8_t AND_ABS = 0x2D;
    const uint8_t AND_ABS_X = 0x3D;
    const uint8_t AND_ABS_Y = 0x39;
    const uint8_t AND_IND_X = 0x21;
    const uint8_t AND_IND_Y = 0x31;

    //ASL shift left
    const uint8_t ASL_ACCUM = 0x0A;
    const uint8_t ASL_ZP = 0x06;
    const uint8_t ASL_ZP_X = 0x16;
    const uint8_t ASL_ABS = 0x0E;
    const uint8_t ASL_ABS_X = 0x1E;

    //Bit test BITs
    const uint8_t BIT_ZP = 0x24;
    const uint8_t BIT_ABS = 0x24;

    //Branch
    const uint8_t BRANCH_BPL = 0x10;
    const uint8_t BRANCH_BMI = 0x30;
    const uint8_t BRANCH_BVC = 0x50;
    const uint8_t BRANCH_BVS = 0x70;
    const uint8_t BRANCH_BCC = 0x90;
    const uint8_t BRANCH_BCS = 0xB0;
    const uint8_t BRANCH_BNE = 0xD0;
    const uint8_t BRANCH_BEQ = 0xF0;

    //Break
    const uint8_t BRK = 0x00;

    //CMP
    const uint8_t CMP_I = 0xC9;
    const uint8_t CMP_ZP = 0xC5;
    const uint8_t CMP_ZP_X = 0xD5;
    const uint8_t CMP_ABS = 0xCD;
    const uint8_t CMP_ABS_X = 0xDD;
    const uint8_t CMP_ABS_Y = 0xD9;
    const uint8_t CMP_IND_X = 0xC1;
    const uint8_t CMP_IND_Y = 0xD1;

    //CPX compare x reg
    const uint8_t CPX_I = 0xE0;
    const uint8_t CPX_ZP = 0xE4;
    const uint8_t CPX_ABS = 0xEC;

    //CPY compare y reg
    const uint8_t CPY_I = 0xC0;
    const uint8_t CPY_ZP = 0xC4;
    const uint8_t CPY_ABS = 0xCC;

    //DEC
    const uint8_t DEC_ZP = 0xC6;
    const uint8_t DEC_ZPX = 0xD6;
    const uint8_t DEC_ABS = 0xCE;
    const uint8_t DEC_ABS_x = 0xDE;

    //EOR
    const uint8_t EOR_I = 0x49;
    const uint8_t EOR_ZP = 0x45;
    const uint8_t EOR_ZP_X = 0x55;
    const uint8_t EOR_ABS = 0x4D;
    const uint8_t EOR_ABS_X = 0x5D;
    const uint8_t EOR_ABS_Y = 0x59;
    const uint8_t EOR_IND_X = 0x41;
    const uint8_t EOR_IND_Y = 0x51;

    //Flags
    const uint8_t CLC = 0x18;
    const uint8_t SEC = 0x38;
    const uint8_t CLI = 0x58;
    const uint8_t SEI = 0x78;
    const uint8_t CLV = 0xB8;
    const uint8_t CLD = 0xD8;
    const uint8_t SED = 0xF8;

    //INC
    const uint8_t INC_ZP = 0xE6;
    const uint8_t INC_ZP_X = 0xF6;
    const uint8_t INC_ABS = 0xEE;
    const uint8_t INC_ABS_X = 0xFE;

    //JMP
    const uint8_t JMP_ABS = 0x4C;
    const uint8_t JMP_IND = 0x6C;

    //JSR
    const uint8_t JSR_ABS = 0x20;

    //LDA
    const uint8_t LDA_I = 0xA9;
    const uint8_t LDA_ZP = 0xA5;
    const uint8_t LDA_ZP_X = 0xB5;
    const uint8_t LDA_ABS = 0xAD;
    const uint8_t LDA_ABS_X = 0xBD;
    const uint8_t LDA_ABS_Y = 0xB9;
    const uint8_t LDA_IND_X = 0xA1;
    const uint8_t LDA_IND_Y = 0xB1;

    //LDX
    const uint8_t LDX_I = 0xA2;
    const uint8_t LDX_ZP = 0xA6;
    const uint8_t LDX_ZP_Y = 0xB6;
    const uint8_t LDX_ABS = 0xAE;
    const uint8_t LDX_ABS_Y = 0xBE;

    //LSR
    const uint8_t LSR_ACCUM = 0x4A;
    const uint8_t LSR_ZP = 0x46;
    const uint8_t LSR_ZP_X = 0x56;
    const uint8_t LSR_ABS = 0x4E;
    const uint8_t LSR_ABS_X = 0x5E;

    //NOP
    const uint8_t NOP = 0xEA;

    //ORA
    const uint8_t ORS_I = 0x09;
    const uint8_t ORS_ZP = 0x05;
    const uint8_t ORS_ZP_X = 0x15;
    const uint8_t ORS_ABS = 0x0D;
    const uint8_t ORS_ABS_X = 0x1D;
    const uint8_t ORS_ABS_Y = 0x19;
    const uint8_t ORS_IND_X = 0x01;
    const uint8_t ORS_IND_Y = 0x11;

    //Register instructions
    const uint8_t TAX = 0xAA;
    const uint8_t TXA = 0x8A;
    const uint8_t DEX = 0xCA;
    const uint8_t INX = 0xE8;
    const uint8_t TAY = 0xA8;
    const uint8_t TYA = 0x98;
    const uint8_t DEY = 0x88;
    const uint8_t INY = 0xC8;

    //Rotate Left
    const uint8_t ROL_ACCUM = 0x2A;
    const uint8_t ROL_ZP = 0x26;
    const uint8_t ROL_ZP_X = 0x36;
    const uint8_t ROL_ABS = 0x2E;
    const uint8_t ROL_ABS_X = 0x3E;

    //Rotate Left
    const uint8_t ROR_ACCUM = 0x6A;
    const uint8_t ROR_ZP = 0x66;
    const uint8_t ROR_ZP_X = 0x76;
    const uint8_t ROR_ABS = 0x6E;
    const uint8_t ROR_ABS_X = 0x7E;

    //RTI
    const uint8_t RTI = 0x40;

    //RTS
    const uint8_t RTS = 0x60;

    //SBC
    const uint8_t SBC_I = 0xE9;
    const uint8_t SBC_ZP = 0xE5;
    const uint8_t SBC_ZP_X = 0xF5;
    const uint8_t SBC_ABS = 0xED;
    const uint8_t SBC_ABS_X = 0xFD;
    const uint8_t SBC_ABS_Y = 0xF9;
    const uint8_t SBC_IND_X = 0xE1;
    const uint8_t SBC_IND_Y = 0xF1;

    //STA
    const uint8_t STA_ZP = 0x85;
    const uint8_t STA_ZP_X = 0x95;
    const uint8_t STA_ABS = 0x8D;
    const uint8_t STA_ABS_X = 0x9D;
    const uint8_t STA_ABS_Y = 0x99;
    const uint8_t STA_IND_X = 0x81;
    const uint8_t STA_IND_Y = 0x91;


    //Stack
    const uint8_t TXS = 0x9A;
    const uint8_t TSX = 0xBA;
    const uint8_t PHA = 0x48;
    const uint8_t PLA = 0x69;
    const uint8_t PHP = 0x08;
    const uint8_t PLP = 0x28;

    void exec(uint8_t instruction);

};