CC = g++

CFLAGS = -Wall -std=c++11

p1: p1.o scanner.o testScanner.o
	$(CC) $(CFLAGS) -o p1 p1.o scanner.o testScanner.o

p1.o: p1.cpp testScanner.cpp testScanner.hpp scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c p1.cpp

testScanner.o: testScanner.cpp testScanner.hpp scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c testScanner.cpp

scanner.o: scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c scanner.cpp

clean: 
	rm *.o p1