CC=gcc
FLAGS=-g  -I/usr/include/python3.10 -lpython3.10

all: build

build: cjson_impl.h cjson.h cjson.c
	pip install .

test:
	pytest cjson_tests.py -s

clean:
	rm -rf *.o build cjson.eff-info .pytest_cache