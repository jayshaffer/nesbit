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
    REQUIRE( CPU6502::V_flag == 0 );
    REQUIRE( CPU6502::N_flag == 0 );
}

TEST_CASE( "ADC adds with carry resulting in no carry or overflow"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    REQUIRE( CPU6502::V_flag == 0);
    CPU6502::A = 0x7E;
    uint16_t m = 0x01;
    CPU6502::adc(&m);
    REQUIRE(CPU6502::A == 0x7F);
    REQUIRE( CPU6502::C_flag == 0);
    REQUIRE( CPU6502::V_flag == 0);
}

TEST_CASE( "ADC adds with carry resulting in carry"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    CPU6502::A = 2;
    uint16_t m = 0xFF;
    CPU6502::adc(&m);
    REQUIRE(CPU6502::A);
    REQUIRE( CPU6502::C_flag);
}

TEST_CASE( "ADC adds with carry resulting in overflow"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    CPU6502::A = 1;
    uint16_t m = 0x7f;
    CPU6502::adc(&m);
    REQUIRE(CPU6502::A == 0x80);
    REQUIRE( CPU6502::C_flag == 0);
    REQUIRE( CPU6502::V_flag);
}

TEST_CASE( "SBC with carry resulting in no carry or overflow"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    REQUIRE( CPU6502::V_flag == 0);
    CPU6502::A = 0xFF;
    CPU6502::sec();
    uint16_t m = 1;
    CPU6502::sbc(&m);
    REQUIRE(CPU6502::A == 0xFE);
    REQUIRE( CPU6502::C_flag == 1);
    REQUIRE( CPU6502::V_flag == 0);
}

TEST_CASE( "SBC with carry resulting in carry"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    CPU6502::A = 2;
    uint16_t m = 0xFF;
    CPU6502::adc(&m);
    REQUIRE(CPU6502::A);
    REQUIRE( CPU6502::C_flag);
}

TEST_CASE( "SBC with carry resulting in overflow"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    REQUIRE( CPU6502::C_flag == 0);
    CPU6502::A = 1;
    uint16_t m = 0x7F;
    CPU6502::adc(&m);
    REQUIRE(CPU6502::A == 0x80);
    REQUIRE( CPU6502::C_flag == 0);
    REQUIRE( CPU6502::V_flag);
}

TEST_CASE( "Accumulator AND"){
    CPU6502::reset();
    REQUIRE( CPU6502::A == 0);
    CPU6502::A = 0xff;
    uint16_t m = 0xf0;
    CPU6502::an(&m);
    REQUIRE( CPU6502::A == 0xf0);
    REQUIRE( CPU6502::Z_flag == 0);
    REQUIRE( CPU6502::N_flag);
}

TEST_CASE( "ASL"){
    uint16_t m = 0x0f;
    CPU6502::reset();
    CPU6502::asl(&m);
    REQUIRE( m == 30);
    REQUIRE( CPU6502::Z_flag == 0);
    REQUIRE( CPU6502::N_flag == 0);
}

TEST_CASE("plp should pull the status flags off the stack"){
    CPU6502::reset();
    CPU6502::A = 0xFF;
    REQUIRE( CPU6502::C_flag == 0 );
    REQUIRE( CPU6502::Z_flag == 0 );
    REQUIRE( CPU6502::I_flag == 0 );
    REQUIRE( CPU6502::D_flag == 0 );
    REQUIRE( CPU6502::V_flag == 0 );
    REQUIRE( CPU6502::N_flag == 0 );
    CPU6502::pha();
    CPU6502::plp();
    REQUIRE( CPU6502::C_flag == 1 );
    REQUIRE( CPU6502::Z_flag == 1 );
    REQUIRE( CPU6502::I_flag == 1 );
    REQUIRE( CPU6502::D_flag == 1 );
    REQUIRE( CPU6502::V_flag == 1 );
    REQUIRE( CPU6502::N_flag == 1 );
}