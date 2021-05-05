cc = g++
# cflag = -I./include -g -std=c++11
cflag = -I./include -O2 -std=c++11

all: bin/main

obj/Complex.o: include/Complex.hpp src/Complex.cpp
	$(cc) $(cflag) src/Complex.cpp -c -o obj/Complex.o

obj/Node.o: include/Node.hpp src/Node.cpp
	$(cc) $(cflag) src/Node.cpp -c -o obj/Node.o

obj/main.o: src/main.cpp
	$(cc) $(cflag) src/main.cpp -c -o obj/main.o

obj/Util.o: src/Util.cpp include/Util.hpp
	$(cc) $(cflag) src/Util.cpp -c -o obj/Util.o

obj/BoolFunction.o: src/BoolFunction.cpp include/BoolFunction.hpp
	$(cc) $(cflag) src/BoolFunction.cpp -c -o obj/BoolFunction.o

bin/main: obj/Complex.o obj/Node.o obj/main.o obj/Util.o obj/BoolFunction.o
	$(cc) $(cflag) $^ -o $@

clean:
	rm -rf obj/*.o bin/main
