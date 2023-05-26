override CC=gcc-11.3.0
override CXX=g++-11.3.0

all: proj4

proj4: MST_algo.cpp
	g++ MST_algo.cpp -o proj4
