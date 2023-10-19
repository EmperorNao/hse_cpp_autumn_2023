CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: tests

tests: dynamic_array.o bigint.o tests.o
	$(CC) $(FLAGS) -o tests dynamic_array.o bigint.o tests.o -lgtest_main -lgtest -lpthread

dynamic_array.o: dynamic_array.cpp dynamic_array.hpp
	$(CC) $(FLAGS) -c dynamic_array.cpp	

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c bigint.cpp

tests.o: tests.cpp bigint_tests.hpp dynamic_array_tests.hpp 
	$(CC) $(FLAGS) -c tests.cpp -lgtest_main -lgtest -lpthread 

test:
	./tests

clean:
	rm -rf *.o tests