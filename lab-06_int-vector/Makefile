CCFLAGS = -Wall -Werror -Wextra

lab-06_int-vector: obj obj/my_vector.o obj/main.o
	g++ $(CCFLAGS) -o lab-06_int-vector obj/main.o obj/my_vector.o 
	chmod +x lab-06_int-vector
obj:
	mkdir obj
obj/my_vector.o: include/my_vector.hpp src/my_vector.cpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/my_vector.o -c src/my_vector.cpp 
obj/main.o: include/my_vector.hpp src/main.cpp 
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/main.o -c src/main.cpp
clean:
	rm -r obj
	rm lab-06_int-vector
