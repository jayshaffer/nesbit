#include "CPU6502.h"
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
    std::cout << "test";
    std::ifstream file("test.nes");
    char* data = 0;
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);
    data = new char[size + 1];
    data[size] = '\0';
    file.read(data, size);
}