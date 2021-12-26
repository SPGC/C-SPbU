CCFLAGS = -Wall -Werror -Wextra

hw-01_bmp: obj obj/bmp.o obj/main.o
	gcc $(CCFLAGS) -o hw-01_bmp obj/main.o obj/bmp.o 
	chmod +x hw-01_bmp
obj:
	mkdir obj
obj/bmp.o: include/bmp.h src/bmp.c
	gcc -I include $(CCFLAGS) -o obj/bmp.o -c src/bmp.c 
obj/main.o: include/bmp.h src/main.c 
	gcc -I include $(CCFLAGS) -o obj/main.o -c src/main.c 
clean:
	rm -r obj
	rm hw-01_bmp
