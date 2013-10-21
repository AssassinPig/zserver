cc=g++
cflags= 
src=main.cpp  
all= 

lib=
lib_path= 
include=

main : $(all)
	$(cc) main.cpp -o main $(all) 
$(all): %.o : %.c
	$(cc) -c $< -o $@ 
.PHONY : clean
clean :
	rm $(all) *.out main
	#rm *.o *.out main
