cc = gcc
cflag = -I./include -g -std=c++11

obj/Complex.o: include/Complex.hpp src/Complex.cpp
	$(cc) $(cflag) src/Complex.cpp -c -o obj/Complex.o

obj/Node.o: include/Node.hpp src/Node.cpp
	$(cc) $(cflag) src/Node.cpp -c -o obj/Node.o

clean:
	rm -rf obj/*.o bin/main