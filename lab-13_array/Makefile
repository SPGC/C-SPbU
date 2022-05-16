CCFLAGS = -Wall -Werror -Wextra

lab-13_array: obj obj/main.o 
	g++ $(CCFLAGS) --std=c++17 -o lab-13_array obj/main.o
	chmod +x lab-13_array

obj:
	mkdir obj

obj/main.o: include/my_array.h src/main.cpp 
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/main.o -c src/main.cpp

clean:
	rm -r obj
	rm lab-13_array
	
