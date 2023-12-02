CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: tests

tests: tests.o
	$(CC) $(FLAGS) -g -o tests tests.o -lgtest_main -lgtest -lpthread

tests.o: tests.cpp avl_allocator.hpp avl_iterator.hpp avl_tree.hpp avl_tree_tests.hpp
	$(CC) $(FLAGS) -g -c tests.cpp -lgtest_main -lgtest -lpthread

test:
	./tests

clean:
	rm -rf *.o tests