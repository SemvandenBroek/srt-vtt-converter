default:
	g++ -std=c++11 -o srtconverter.o main.cpp

install:
	cp srtconverter.o /usr/bin/srtconverter