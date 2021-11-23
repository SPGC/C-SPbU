lab-01_makefile: obj obj/main.o obj/io.o obj/algorithm.o obj/util.o 
	gcc -o lab-01_makefile ./obj/algorithm.o ./obj/util.o ./obj/main.o ./obj/io.o 
obj:
	mkdir obj
obj/main.o: ./src/main.c ./include/io.h ./include/util.h ./include/algorithm.h
	gcc -I ./include -c -o ./obj/main.o ./src/main.c
obj/util.o: ./src/util.c ./include/util.h ./include/io.h
	gcc -I ./include -c -o ./obj/util.o ./src/util.c
obj/io.o: ./src/io.c ./include/io.h 
	gcc -I ./include -c -o ./obj/io.o ./src/io.c
obj/algorithm.o: ./src/algorithm.c ./include/algorithm.h ./include/io.h ./include/util.h
	gcc -I ./include -c -o ./obj/algorithm.o ./src/algorithm.c