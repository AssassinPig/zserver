CC=g++
#lib=-lpthread -lboost_thread
lib=
#inc="/home/zhufeng/my_lib/boost_trunk"
inc=-L/usr/local/lib

all: main 

main : main.cpp
	$(CC) main.cpp -o all -I $(inc) $(lib)
group : thread_group.cpp
	$(CC) thread_group.cpp -o group -I $(inc) $(lib)
clean:
	rm *.o *.out all



