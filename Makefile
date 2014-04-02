all:	
	g++ -shared -fPIC bigInt.cpp -o bigInt.so
	g++  main.cpp -ldl -o test
