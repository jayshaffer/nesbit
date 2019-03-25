#include "CPU6502.h"
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "rom.h"

using namespace std;

int main(int argc, char* argv[]){
  ROM::load("donkeykong.nes");
  CPU6502::reset();
  CPU6502::power();
}