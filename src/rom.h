#pragma once
#include <stdint.h>
#include <string>

namespace ROM{
    uint8_t rd(uint16_t address);
    void load(std::string filepath);
    void fill(char data[], int length);
}