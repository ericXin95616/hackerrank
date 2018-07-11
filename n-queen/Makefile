n_queen.out : n_queen.o broad.o queen.o
	g++ n_queen.o broad.o queen.o -o n_queen.out

n_queen.o : n_queen.cpp broad.h broad.cpp queen.h queen.cpp
	g++ -Wall -c n_queen.cpp

broad.o : broad.cpp broad.h
	g++ -Wall -c broad.cpp

queen.o : queen.cpp queen.h broad.cpp broad.h 
	g++ -Wall -c queen.cpp

clean :
	rm *.o n_queen.o
