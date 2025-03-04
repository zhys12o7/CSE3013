cc=g++ 
target = answer  

objects = array.o main.o rangearray.o 

$(target) : $(objects) Array.h RangeArray.h 
	$(cc) -o $(target) $(objects) 

.PHONY : clean  
clean :
	rm $(target) $(objects)
