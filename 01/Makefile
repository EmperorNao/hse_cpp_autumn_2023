CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: allocator_tests

allocator_tests: allocator.o allocator_tests.o
	$(CC) $(FLAGS) -o tests allocator_tests.o allocator.o -lgtest_main -lgtest -lpthread

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) -c allocator.cpp

allocator_tests.o: allocator_tests.cpp allocator_tests.hpp 
	$(CC) $(FLAGS) -c allocator_tests.cpp -lgtest_main -lgtest -lpthread 

test:
	./tests

clean:
	rm -rf *.o tests