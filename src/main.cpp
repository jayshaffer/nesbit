#include "CPU6502.h"
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "rom.h"

using namespace std;

int main(int argc, char* argv[]){
    const int PRG_INC = 16384;
    const int CHR_INC = 8192;
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