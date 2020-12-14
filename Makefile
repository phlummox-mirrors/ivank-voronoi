
.PHONY: clean

# Required headers & libraries: on ubuntu:
# - apt-get install freeglut3-dev libglew-dev
# build tools:
# - needs g++ (or amend CXX to clang++)

CXX=g++
CC=$(CXX)
CXXFLAGS=--pedantic -Wall -Wextra -g -std=c++17 -I.  $(shell pkg-config --cflags glew)
LDFLAGS=-g
LDLIBS=$(shell pkg-config --libs glew) -lglut
SHELL=bash

main:

cpp_objs=$(shell for file in *.cpp; do obj=$${file/.cpp/.o}; echo $$obj; done)
c_objs=$(shell for file in *.c; do obj=$${file/.c/.o}; echo $$obj; done)

main: $(cpp_objs) $(c_objs)


clean:
	-rm *.o main



