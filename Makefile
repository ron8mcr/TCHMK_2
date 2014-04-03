all:
	g++ -c -fPIC bigInt.cpp
	g++ -shared -o libbigint.so bigInt.o
	g++ -c main.cpp
	g++ main.o -L. -lbigint -o res
