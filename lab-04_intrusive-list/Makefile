CCFLAGS = -Wall -Werror -Wextra
lab-04_intrusive-list: obj obj/main.o obj/clist.o 
	gcc $(CCFLAGS) -o lab-04_intrusive-list obj/main.o obj/clist.o
	chmod +x lab-04_intrusive-list
obj:
	mkdir obj
obj/clist.o: include/clist.h src/clist.c
	gcc -I include $(CCFLAGS) -o obj/clist.o -c src/clist.c 
obj/main.o: include/clist.h src/main.c 
	gcc -I include $(CCFLAGS) -o obj/main.o -c src/main.c 
clean:
	rm -r obj
	rm lab-04_intrusive-list
