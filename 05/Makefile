CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra -Wno-unused-variable -pedantic

all: tests

tests: error.o tests.o
	$(CC) $(FLAGS) -o tests tests.o error.o -lgtest_main -lgtest -lpthread

error.o: error.hpp error.cpp
	$(CC) $(FLAGS) -c error.cpp

tests.o: tests.cpp serializer.hpp serializer.tpp deserializer.hpp deserializer.tpp
	$(CC) $(FLAGS) -c error.o tests.cpp -lgtest_main -lgtest -lpthread 

test:
	./tests

clean:
	rm -rf *.o tests