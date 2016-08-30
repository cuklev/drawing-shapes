CXX=g++
CXXFLAGS=-O2 -std=gnu++11
LDFLAGS=-lpng

all: draw

draw: draw.o
	${CXX} "$<" -o "$@" ${LDFLAGS}

%.o: %.cpp
	${CXX} -c "$<" -o "$@" ${CXXFLAGS}

.PHONY: all
