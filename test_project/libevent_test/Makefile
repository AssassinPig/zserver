cc=g++
cflags= 
src=main.cpp  
all= 

lib=-levent
lib_path=/usr/lib/libevent-2.0.so.5 
include=/usr/local/include

main : $(all)
	$(cc) main.cpp -o main $(all) $(cflags) -I $(include) $(lib) 
$(all): %.o : %.c
	$(cc) -c $< -o $@ $(cflags)	-I $(include) $(lib)
.PHONY : clean
clean :
	rm $(all) *.out main
	#rm *.o *.out main
