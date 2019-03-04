#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "CPU6502.h"
#include "rom.h"
#include "string"

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
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    CPU6502::A = 1;
    CPU6502::adc(0xFF);
    //REQUIRE(CPU6502::A == 0);
    //REQUIRE( CPU6502::C_flag == 1);
}

TEST_CASE( "Accumulator AND"){
    REQUIRE( CPU6502::A == 0);
    CPU6502::A = 0xff;
    CPU6502::an(0xf0);
    REQUIRE( CPU6502::A == 0xf0);
    REQUIRE( CPU6502::Z_flag == 0);
    REQUIRE( CPU6502::N_flag == 1);
}

TEST_CASE( "ASL"){
    CPU6502::A = 0xff;
    REQUIRE( CPU6502::A == 0xf0);
    REQUIRE( CPU6502::Z_flag == 0);
    REQUIRE( CPU6502::N_flag == 1);
}