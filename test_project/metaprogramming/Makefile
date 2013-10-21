CC=g++

all:main.o binary_num.o policy.o
	$(CC) main.cpp
main.o:main.cpp  binary_num.o
	$(CC) -c main.cpp
binary_num.o:binary_num.hpp
	$(CC) -c binary_num.hpp
policy.o:policy.hpp
	$(CC) -c policy.hpp
clean:
	rm *.o *.out *.gch

