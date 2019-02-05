CXX = g++
GCCFLAGS = -Wall -g
VPATH = src

main: main.o CPU6502.o rom.o
	$(CXX) -o $@ $^