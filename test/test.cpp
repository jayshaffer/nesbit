#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "CPU6502.cpp"

const int PRG_INC = 16384;
const int CHR_INC = 8192;

void loadTestRom(){
    std::ifstream file("donkeykong.nes");
    char* data = 0;
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);
    data = new char[size + 1];
    data[size] = '\0';
    file.read(data, size);
    int prgSize = PRG_INC * (int) data[4];
    int chrSize = CHR_INC * (int) data[5];
    ROM::fill(data + 16, prgSize);
    CPU6502::reset();
}

TEST_CASE( "CPU is reset", "" ) {
    CPU6502::X = 1;
    CPU6502::Y = 1;
    CPU6502::A = 1;
    CPU6502::C_flag = 1;
    CPU6502::Z_flag = 1;
    CPU6502::I_flag = 1;
    CPU6502::D_flag = 1;
    CPU6502::B_flag = 1;
    CPU6502::V_flag = 1;
    CPU6502::N_flag = 1;
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0 );
    REQUIRE( CPU6502::Y == 0 );
    REQUIRE( CPU6502::X == 0 );
    REQUIRE( CPU6502::C_flag == 0 );
    REQUIRE( CPU6502::Z_flag == 0 );
    REQUIRE( CPU6502::I_flag == 0 );
    REQUIRE( CPU6502::D_flag == 0 );
    REQUIRE( CPU6502::B_flag == 0 );
    REQUIRE( CPU6502::V_flag == 0 );
    REQUIRE( CPU6502::N_flag == 0 );
}

TEST_CASE( "ADC adds with carry"){
    CPU6502::adc(0xFFFF);
    REQUIRE( );
}