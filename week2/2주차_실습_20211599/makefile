cc=gcc
target = animal_exe

objects = dog.o blackcow.o turtle.o

$(target) : $(objects)
	$(cc) -o $(target) $(objects)


$(objects)  : some.h

.PHONY : clean
clean : 
	rm $(target) $(objects)

