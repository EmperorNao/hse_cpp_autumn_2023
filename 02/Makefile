CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: parser_tests

parser_tests: parser.o parser_tests.o
	$(CC) $(FLAGS) -o tests parser_tests.o parser.o -lgtest_main -lgtest -lpthread

parser.o: parser.cpp parser.hpp
	$(CC) $(FLAGS) -c parser.cpp

parser_tests.o: parser_tests.cpp parser_tests.hpp 
	$(CC) $(FLAGS) -c parser_tests.cpp -lgtest_main -lgtest -lpthread 

test:
	./tests

clean:
	rm -rf *.o tests