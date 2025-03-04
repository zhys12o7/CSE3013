cc=gcc  #gcc를 이용해 컴파일을 하겠다
cflags = -W -g  
target = answer  #answer의 이름으로 make를 하겠다.

objects = main.o page.o print.o #사용되는 파일

$(target) : $(objects) 
	$(cc) $(cflags) -o $(target) $(objects) 

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o page.o print.o : Header.h  #헤더파일 사용

.PHONY : clean  #만일의 경우를 대비한다.
clean : # 나온 파일을 지운다.
	rm $(target) $(objects)
