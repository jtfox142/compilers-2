CC = g++

CFLAGS = -Wall -std=c++11

p2: p2.o scanner.o parser.o tree.o
	$(CC) $(CFLAGS) -o p2 p2.o scanner.o parser.o tree.o

p2.o: p2.cpp parser.cpp parser.hpp scanner.cpp scanner.hpp tree.hpp token.hpp
	$(CC) $(CFLAGS) -c p2.cpp

parser.o: parser.cpp parser.hpp tree.cpp tree.hpp node.hpp scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c parser.cpp

tree.o: tree.cpp tree.hpp node.hpp
	$(CC) $(CFLAGS) -c tree.cpp

scanner.o: scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c scanner.cpp

clean: 
	rm *.o p2