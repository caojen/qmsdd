cc = g++
# cflag = -I./include -g -std=c++11
cflag = -I./include -I./include/qmdd -O3 -std=c++11

objs = obj/Complex.o obj/Node.o obj/main.o obj/Util.o obj/BoolFunction.o obj/RealParser.o \
obj/qmdd/qcost.o obj/qmdd/QMDDcircuit.o obj/qmdd/QMDDcomplex.o obj/qmdd/QMDDpackage.o obj/qmdd/QMDDreorder.o obj/qmdd/textFileUtilities.o obj/qmdd/timing.o

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

obj/RealParser.o: src/RealParser.cpp include/RealParser.hpp
	$(cc) $(cflag) src/RealParser.cpp -c -o obj/RealParser.o

obj/qmdd/qcost.o: src/qmdd/qcost.c include/qmdd/qcost.h
	$(cc) $(cflag) $< -c -o $@

obj/qmdd/QMDDcircuit.o: src/qmdd/QMDDcircuit.c include/qmdd/QMDDcircuit.h
	$(cc) $(cflag) $< -c -o $@

obj/qmdd/QMDDcomplex.o: src/qmdd/QMDDcomplex.c include/qmdd/QMDDcomplex.h
	$(cc) $(cflag) $< -c -o $@

obj/qmdd/QMDDpackage.o: src/qmdd/QMDDpackage.c include/qmdd/QMDDpackage.h
	$(cc) $(cflag) $< -c -o $@

obj/qmdd/QMDDreorder.o: src/qmdd/QMDDreorder.c include/qmdd/QMDDreorder.h
	$(cc) $(cflag) $< -c -o $@

obj/qmdd/textFileUtilities.o: src/qmdd/textFileUtilities.c include/qmdd/textFileUtilities.h
	$(cc) $(cflag) $< -c -o $@

obj/qmdd/timing.o: src/qmdd/timing.c include/qmdd/timing.h
	$(cc) $(cflag) $< -c -o $@

bin/main: $(objs)
	$(cc) $(cflag) $^ -o $@

clean:
	rm -rf obj/*.o obj/qmdd/*.o bin/main
