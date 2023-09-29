CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: matrix_tests

matrix_tests: matrix.o matrix_tests.o
	$(CC) $(FLAGS) -o tests matrix_tests.o matrix.o -lgtest_main -lgtest -lpthread

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) -c matrix.cpp

matrix_tests.o: matrix_tests.cpp matrix_tests.hpp 
	$(CC) $(FLAGS) -c matrix_tests.cpp -lgtest_main -lgtest -lpthread 

test:
	./tests

clean:
	rm -rf *.o tests