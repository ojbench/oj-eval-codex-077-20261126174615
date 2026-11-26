.PHONY: all test clean

all: code

# The problem consumes a C++ header rather than a standalone executable.
code: CrossArray.hpp
	cp CrossArray.hpp code

test:
	mkdir -p build
	$(CXX) -std=c++11 -O1 -g -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer tests/cross_array_test.cpp -o build/cross_array_test
	./build/cross_array_test

clean:
	rm -rf build code
