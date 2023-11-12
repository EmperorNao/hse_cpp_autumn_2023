CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: tests

tests: tests.o
	$(CC) $(FLAGS) -o tests tests.o -lgtest_main -lgtest -lpthread

tests.o: tests.cpp format.hpp format_tests.hpp
	$(CC) $(FLAGS) -c tests.cpp -lgtest_main -lgtest -lpthread 

test:
	./tests

clean:
	rm -rf *.o tests