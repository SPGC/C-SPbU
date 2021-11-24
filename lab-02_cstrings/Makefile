CCFLAGS = -Wall -Werror -Wextra

lab-02_cstrings: obj obj/str.o obj/test_str.o obj/test.o
	gcc $(CCFLAGS) -o lab-02_cstring obj/str.o obj/test_str.o obj/test.o

obj: 
	mkdir obj

obj/str.o: include/str.h src/str.c
	gcc -I ./include $(CCFLAGS) -c -o ./obj/str.o ./src/str.c

obj/test_str.o: include/test_str.h src/test_str.c 
	gcc -I ./include $(CCFLAGS) -c -o ./obj/test_str.o ./src/test_str.c 

obj/test.o: include/test_str.h src/test.c 
	gcc -I ./include $(CCFLAGS) -c -o ./obj/test.o ./src/test.c
