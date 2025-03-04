cc=g++ 
target = answer  

objects = main.o string.o 

$(target) : $(objects) string.h 
	$(cc) -o $(target) $(objects) 

.PHONY : clean  
clean :
	rm $(target) $(objects)
