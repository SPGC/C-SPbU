CCFLAGS = -Wall -Werror -Wextra

lab-05_c-io: obj obj/clist.o obj/point_list.o obj/main.o
	gcc $(CCFLAGS) -o lab-05_c-io obj/main.o obj/clist.o obj/point_list.o
	chmod +x lab-05_c-io
obj:
	mkdir obj
obj/clist.o: include/clist.h src/clist.c
	gcc -I include $(CCFLAGS) -o obj/clist.o -c src/clist.c 
obj/point_list.o: include/point_list.h src/point_list.c
	gcc -I include $(CCFLAGS) -o obj/point_list.o -c src/point_list.c 
obj/main.o: include/clist.h include/point_list.h src/main.c 
	gcc -I include $(CCFLAGS) -o obj/main.o -c src/main.c 
clean:
	rm -r obj
	rm lab-05_c-io
	rm *.txt
	rm *.bin
