CCFLAGS = -Wall -Werror -Wextra

lab-03_mergesort: obj obj/main.o obj/mergesort.o 
	gcc $(CCFLAGS) -o lab-03_mergesort obj/main.o obj/mergesort.o
	chmod +x lab-03_mergesort

obj:
	mkdir obj

obj/main.o: include/mergesort.h src/main.c 
	gcc -I include $(CCFLAGS) -o obj/main.o -c src/main.c 

obj/mergesort.o: include/mergesort.h src/mergesort.c 	
	gcc -I include $(CCFLAGS) -o obj/mergesort.o -c src/mergesort.c 

clean:
	rm -r obj
	rm lab-03_mergesort