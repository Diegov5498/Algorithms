
CXX = g++ -std=c++17 -Wall

all: run_test

run_test: hashing_test
	./hashing_test

headers: GlassesDisplay.hpp 

hashing_test: headers GlassesDisplay.cpp main.cpp
	${CXX} GlassesDisplay.cpp main.cpp -o hashing_test

clean:
	rm -f hashing_test
