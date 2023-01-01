CXX=c++
CFLAGS=-Isrc -O3

.PHONY : build run clean

build:
	$(CXX) $(CFLAGS) tests/tests.cpp -o seq

run:
	./seq

clean:
	rm -rf seq
