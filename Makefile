all:
	g++ -c -fPIC bigInt.cpp
	g++ -shared -o libbigint.so bigInt.o
	LD_LIBRARY_PATH=./ g++ main.cpp -lbigint -I. -Wl,-rpath,. -L. -o TCHMK_2
	
windows:
	g++ -c bigInt.cpp
	g++ -shared -o bigint.dll bigInt.o
	g++ main.cpp bigint.dll -I. -Wl,-rpath,. -L. -o TCHMK_2.exe