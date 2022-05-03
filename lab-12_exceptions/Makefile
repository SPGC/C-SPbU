CCFLAGS = -Wall -Werror -Wextra

lab-12_exceptions: obj obj/main.o obj/Matrix.o
	g++ $(CCFLAGS) --std=c++17 -o lab-12_exceptions obj/main.o obj/Matrix.o 
	chmod +x lab-12_exceptions

obj:
	mkdir obj

obj/Matrix.o: include/Matrix.hpp src/Matrix.cpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/Matrix.o -c src/Matrix.cpp 

obj/main.o: include/Matrix.hpp src/main.cpp 
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/main.o -c src/main.cpp

clean:
	rm -r obj
	rm lab-12_exceptions
	
